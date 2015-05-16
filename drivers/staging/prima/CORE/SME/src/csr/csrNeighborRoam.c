/*
 * Copyright (c) 2012-2014 The Linux Foundation. All rights reserved.
 *
 * Previously licensed under the ISC license by Qualcomm Atheros, Inc.
 *
 *
 * Permission to use, copy, modify, and/or distribute this software for
 * any purpose with or without fee is hereby granted, provided that the
 * above copyright notice and this permission notice appear in all
 * copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * This file was originally distributed by Qualcomm Atheros, Inc.
 * under proprietary terms before Copyright ownership was assigned
 * to the Linux Foundation.
 */

/** ------------------------------------------------------------------------- * 
    ------------------------------------------------------------------------- *  

  
    \file csrNeighborRoam.c
  
    Implementation for the simple roaming algorithm for 802.11r Fast transitions and Legacy roaming for Android platform.
  
    Copyright (C) 2010 Qualcomm, Incorporated
  
 
   ========================================================================== */

/*                                                                           

                                           


                                                                       
                                                                



                                                     
                                                                                            
                                            

                                                                           */
#ifdef WLAN_FEATURE_NEIGHBOR_ROAMING
#include "wlan_qct_wda.h"
#include "palApi.h"
#include "csrInsideApi.h"
#include "smsDebug.h"
#include "logDump.h"
#include "smeQosInternal.h"
#include "wlan_qct_tl.h"
#include "smeInside.h"
#include "vos_diag_core_event.h"
#include "vos_diag_core_log.h"
#include "csrApi.h"
#include "wlan_qct_tl.h"
#include "sme_Api.h"
#include "csrNeighborRoam.h"
#include "macTrace.h"
#if defined(FEATURE_WLAN_ESE) && !defined(FEATURE_WLAN_ESE_UPLOAD)
#include "csrEse.h"
#endif

#define WLAN_FEATURE_NEIGHBOR_ROAMING_DEBUG 1
#ifdef WLAN_FEATURE_NEIGHBOR_ROAMING_DEBUG
#define NEIGHBOR_ROAM_DEBUG smsLog
#else
#define NEIGHBOR_ROAM_DEBUG(x...)
#endif

static void csrNeighborRoamResetChannelInfo(tpCsrNeighborRoamChannelInfo rChInfo);
static void csrNeighborRoamResetCfgListChanScanControlInfo(tpAniSirGlobal pMac);
static void csrNeighborRoamResetPreauthControlInfo(tpAniSirGlobal pMac);
static void csrNeighborRoamDeregAllRssiIndication(tpAniSirGlobal pMac);

VOS_STATUS csrNeighborRoamNeighborLookupUPCallback (v_PVOID_t pAdapter, v_U8_t rssiNotification,
                                                                               v_PVOID_t pUserCtxt,
                                                                               v_S7_t avgRssi);
VOS_STATUS csrNeighborRoamNeighborLookupDOWNCallback (v_PVOID_t pAdapter, v_U8_t rssiNotification,
                                                                               v_PVOID_t pUserCtxt,
                                                                               v_S7_t avgRssi);
void csrNeighborRoamRRMNeighborReportResult(void *context, VOS_STATUS vosStatus);
eHalStatus csrRoamCopyConnectedProfile(tpAniSirGlobal pMac, tANI_U32 sessionId, tCsrRoamProfile *pDstProfile );

#ifdef WLAN_FEATURE_VOWIFI_11R
static eHalStatus csrNeighborRoamIssuePreauthReq(tpAniSirGlobal pMac);
VOS_STATUS csrNeighborRoamIssueNeighborRptRequest(tpAniSirGlobal pMac);
#endif

v_U8_t *csrNeighborRoamStateToString(v_U8_t state)
{
    switch(state)
    {
        CASE_RETURN_STRING( eCSR_NEIGHBOR_ROAM_STATE_CLOSED );
        CASE_RETURN_STRING( eCSR_NEIGHBOR_ROAM_STATE_INIT );
        CASE_RETURN_STRING( eCSR_NEIGHBOR_ROAM_STATE_CONNECTED );
        CASE_RETURN_STRING( eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN );
        CASE_RETURN_STRING( eCSR_NEIGHBOR_ROAM_STATE_REASSOCIATING );
        CASE_RETURN_STRING( eCSR_NEIGHBOR_ROAM_STATE_REPORT_QUERY );
        CASE_RETURN_STRING( eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN );
        CASE_RETURN_STRING( eCSR_NEIGHBOR_ROAM_STATE_PREAUTHENTICATING );
        CASE_RETURN_STRING( eCSR_NEIGHBOR_ROAM_STATE_PREAUTH_DONE );
            default:
        return "eCSR_NEIGHBOR_ROAM_STATE_UNKNOWN";
    }

}

/*                        */
#define CSR_NEIGHBOR_ROAM_STATE_TRANSITION(newState)\
{\
    pMac->roam.neighborRoamInfo.prevNeighborRoamState = pMac->roam.neighborRoamInfo.neighborRoamState;\
    pMac->roam.neighborRoamInfo.neighborRoamState = newState;\
    VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_DEBUG, \
               FL("Neighbor Roam Transition from state %s ==> %s"), \
               csrNeighborRoamStateToString (pMac->roam.neighborRoamInfo.prevNeighborRoamState), \
               csrNeighborRoamStateToString (newState));\
}

/*                                                                            

                                              

                                                                                    
                                          

                                                  
                                                                    

                

                                                                           */
void csrNeighborRoamFreeNeighborRoamBSSNode(tpAniSirGlobal pMac, tpCsrNeighborRoamBSSInfo neighborRoamBSSNode)
{
    if (neighborRoamBSSNode)
    {
        if (neighborRoamBSSNode->pBssDescription)
        {
            vos_mem_free(neighborRoamBSSNode->pBssDescription);
            neighborRoamBSSNode->pBssDescription = NULL;
        }
        vos_mem_free(neighborRoamBSSNode);
        neighborRoamBSSNode = NULL;
    }

    return;
}

/*                                                                            

                                                

                                                                   

                                                  
                                                                   
                                                                 

                                                    

                                                                           */
tANI_BOOLEAN csrNeighborRoamRemoveRoamableAPListEntry(tpAniSirGlobal pMac, 
                                                tDblLinkList *pList, tpCsrNeighborRoamBSSInfo pNeighborEntry)
{
    if(pList)
    {
        return csrLLRemoveEntry(pList, &pNeighborEntry->List, LL_ACCESS_LOCK);
    }

    smsLog(pMac, LOGE, FL("Removing neighbor BSS node from list failed. Current count = %d"), csrLLCount(pList));

    return eANI_BOOLEAN_FALSE;
}

/*                                                                            

                                                 

                                                                                                            

                                                  
                                                                    
                                                                                       

                                                 

                                                                           */
tpCsrNeighborRoamBSSInfo csrNeighborRoamGetRoamableAPListNextEntry(tpAniSirGlobal pMac, 
                                        tDblLinkList *pList, tpCsrNeighborRoamBSSInfo pNeighborEntry)
{
    tListElem *pEntry = NULL;
    tpCsrNeighborRoamBSSInfo pResult = NULL;
    
    if(pList)
    {
        if(NULL == pNeighborEntry)
        {
            pEntry = csrLLPeekHead(pList, LL_ACCESS_LOCK);
        }
        else
        {
            pEntry = csrLLNext(pList, &pNeighborEntry->List, LL_ACCESS_LOCK);
        }
        if(pEntry)
        {
            pResult = GET_BASE_ADDR(pEntry, tCsrNeighborRoamBSSInfo, List);
        }
    }
    
    return pResult;
}

/*                                                                            

                                          

                                                                     

                                                  
                                                        

                

                                                                           */
void csrNeighborRoamFreeRoamableBSSList(tpAniSirGlobal pMac, tDblLinkList *pList)
{
    tpCsrNeighborRoamBSSInfo pResult = NULL;

    NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Emptying the BSS list. Current count = %d"), csrLLCount(pList));

    /*                                                                        */
    while ((pResult = csrNeighborRoamGetRoamableAPListNextEntry(pMac, pList, NULL)) != NULL)
    {
        csrNeighborRoamRemoveRoamableAPListEntry(pMac, pList, pResult);
        csrNeighborRoamFreeNeighborRoamBSSNode(pMac, pResult);
    }
    return;
}

static void csrNeighborRoamTriggerHandoff(tpAniSirGlobal pMac, 
                                          tpCsrNeighborRoamControlInfo pNeighborRoamInfo)
{
#ifdef WLAN_FEATURE_VOWIFI_11R
    if ((pNeighborRoamInfo->is11rAssoc)
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
     && !csrRoamIsRoamOffloadScanEnabled(pMac)
#endif
    )
    {
        if ((eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN == pNeighborRoamInfo->neighborRoamState) ||
            (eSME_ROAM_TRIGGER_FAST_ROAM == pNeighborRoamInfo->cfgRoamEn))
        {
            csrNeighborRoamIssuePreauthReq(pMac);
            pNeighborRoamInfo->cfgRoamEn = eSME_ROAM_TRIGGER_NONE;
            vos_mem_set(&pNeighborRoamInfo->cfgRoambssId[0],
                        sizeof(pNeighborRoamInfo->cfgRoambssId),
                        0xFF);
        }
        else
        {
            smsLog(pMac, LOGE, FL("11R Reassoc indication received in"
                   "unexpected state %s"),
                   macTraceGetNeighbourRoamState(
                   pNeighborRoamInfo->neighborRoamState));
            VOS_ASSERT(0);
        }
    }
    else
#endif

#ifdef FEATURE_WLAN_ESE
        if ((pNeighborRoamInfo->isESEAssoc)
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        && !csrRoamIsRoamOffloadScanEnabled(pMac)
#endif
        )
        {
            if (eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN == pNeighborRoamInfo->neighborRoamState)
            {
                csrNeighborRoamIssuePreauthReq(pMac);
            }
            else
            {
                smsLog(pMac, LOGE, FL("ESE Reassoc indication received in unexpected state %s"),
                       macTraceGetNeighbourRoamState(pNeighborRoamInfo->neighborRoamState));
                VOS_ASSERT(0);
            }
        }
        else
#endif
#ifdef FEATURE_WLAN_LFR
            if (csrRoamIsFastRoamEnabled(pMac, CSR_SESSION_ID_INVALID))
            {
                if ((eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN == pNeighborRoamInfo->neighborRoamState)
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
                || csrRoamIsRoamOffloadScanEnabled(pMac) ||
                (eSME_ROAM_TRIGGER_FAST_ROAM == pNeighborRoamInfo->cfgRoamEn)
#endif
                )
                {
                    csrNeighborRoamIssuePreauthReq(pMac);
                    pNeighborRoamInfo->cfgRoamEn = eSME_ROAM_TRIGGER_NONE;
                    vos_mem_set(&pNeighborRoamInfo->cfgRoambssId[0],
                                sizeof(pNeighborRoamInfo->cfgRoambssId),
                                0xFF);
                }
                else
                {
                    smsLog(pMac, LOGE, FL("LFR Reassoc indication received in"
                           "unexpected state %s"),
                           macTraceGetNeighbourRoamState(
                           pNeighborRoamInfo->neighborRoamState));
                    VOS_ASSERT(0);
                }
            }
            else
#endif
            {
                if (eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN == pNeighborRoamInfo->neighborRoamState)
                {
                    csrNeighborRoamRequestHandoff(pMac);
                }
                else
                {
                    smsLog(pMac, LOGE, FL("Non-11R Reassoc indication received in"
                           "unexpected state %s or Roaming is disabled"),
                           macTraceGetNeighbourRoamState(
                           pNeighborRoamInfo->neighborRoamState));
                }
            }
}

VOS_STATUS csrNeighborRoamUpdateFastRoamingEnabled(tpAniSirGlobal pMac, const v_BOOL_t fastRoamEnabled)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    VOS_STATUS vosStatus = VOS_STATUS_SUCCESS;

    if (eCSR_NEIGHBOR_ROAM_STATE_CONNECTED == pNeighborRoamInfo->neighborRoamState)
    {
        if (VOS_TRUE == fastRoamEnabled)
        {
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            if (pMac->roam.configParam.isRoamOffloadScanEnabled)
            {
                csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_START, REASON_CONNECT);
            } else {
#endif
            NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Registering neighbor lookup DOWN event with TL, RSSI = %d"),
                                    pNeighborRoamInfo->currentNeighborLookupThreshold);
            /*                                                                         */
            vosStatus = WLANTL_RegRSSIIndicationCB(pMac->roam.gVosContext, (v_S7_t)pNeighborRoamInfo->currentNeighborLookupThreshold * (-1),
                                                WLANTL_HO_THRESHOLD_DOWN,
                                                csrNeighborRoamNeighborLookupDOWNCallback,
                                                VOS_MODULE_ID_SME, pMac);
            if (!VOS_IS_STATUS_SUCCESS(vosStatus))
            {
                //       
                smsLog(pMac, LOGE, FL(" Couldn't register csrNeighborRoamNeighborLookupDOWNCallback with TL: Status = %d"), vosStatus);
                vosStatus = VOS_STATUS_E_FAILURE;
            }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            }
#endif
        }
        else if (VOS_FALSE == fastRoamEnabled)
        {
            NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Currently in CONNECTED state, so deregister all events"));
            /*                                                       */
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            if (pMac->roam.configParam.isRoamOffloadScanEnabled)
            {
               csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_STOP, REASON_DISCONNECTED);
            } else {
#endif
            csrNeighborRoamDeregAllRssiIndication(pMac);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            }
#endif
        }
    }
    else if (eCSR_NEIGHBOR_ROAM_STATE_INIT == pNeighborRoamInfo->neighborRoamState)
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Currently in INIT state, Nothing to do"));
    }
    else
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGE,
        FL("Unexpected state %s, returning failure"),
        macTraceGetNeighbourRoamState(
        pNeighborRoamInfo->neighborRoamState));
        vosStatus = VOS_STATUS_E_FAILURE;
    }
    return vosStatus;
}

#ifdef FEATURE_WLAN_ESE
VOS_STATUS csrNeighborRoamUpdateEseModeEnabled(tpAniSirGlobal pMac, const v_BOOL_t eseMode)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    VOS_STATUS vosStatus = VOS_STATUS_SUCCESS;

    if (eCSR_NEIGHBOR_ROAM_STATE_CONNECTED == pNeighborRoamInfo->neighborRoamState)
    {
        if (VOS_TRUE == eseMode)
        {
            NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Registering neighbor lookup DOWN event with TL, RSSI = %d"),
                                    pNeighborRoamInfo->currentNeighborLookupThreshold);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            if (pMac->roam.configParam.isRoamOffloadScanEnabled)
            {
                csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_START, REASON_CONNECT);
            } else {
#endif
            /*                                                                         */
            vosStatus = WLANTL_RegRSSIIndicationCB(pMac->roam.gVosContext, (v_S7_t)pNeighborRoamInfo->currentNeighborLookupThreshold * (-1),
                                                WLANTL_HO_THRESHOLD_DOWN,
                                                csrNeighborRoamNeighborLookupDOWNCallback,
                                                VOS_MODULE_ID_SME, pMac);
            if (!VOS_IS_STATUS_SUCCESS(vosStatus))
            {
                //       
                smsLog(pMac, LOGE, FL(" Couldn't register csrNeighborRoamNeighborLookupDOWNCallback with TL: Status = %d"), vosStatus);
                vosStatus = VOS_STATUS_E_FAILURE;
            }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            }
#endif
        }
        else if (VOS_FALSE == eseMode)
        {
            NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Currently in CONNECTED state, so deregister all events"));
            /*                                                       */
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            if (pMac->roam.configParam.isRoamOffloadScanEnabled)
            {
               csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_STOP, REASON_DISCONNECTED);
            } else {
#endif
            csrNeighborRoamDeregAllRssiIndication(pMac);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            }
#endif
        }
    }
    else if (eCSR_NEIGHBOR_ROAM_STATE_INIT == pNeighborRoamInfo->neighborRoamState)
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Currently in INIT state, Nothing to do"));
    }
    else
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("Unexpected state %d, returning failure"), pNeighborRoamInfo->neighborRoamState);
        vosStatus = VOS_STATUS_E_FAILURE;
    }
    return vosStatus;
}

#endif


VOS_STATUS csrNeighborRoamSetLookupRssiThreshold(tpAniSirGlobal pMac, v_U8_t neighborLookupRssiThreshold)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    VOS_STATUS vosStatus = VOS_STATUS_SUCCESS;

    if (eCSR_NEIGHBOR_ROAM_STATE_CONNECTED == pNeighborRoamInfo->neighborRoamState)
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Currently in CONNECTED state, so deregister all and re-register for DOWN event again"));

        pMac->roam.neighborRoamInfo.cfgParams.neighborLookupThreshold = neighborLookupRssiThreshold;
        pNeighborRoamInfo->currentNeighborLookupThreshold = pMac->roam.neighborRoamInfo.cfgParams.neighborLookupThreshold;

        /*                                                       */
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        if (pMac->roam.configParam.isRoamOffloadScanEnabled)
        {
            csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_UPDATE_CFG, REASON_LOOKUP_THRESH_CHANGED);
        }
        else
        {
#endif
           csrNeighborRoamDeregAllRssiIndication(pMac);

           NEIGHBOR_ROAM_DEBUG(pMac, LOG2,
           FL("Registering neighbor lookup DOWN event with TL, RSSI = %d"),
           pNeighborRoamInfo->currentNeighborLookupThreshold);
           /*                                                                         */
           vosStatus = WLANTL_RegRSSIIndicationCB(pMac->roam.gVosContext,
                       (v_S7_t)pNeighborRoamInfo->currentNeighborLookupThreshold * (-1),
                       WLANTL_HO_THRESHOLD_DOWN,
                       csrNeighborRoamNeighborLookupDOWNCallback,
                       VOS_MODULE_ID_SME, pMac);
           if (!VOS_IS_STATUS_SUCCESS(vosStatus))
           {
              //       
              smsLog(pMac, LOGE, FL(" Couldn't register csrNeighborRoamNeighborLookupDOWNCallback with TL: Status = %d"), vosStatus);
              vosStatus = VOS_STATUS_E_FAILURE;
           }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        }
#endif
    }
    else if (eCSR_NEIGHBOR_ROAM_STATE_INIT == pNeighborRoamInfo->neighborRoamState)
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Currently in INIT state, safe to set lookupRssi threshold"));
        pMac->roam.neighborRoamInfo.cfgParams.neighborLookupThreshold = neighborLookupRssiThreshold;
        pNeighborRoamInfo->currentNeighborLookupThreshold = pMac->roam.neighborRoamInfo.cfgParams.neighborLookupThreshold;
    }
    else
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGE,
        FL("Unexpected state %s, returning failure"),
        macTraceGetNeighbourRoamState(pNeighborRoamInfo->neighborRoamState));
        vosStatus = VOS_STATUS_E_FAILURE;
    }
    return vosStatus;
}

/*                                                                            

                                         

                                                                                        
                                                              
                                                                                           

                                  
                                                      
                                                                                                      

                

                                                                           */
VOS_STATUS csrNeighborRoamReassocIndCallback(v_PVOID_t pAdapter, 
                               v_U8_t trafficStatus, 
                               v_PVOID_t pUserCtxt,
                               v_S7_t   avgRssi)
{
    tpAniSirGlobal pMac = PMAC_STRUCT( pUserCtxt );
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    VOS_STATUS vosStatus = VOS_STATUS_SUCCESS;   

    if (eSME_ROAM_TRIGGER_FAST_ROAM != pNeighborRoamInfo->cfgRoamEn)
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Deregistering DOWN event reassoc callback with TL. Threshold RSSI = %d Reported RSSI = %d"),
                         pNeighborRoamInfo->cfgParams.neighborReassocThreshold * (-1),
                         avgRssi);

        vosStatus = WLANTL_DeregRSSIIndicationCB(pMac->roam.gVosContext, (v_S7_t)pNeighborRoamInfo->cfgParams.neighborReassocThreshold * (-1),
                                                        WLANTL_HO_THRESHOLD_DOWN, 
                                                        csrNeighborRoamReassocIndCallback,
                                                        VOS_MODULE_ID_SME);
                        
        if(!VOS_IS_STATUS_SUCCESS(vosStatus))
        {
            //       
            smsLog(pMac, LOGW, FL(" Couldn't deregister csrNeighborRoamReassocIndCallback with TL: Status = %d"), vosStatus);
        }

        NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Rcvd reassoc notification-deregister UP indication. Threshold RSSI = %d Reported RSSI = %d"),
                            NEIGHBOR_ROAM_LOOKUP_UP_THRESHOLD * (-1), avgRssi);
        vosStatus = WLANTL_DeregRSSIIndicationCB(pMac->roam.gVosContext,
                           (v_S7_t)NEIGHBOR_ROAM_LOOKUP_UP_THRESHOLD * (-1),
                           WLANTL_HO_THRESHOLD_UP,
                           csrNeighborRoamNeighborLookupUPCallback,
                           VOS_MODULE_ID_SME);

       if(!VOS_IS_STATUS_SUCCESS(vosStatus))
       {
           //       
           smsLog(pMac, LOGW, FL(" Couldn't deregister csrNeighborRoamNeighborLookupUPCallback with TL: Status = %d"), vosStatus);
       }
    }
    /*                                          */
    vos_timer_stop(&pNeighborRoamInfo->neighborResultsRefreshTimer);
    vos_timer_stop(&pNeighborRoamInfo->emptyScanRefreshTimer);

    csrNeighborRoamTriggerHandoff(pMac, pNeighborRoamInfo);

    return VOS_STATUS_SUCCESS;
}

/*                */
static void csrNeighborRoamResetChannelInfo(tpCsrNeighborRoamChannelInfo rChInfo)
{
        if ((rChInfo->IAPPNeighborListReceived == FALSE) &&
                        (rChInfo->currentChannelListInfo.numOfChannels))
        {
                rChInfo->currentChanIndex = CSR_NEIGHBOR_ROAM_INVALID_CHANNEL_INDEX;
                rChInfo->currentChannelListInfo.numOfChannels = 0;

                if (rChInfo->currentChannelListInfo.ChannelList)
                        vos_mem_free(rChInfo->currentChannelListInfo.ChannelList);

                rChInfo->currentChannelListInfo.ChannelList = NULL;
                rChInfo->chanListScanInProgress = eANI_BOOLEAN_FALSE;
        }
        else 
        {
                rChInfo->currentChanIndex = 0;
                rChInfo->chanListScanInProgress = eANI_BOOLEAN_TRUE;
        }
}

static void csrNeighborRoamResetCfgListChanScanControlInfo(tpAniSirGlobal pMac)
{
        tpCsrNeighborRoamControlInfo pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

        /*                          */
        vos_timer_stop(&pNeighborRoamInfo->neighborScanTimer);

        /*                                          */
        vos_timer_stop(&pNeighborRoamInfo->neighborResultsRefreshTimer);

        /*                                       */
        vos_timer_stop(&pNeighborRoamInfo->emptyScanRefreshTimer);

        /*                        */
        if (eANI_BOOLEAN_TRUE == pNeighborRoamInfo->scanRspPending)
        {
            csrScanAbortMacScan(pMac, pNeighborRoamInfo->csrSessionId,
                                eCSR_SCAN_ABORT_DEFAULT);
        }
        pNeighborRoamInfo->scanRspPending = eANI_BOOLEAN_FALSE;

        /*                                     */
        csrNeighborRoamResetChannelInfo(&pNeighborRoamInfo->roamChannelInfo);
}

static void csrNeighborRoamResetPreauthControlInfo(tpAniSirGlobal pMac)
{
        tpCsrNeighborRoamControlInfo pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

#if  defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_ESE) || defined(FEATURE_WLAN_LFR)
        pNeighborRoamInfo->is11rAssoc = eANI_BOOLEAN_FALSE;
        /*                          */
        csrNeighborRoamPurgePreauthFailedList(pMac);
#endif

        pNeighborRoamInfo->FTRoamInfo.preauthRspPending = eANI_BOOLEAN_FALSE;
        pNeighborRoamInfo->FTRoamInfo.numPreAuthRetries = 0;
#ifdef WLAN_FEATURE_VOWIFI_11R
        /*                                           */
        pNeighborRoamInfo->FTRoamInfo.currentNeighborRptRetryNum = 0;
        pNeighborRoamInfo->FTRoamInfo.neighborRptPending = eANI_BOOLEAN_FALSE;
        pNeighborRoamInfo->FTRoamInfo.numBssFromNeighborReport = 0;
        vos_mem_zero(pNeighborRoamInfo->FTRoamInfo.neighboReportBssInfo, sizeof(tCsrNeighborReportBssInfo) * MAX_BSS_IN_NEIGHBOR_RPT);
#endif
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
    pNeighborRoamInfo->uOsRequestedHandoff = 0;
    vos_mem_zero(&pNeighborRoamInfo->handoffReqInfo, sizeof(tCsrHandoffRequest));
#endif

}

static void csrNeighborRoamDeregAllRssiIndication(tpAniSirGlobal pMac)
{
        tpCsrNeighborRoamControlInfo pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
        VOS_STATUS                    vosStatus = VOS_STATUS_SUCCESS;

        NEIGHBOR_ROAM_DEBUG(pMac, LOG2,
                        FL("Deregister neighbor lookup UP callback with TL. RSSI = %d"), 
                        NEIGHBOR_ROAM_LOOKUP_UP_THRESHOLD * (-1));

        /*                                                   */
        vosStatus = WLANTL_DeregRSSIIndicationCB(pMac->roam.gVosContext, 
                        (v_S7_t)NEIGHBOR_ROAM_LOOKUP_UP_THRESHOLD * (-1),
                        WLANTL_HO_THRESHOLD_UP, 
                        csrNeighborRoamNeighborLookupUPCallback,
                        VOS_MODULE_ID_SME);

        if(!VOS_IS_STATUS_SUCCESS(vosStatus))
        {
                smsLog(pMac, LOGW,
                                FL("Couldn't deregister csrNeighborRoamNeighborLookupUPCallback "
                                        "with TL: Status = %d"), vosStatus);
        }

        NEIGHBOR_ROAM_DEBUG(pMac, LOG2,
                        FL("Deregistering reassoc DOWN callback with TL. RSSI = %d"), 
                        pNeighborRoamInfo->cfgParams.neighborReassocThreshold * (-1));

        /*                                                   */
        vosStatus = WLANTL_DeregRSSIIndicationCB(pMac->roam.gVosContext, 
                        (v_S7_t)pNeighborRoamInfo->cfgParams.neighborReassocThreshold * (-1),
                        WLANTL_HO_THRESHOLD_DOWN, 
                        csrNeighborRoamReassocIndCallback,
                        VOS_MODULE_ID_SME);

        if(!VOS_IS_STATUS_SUCCESS(vosStatus))
        {
                smsLog(pMac, LOGW,
                                FL(" Couldn't deregister csrNeighborRoamReassocIndCallback with "
                                        "TL: Status = %d"), vosStatus);
        }

        NEIGHBOR_ROAM_DEBUG(pMac, LOG2,
                        FL("Deregistering neighborLookup DOWN callback with TL. RSSI = %d"), 
                        pNeighborRoamInfo->currentNeighborLookupThreshold * (-1));

        /*                                                           */
        vosStatus = WLANTL_DeregRSSIIndicationCB(pMac->roam.gVosContext, 
                        (v_S7_t)pNeighborRoamInfo->currentNeighborLookupThreshold * (-1),
                        WLANTL_HO_THRESHOLD_DOWN, 
                        csrNeighborRoamNeighborLookupDOWNCallback,
                        VOS_MODULE_ID_SME);

        if(!VOS_IS_STATUS_SUCCESS(vosStatus))
        {
                smsLog(pMac, LOGW,
                                FL(" Couldn't deregister csrNeighborRoamNeighborLookupDOWNCallback "
                                        "with TL: Status = %d"), vosStatus);
        }

        /*                                                              */
        pNeighborRoamInfo->currentNeighborLookupThreshold = 
                pNeighborRoamInfo->cfgParams.neighborLookupThreshold;
#ifdef FEATURE_WLAN_LFR
        pNeighborRoamInfo->uEmptyScanCount = 0;
        pNeighborRoamInfo->lookupDOWNRssi = 0;
        pNeighborRoamInfo->uScanMode = DEFAULT_SCAN;
#endif
}

/*                                                                            

                                                     

                                                                                     
                                                                                     
                                           

                                                  

                

                                                                           */
void csrNeighborRoamResetConnectedStateControlInfo(tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

    csrNeighborRoamResetChannelInfo(&pNeighborRoamInfo->roamChannelInfo);
    csrNeighborRoamFreeRoamableBSSList(pMac, &pNeighborRoamInfo->roamableAPList);
    
 /*                                          */
    vos_timer_stop(&pNeighborRoamInfo->neighborResultsRefreshTimer);
    vos_timer_stop(&pNeighborRoamInfo->emptyScanRefreshTimer);

#ifdef WLAN_FEATURE_VOWIFI_11R
    /*                                           */
    pNeighborRoamInfo->FTRoamInfo.currentNeighborRptRetryNum = 0;
    pNeighborRoamInfo->FTRoamInfo.neighborRptPending = eANI_BOOLEAN_FALSE;
    pNeighborRoamInfo->FTRoamInfo.numPreAuthRetries = 0;
    pNeighborRoamInfo->FTRoamInfo.numBssFromNeighborReport = 0;
    pNeighborRoamInfo->FTRoamInfo.preauthRspPending = 0;
    vos_mem_zero(pNeighborRoamInfo->FTRoamInfo.neighboReportBssInfo, sizeof(tCsrNeighborReportBssInfo) * MAX_BSS_IN_NEIGHBOR_RPT);
#endif
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
    pNeighborRoamInfo->uOsRequestedHandoff = 0;
    vos_mem_zero(&pNeighborRoamInfo->handoffReqInfo, sizeof(tCsrHandoffRequest));
#endif
}

void csrNeighborRoamResetReportScanStateControlInfo(tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    pNeighborRoamInfo->csrSessionId            =   CSR_SESSION_ID_INVALID;
    vos_mem_set(pNeighborRoamInfo->currAPbssid, sizeof(tCsrBssid), 0);
    pNeighborRoamInfo->neighborScanTimerInfo.pMac = pMac;
    pNeighborRoamInfo->neighborScanTimerInfo.sessionId = CSR_SESSION_ID_INVALID;
#ifdef FEATURE_WLAN_ESE
    pNeighborRoamInfo->isESEAssoc = eANI_BOOLEAN_FALSE;
    pNeighborRoamInfo->isVOAdmitted = eANI_BOOLEAN_FALSE;
    pNeighborRoamInfo->MinQBssLoadRequired = 0;
#endif

    /*                         */
    vos_timer_stop(&pNeighborRoamInfo->neighborResultsRefreshTimer);
    /*                                       */
    vos_timer_stop(&pNeighborRoamInfo->emptyScanRefreshTimer);
     /*                        */
       csrNeighborRoamFreeRoamableBSSList(pMac, &pNeighborRoamInfo->roamableAPList); 
    return;
}

/*                                                                            

                                                

                                                                                     
                                                                                     
                      

                                                  

                

                                                                           */
void csrNeighborRoamResetInitStateControlInfo(tpAniSirGlobal pMac)
{
    csrNeighborRoamResetConnectedStateControlInfo(pMac);

    /*                                                                                              */
    csrNeighborRoamResetReportScanStateControlInfo(pMac);
}



#ifdef WLAN_FEATURE_VOWIFI_11R
/*                                                                            

                                      

                                                                             
                                                                            
                                                                                     
                                                                                       
                                          

                                                  
                                                               

                                                                                  
                          

                                                                           */
static eHalStatus csrNeighborRoamBssIdScanFilter(tpAniSirGlobal pMac, tCsrScanResultFilter *pScanFilter)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tANI_U8 i = 0;

    VOS_ASSERT(pScanFilter != NULL);
    if (pScanFilter == NULL)
        return eHAL_STATUS_FAILURE;
    vos_mem_zero(pScanFilter, sizeof(tCsrScanResultFilter));

    pScanFilter->BSSIDs.numOfBSSIDs = pNeighborRoamInfo->FTRoamInfo.numBssFromNeighborReport;
    pScanFilter->BSSIDs.bssid = vos_mem_malloc(sizeof(tSirMacAddr) * pScanFilter->BSSIDs.numOfBSSIDs);
    if (NULL == pScanFilter->BSSIDs.bssid)
    {
        smsLog(pMac, LOGE, FL("Scan Filter BSSID mem alloc failed"));
        return eHAL_STATUS_FAILED_ALLOC;
    }

    vos_mem_zero(pScanFilter->BSSIDs.bssid, sizeof(tSirMacAddr) * pScanFilter->BSSIDs.numOfBSSIDs);

    /*                                                                         */
    for (i = 0; i < pScanFilter->BSSIDs.numOfBSSIDs; i++)
    {
        vos_mem_copy(&pScanFilter->BSSIDs.bssid[i], 
                pNeighborRoamInfo->FTRoamInfo.neighboReportBssInfo[i].neighborBssId, sizeof(tSirMacAddr));
    }

    /*                                       */
    return csrNeighborRoamPrepareScanProfileFilter(pMac, pScanFilter);
}

/*                                                                            

                                           

                                                       

                                                  

                

                                                                           */
void csrNeighborRoamPurgePreauthFailList(tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

    NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("Purging the preauth fail list"));
    while (pNeighborRoamInfo->FTRoamInfo.preAuthFailList.numMACAddress)
    {
        vos_mem_zero(pNeighborRoamInfo->FTRoamInfo.preAuthFailList.macAddress[pNeighborRoamInfo->FTRoamInfo.preAuthFailList.numMACAddress-1],
                                    sizeof(tSirMacAddr));
        pNeighborRoamInfo->FTRoamInfo.preAuthFailList.numMACAddress--;
    }
    return;
}

/*                                                                            

                                                

                                                                       

                                                  
                                                              

                                                                         

                                                                           */
eHalStatus csrNeighborRoamAddBssIdToPreauthFailList(tpAniSirGlobal pMac, tSirMacAddr bssId)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

    NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL(" Added BSSID "MAC_ADDRESS_STR" to Preauth failed list"),
                        MAC_ADDR_ARRAY(bssId));


    if ((pNeighborRoamInfo->FTRoamInfo.preAuthFailList.numMACAddress + 1) >
            MAX_NUM_PREAUTH_FAIL_LIST_ADDRESS)
    {
        smsLog(pMac, LOGE, FL("Preauth fail list already full.. Cannot add new one"));
        return eHAL_STATUS_FAILURE;
    }
    vos_mem_copy(pNeighborRoamInfo->FTRoamInfo.preAuthFailList.macAddress[
                  pNeighborRoamInfo->FTRoamInfo.preAuthFailList.numMACAddress],
                 bssId,
                 sizeof(tSirMacAddr));
    pNeighborRoamInfo->FTRoamInfo.preAuthFailList.numMACAddress++;
    
    return eHAL_STATUS_SUCCESS;
}

/*                                                                            

                                         

                                                                          
                                                                               

                                                  

                                                                                

                                                                           */
tANI_BOOLEAN csrNeighborRoamIsPreauthCandidate(tpAniSirGlobal pMac, tSirMacAddr bssId)
{
    tANI_U8 i = 0;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
    if (csrRoamIsRoamOffloadScanEnabled(pMac))
    {
        return eANI_BOOLEAN_TRUE;
    }
#endif
    if (0 == pNeighborRoamInfo->FTRoamInfo.preAuthFailList.numMACAddress)
        return eANI_BOOLEAN_TRUE;
    
    for (i = 0; i < pNeighborRoamInfo->FTRoamInfo.preAuthFailList.numMACAddress; i++)
    {
        if (VOS_TRUE == vos_mem_compare(pNeighborRoamInfo->FTRoamInfo.preAuthFailList.macAddress[i],
                                                                        bssId, sizeof(tSirMacAddr)))
        {
            NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("BSSID "MAC_ADDRESS_STR" already present in preauth fail list"),
                                                MAC_ADDR_ARRAY(bssId));
            return eANI_BOOLEAN_FALSE;
        }
    }

    return eANI_BOOLEAN_TRUE;
}

/*                                                                            

                                      

                                                                                    
                            

                                                  

                                                                         

                                                                           */
static eHalStatus csrNeighborRoamIssuePreauthReq(tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus status = eHAL_STATUS_SUCCESS;
    tpCsrNeighborRoamBSSInfo    pNeighborBssNode;

#ifdef FEATURE_WLAN_LFR_METRICS
    tCsrRoamInfo *roamInfo;
#endif
    
    /*                            */
    VOS_ASSERT(pNeighborRoamInfo->FTRoamInfo.preauthRspPending == eANI_BOOLEAN_FALSE);

    /*                                  */
    /*                                                                                                    */
    /*                                                                                                 */
    /*                                                                      */
    pNeighborBssNode = csrNeighborRoamGetRoamableAPListNextEntry(pMac, &pNeighborRoamInfo->roamableAPList, NULL);

    if (NULL == pNeighborBssNode)
    {
        smsLog(pMac, LOGW, FL("Roamable AP list is empty.. "));
        return eHAL_STATUS_FAILURE;
    }
    else
    {
#ifdef FEATURE_WLAN_LFR_METRICS
        /*                                          
                                                                    */
        roamInfo = vos_mem_malloc(sizeof(tCsrRoamInfo));
        if (NULL == roamInfo)
        {
            smsLog(pMac, LOG1, FL("Memory allocation failed!"));
        }
        else
        {
            vos_mem_copy((void *)roamInfo->bssid,
                (void *)pNeighborBssNode->pBssDescription->bssId,
                sizeof(tCsrBssid));
            csrRoamCallCallback(pMac, pNeighborRoamInfo->csrSessionId,
                                roamInfo, 0, eCSR_ROAM_PREAUTH_INIT_NOTIFY, 0);
            vos_mem_free(roamInfo);
        }
#endif

        status = csrRoamEnqueuePreauth(pMac, pNeighborRoamInfo->csrSessionId, pNeighborBssNode->pBssDescription,
                eCsrPerformPreauth, eANI_BOOLEAN_TRUE);

        smsLog(pMac, LOG1, FL("Before Pre-Auth: BSSID "MAC_ADDRESS_STR", Ch:%d"),
               MAC_ADDR_ARRAY(pNeighborBssNode->pBssDescription->bssId),
               (int)pNeighborBssNode->pBssDescription->channelId);

        if (eHAL_STATUS_SUCCESS != status)
        {
            smsLog(pMac, LOGE, FL("Send Preauth request to PE failed with status %d"), status);
            return status;
        }
    }
    
    pNeighborRoamInfo->FTRoamInfo.preauthRspPending = eANI_BOOLEAN_TRUE;

    /*                                   */
    pNeighborRoamInfo->FTRoamInfo.numPreAuthRetries++;
    
    /*                                           */
    CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_PREAUTHENTICATING)
    
    return status;
}

/*                                                                            

                                        

                                                             
                                                                                
                                                                             
                                                                                            
                                                
                                                             

                                                  
                                                                                 
                                                             

                                                                     
                                         

                                                                           */
eHalStatus csrNeighborRoamPreauthRspHandler(tpAniSirGlobal pMac, tSirRetStatus limStatus)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus  status = eHAL_STATUS_SUCCESS;
    VOS_STATUS  vosStatus = VOS_STATUS_SUCCESS;
    eHalStatus  preauthProcessed = eHAL_STATUS_SUCCESS;
    tpCsrNeighborRoamBSSInfo pPreauthRspNode = NULL;

#ifdef FEATURE_WLAN_LFR_METRICS
    tCsrRoamInfo *roamInfo;
#endif

    if (eANI_BOOLEAN_FALSE == pNeighborRoamInfo->FTRoamInfo.preauthRspPending)
    {
            
            /*                                               
                                                                  
                                                             
                                                                
             */
            NEIGHBOR_ROAM_DEBUG(pMac, LOGW,
                                FL("Unexpected pre-auth response in state %d"),
                                pNeighborRoamInfo->neighborRoamState);
            preauthProcessed = eHAL_STATUS_FAILURE;
            goto DEQ_PREAUTH;
    }    

    //                                     
    if ((pNeighborRoamInfo->neighborRoamState != eCSR_NEIGHBOR_ROAM_STATE_PREAUTHENTICATING) &&
        (pNeighborRoamInfo->neighborRoamState != eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN))
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGW,
        FL("Preauth response received in state %s"),
        macTraceGetNeighbourRoamState(
        pNeighborRoamInfo->neighborRoamState));
        preauthProcessed = eHAL_STATUS_FAILURE;
        goto DEQ_PREAUTH;
    }

    pNeighborRoamInfo->FTRoamInfo.preauthRspPending = eANI_BOOLEAN_FALSE;

    if (eSIR_SUCCESS == limStatus)
    {
        pPreauthRspNode = csrNeighborRoamGetRoamableAPListNextEntry(pMac, &pNeighborRoamInfo->roamableAPList, NULL);
    }
    if ((eSIR_SUCCESS == limStatus) && (NULL != pPreauthRspNode))
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOG1, FL("Preauth completed successfully after %d tries"), pNeighborRoamInfo->FTRoamInfo.numPreAuthRetries);

        smsLog(pMac, LOG1, FL("After Pre-Auth: BSSID "MAC_ADDRESS_STR", Ch:%d"),
               MAC_ADDR_ARRAY(pPreauthRspNode->pBssDescription->bssId),
               (int)pPreauthRspNode->pBssDescription->channelId);

#ifdef FEATURE_WLAN_LFR_METRICS
        /*                                          
                                                                             */
        roamInfo = vos_mem_malloc(sizeof(tCsrRoamInfo));
        if (NULL == roamInfo)
        {
            smsLog(pMac, LOG1, FL("Memory allocation failed!"));
        }
        else
        {
            vos_mem_copy((void *)roamInfo->bssid,
                (void *)pPreauthRspNode->pBssDescription->bssId,
                sizeof(tCsrBssid));
            csrRoamCallCallback(pMac, pNeighborRoamInfo->csrSessionId,
                roamInfo, 0, eCSR_ROAM_PREAUTH_STATUS_SUCCESS, 0);
            vos_mem_free(roamInfo);
        }
#endif

        /*                                                                                            */
        csrNeighborRoamRemoveRoamableAPListEntry(pMac, &pNeighborRoamInfo->roamableAPList, pPreauthRspNode);
        csrLLInsertTail(&pNeighborRoamInfo->FTRoamInfo.preAuthDoneList, &pPreauthRspNode->List, LL_ACCESS_LOCK);

        /*                                                                   */
        CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_PREAUTH_DONE)
        pNeighborRoamInfo->FTRoamInfo.numPreAuthRetries = 0;

        /*                                                                                               
                                                                                                       */
    }
    else
    {
        tpCsrNeighborRoamBSSInfo    pNeighborBssNode = NULL;
        tListElem                   *pEntry;

        smsLog(pMac, LOGE, FL("Preauth failed retry number %d, status = 0x%x"),
               pNeighborRoamInfo->FTRoamInfo.numPreAuthRetries, limStatus);
        
        /*                                                                                                                */
        if ((pNeighborRoamInfo->FTRoamInfo.numPreAuthRetries >=
             CSR_NEIGHBOR_ROAM_MAX_NUM_PREAUTH_RETRIES) ||
            (eSIR_LIM_MAX_STA_REACHED_ERROR == limStatus))
        {
            /*                                                                                            */
            pNeighborRoamInfo->FTRoamInfo.numPreAuthRetries = 0;

            /*                                                                                        */
            pEntry = csrLLRemoveHead(&pNeighborRoamInfo->roamableAPList, LL_ACCESS_LOCK);
            if(pEntry)
            {
                pNeighborBssNode = GET_BASE_ADDR(pEntry, tCsrNeighborRoamBSSInfo, List);
                /*                                                                   */
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
                if(!pNeighborRoamInfo->uOsRequestedHandoff)
#endif
                {
            status = csrNeighborRoamAddBssIdToPreauthFailList(pMac, pNeighborBssNode->pBssDescription->bssId);
                }

#ifdef FEATURE_WLAN_LFR_METRICS
                /*                                                         
                                                                      */
                roamInfo = vos_mem_malloc(sizeof(tCsrRoamInfo));
                if (NULL == roamInfo)
                {
                    smsLog(pMac, LOG1, FL("Memory allocation failed!"));
                }
                else
                {
                    vos_mem_copy((void *)roamInfo->bssid,
                        (void *)pNeighborBssNode->pBssDescription->bssId,
                        sizeof(tCsrBssid));
                    csrRoamCallCallback(pMac, pNeighborRoamInfo->csrSessionId,
                        roamInfo, 0, eCSR_ROAM_PREAUTH_STATUS_FAILURE, 0);
                    vos_mem_free(roamInfo);
                }
#endif

            /*                           */
            csrNeighborRoamFreeNeighborRoamBSSNode(pMac, pNeighborBssNode);
            }
        }

        /*                                               */
        if (eHAL_STATUS_SUCCESS == csrNeighborRoamIssuePreauthReq(pMac))
        goto DEQ_PREAUTH; 

#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        if (csrRoamIsRoamOffloadScanEnabled(pMac))
        {
          if(pNeighborRoamInfo->uOsRequestedHandoff)
          {
             pNeighborRoamInfo->uOsRequestedHandoff = 0;
             csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_START, REASON_PREAUTH_FAILED_FOR_ALL);
          }
          else
          {
             csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_RESTART, REASON_PREAUTH_FAILED_FOR_ALL);
          }
          CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_CONNECTED);
        } else
        {
#endif
          CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN);

          /*                                                                      */
          NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("No more pre-auth candidates-"
                  "register UP indication with TL. RSSI = %d,"), NEIGHBOR_ROAM_LOOKUP_UP_THRESHOLD * (-1));

          vosStatus = WLANTL_RegRSSIIndicationCB(pMac->roam.gVosContext,
                              (v_S7_t)NEIGHBOR_ROAM_LOOKUP_UP_THRESHOLD * (-1),
                              WLANTL_HO_THRESHOLD_UP,
                              csrNeighborRoamNeighborLookupUPCallback,
                              VOS_MODULE_ID_SME, pMac);
          if(!VOS_IS_STATUS_SUCCESS(vosStatus))
          {
              //       
              smsLog(pMac, LOGE, FL(" Couldn't register csrNeighborRoamNeighborLookupCallback UP event with TL: Status = %d"), status);
          }

          /*                                                                                                    */
          status = vos_timer_start(&pNeighborRoamInfo->neighborResultsRefreshTimer,
                          pNeighborRoamInfo->cfgParams.neighborResultsRefreshPeriod);
          if ( status != eHAL_STATUS_SUCCESS )
          {
             smsLog(pMac, LOGE, FL("Neighbor results refresh timer start failed with status %d"), status);
          }
        }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
    }
#endif

DEQ_PREAUTH:
    csrRoamDequeuePreauth(pMac);
    return preauthProcessed;
}
#endif  /*                               */

/*                                                                            

                                               

                                                                                         
                                                           

                                                  
                                                                              

                                                                         

                                                                           */
eHalStatus csrNeighborRoamPrepareScanProfileFilter(tpAniSirGlobal pMac, tCsrScanResultFilter *pScanFilter)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tANI_U8 sessionId   = (tANI_U8)pNeighborRoamInfo->csrSessionId;
    tCsrRoamConnectedProfile *pCurProfile = &pMac->roam.roamSession[sessionId].connectedProfile;
    tANI_U8 i = 0;
    
    VOS_ASSERT(pScanFilter != NULL);
    if (pScanFilter == NULL)
        return eHAL_STATUS_FAILURE;

    vos_mem_zero(pScanFilter, sizeof(tCsrScanResultFilter));

    /*                                        */
    pScanFilter->BSSIDs.numOfBSSIDs = 0;

    //                                                              
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
    if (pNeighborRoamInfo->uOsRequestedHandoff)
    {
        pScanFilter->BSSIDs.numOfBSSIDs = 1;
        pScanFilter->BSSIDs.bssid = vos_mem_malloc(sizeof(tSirMacAddr) * pScanFilter->BSSIDs.numOfBSSIDs);
        if (NULL == pScanFilter->BSSIDs.bssid)
        {
            smsLog(pMac, LOGE, FL("Scan Filter BSSID mem alloc failed"));
            return eHAL_STATUS_FAILED_ALLOC;
        }

        vos_mem_zero(pScanFilter->BSSIDs.bssid, sizeof(tSirMacAddr) * pScanFilter->BSSIDs.numOfBSSIDs);

        /*                                                        */
        for (i = 0; i < pScanFilter->BSSIDs.numOfBSSIDs; i++)
        {
            vos_mem_copy(&pScanFilter->BSSIDs.bssid[i],
                         pNeighborRoamInfo->handoffReqInfo.bssid, sizeof(tSirMacAddr));
        }
    }
#endif
    /*                                                         */
    pScanFilter->SSIDs.numOfSSIDs = 1;  
    pScanFilter->SSIDs.SSIDList = vos_mem_malloc(sizeof(tCsrSSIDInfo));
    if (NULL == pScanFilter->SSIDs.SSIDList)
    {
        smsLog(pMac, LOGE, FL("Scan Filter SSID mem alloc failed"));
        return eHAL_STATUS_FAILED_ALLOC;
    }
    pScanFilter->SSIDs.SSIDList->handoffPermitted = 1;
    pScanFilter->SSIDs.SSIDList->ssidHidden = 0;
    pScanFilter->SSIDs.SSIDList->SSID.length =  pCurProfile->SSID.length;
    vos_mem_copy((void *)pScanFilter->SSIDs.SSIDList->SSID.ssId, (void *)pCurProfile->SSID.ssId, pCurProfile->SSID.length); 

    NEIGHBOR_ROAM_DEBUG(pMac, LOG1, FL("Filtering for SSID %.*s from scan results,"
                                "length of SSID = %u"),
                                pScanFilter->SSIDs.SSIDList->SSID.length,
                                pScanFilter->SSIDs.SSIDList->SSID.ssId,
                                pScanFilter->SSIDs.SSIDList->SSID.length);
    pScanFilter->authType.numEntries = 1;
    pScanFilter->authType.authType[0] = pCurProfile->AuthType;

    pScanFilter->EncryptionType.numEntries = 1; //              
    pScanFilter->EncryptionType.encryptionType[0] = pCurProfile->EncryptionType;

    pScanFilter->mcEncryptionType.numEntries = 1;
    pScanFilter->mcEncryptionType.encryptionType[0] = pCurProfile->mcEncryptionType;

    pScanFilter->BSSType = pCurProfile->BSSType;

    /*                                                                        */
    pScanFilter->ChannelInfo.numOfChannels = pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels;
    pScanFilter->ChannelInfo.ChannelList = vos_mem_malloc(pScanFilter->ChannelInfo.numOfChannels * sizeof(tANI_U8));
    if (NULL == pScanFilter->ChannelInfo.ChannelList)
    {
        smsLog(pMac, LOGE, FL("Scan Filter Channel list mem alloc failed"));
        vos_mem_free(pScanFilter->SSIDs.SSIDList);
        pScanFilter->SSIDs.SSIDList = NULL;
        return eHAL_STATUS_FAILED_ALLOC;
    }
    for (i = 0; i < pScanFilter->ChannelInfo.numOfChannels; i++)
    {
        pScanFilter->ChannelInfo.ChannelList[i] = pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList[i];
    }

#ifdef WLAN_FEATURE_VOWIFI_11R
    if (pNeighborRoamInfo->is11rAssoc)
    {
        /*                                                                                              */
        pScanFilter->MDID.mdiePresent = pCurProfile->MDID.mdiePresent;
        pScanFilter->MDID.mobilityDomain = pCurProfile->MDID.mobilityDomain;
    }
#endif

    return eHAL_STATUS_SUCCESS;
}

tANI_U32 csrGetCurrentAPRssi(tpAniSirGlobal pMac, tScanResultHandle *pScanResultList)
{
        tCsrScanResultInfo *pScanResult;
        tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
#ifdef FEATURE_WLAN_LFR
        tANI_U32 CurrAPRssi = pNeighborRoamInfo->lookupDOWNRssi;
#else
        /*                                                                        
                                                                                   
                                                                                       */
        tANI_U32 CurrAPRssi = -125;
#endif

        while (NULL != (pScanResult = csrScanResultGetNext(pMac, *pScanResultList)))
        {

                if (VOS_TRUE == vos_mem_compare(pScanResult->BssDescriptor.bssId,
                                                pNeighborRoamInfo->currAPbssid, sizeof(tSirMacAddr)))
                {
                        /*                                                 
                                                                              
                                                                                                          
                                                                                                              
                                                                                                                      */

                         CurrAPRssi = (int)pScanResult->BssDescriptor.rssi * (-1) ;

                } else {
                        continue;
                }
        }

        return CurrAPRssi;

}

/*                                                                            

                                         

                                                                                             
                                                                                   

                                                  
                                                                                 

                                                                                
                                             

                                                                           */

static tANI_BOOLEAN csrNeighborRoamProcessScanResults(tpAniSirGlobal pMac, 
                                                      tScanResultHandle *pScanResultList)
{
    tCsrScanResultInfo *pScanResult;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tpCsrNeighborRoamBSSInfo    pBssInfo;
    tANI_U32 CurrAPRssi;
    tANI_U8 RoamRssiDiff = pMac->roam.configParam.RoamRssiDiff;
#if  defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_ESE) || defined(FEATURE_WLAN_LFR)
    tANI_U8 immediateRoamRssiDiff = pMac->roam.configParam.nImmediateRoamRssiDiff;
#endif
    tANI_BOOLEAN roamNow = eANI_BOOLEAN_FALSE;

    /*                                                              
                                                                 
                                                        
                                                             
                  
                                                                   */
    CurrAPRssi = csrGetCurrentAPRssi(pMac, pScanResultList);

    /*                                                                               */
    /*                                                                                                                               */
    /*                                                                                                                
                                                                                                    */
    /*                                                                                                                                     
                                                                           */

    while (NULL != (pScanResult = csrScanResultGetNext(pMac, *pScanResultList)))
    {
            VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_DEBUG,
            FL("Scan result: BSSID "MAC_ADDRESS_STR" (Rssi %ld, Ch:%d)"),
            MAC_ADDR_ARRAY(pScanResult->BssDescriptor.bssId),
            abs(pScanResult->BssDescriptor.rssi),
            pScanResult->BssDescriptor.channelId);

       if ((VOS_TRUE == vos_mem_compare(pScanResult->BssDescriptor.bssId,
           pNeighborRoamInfo->currAPbssid, sizeof(tSirMacAddr))) ||
           ((eSME_ROAM_TRIGGER_SCAN == pNeighborRoamInfo->cfgRoamEn) &&
           (VOS_TRUE != vos_mem_compare(pScanResult->BssDescriptor.bssId,
                        pNeighborRoamInfo->cfgRoambssId, sizeof(tSirMacAddr)))))
        {
            /*                                                                   */
            VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                    "SKIP-currently associated AP");
            continue;
        }

#ifdef FEATURE_WLAN_LFR
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
       /*                                                                                      
                                         */
       if ((pNeighborRoamInfo->uOsRequestedHandoff) &&
           ((VOS_FALSE == vos_mem_compare(pScanResult->BssDescriptor.bssId,
                                         pNeighborRoamInfo->handoffReqInfo.bssid,
                                         sizeof(tSirMacAddr)))||
            (pScanResult->BssDescriptor.channelId != pNeighborRoamInfo->handoffReqInfo.channel)))

       {
           VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                      "SKIP-not a candidate AP for OS requested roam");
           continue;
       }
#endif
#endif

#ifdef FEATURE_WLAN_LFR
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
       if (pNeighborRoamInfo->isForcedInitialRoamTo5GH)
       {
            //                                                                               
            //                                                                      
            //                
            if(GetRFBand(pScanResult->BssDescriptor.channelId) != SIR_BAND_5_GHZ)
            {
                VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                           "%s: Forced Roam to 5G Skip Non 5G Scan results ", __func__);
                continue;
            }

            //                                                  
            //                                                 
            //                                                     
            if (abs(pScanResult->BssDescriptor.rssi) > abs(CurrAPRssi) &&
               ((abs(pScanResult->BssDescriptor.rssi) - abs(CurrAPRssi))
                > pMac->roam.configParam.nSelect5GHzMargin)
               )
            {
                VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                      "%s: Forced Roam to 5G Current AP rssi=%d new ap rssi=%d not good enough, nSelect5GHzMargin=%d", __func__,
                      CurrAPRssi,
                      (int)pScanResult->BssDescriptor.rssi * (-1),
                      pMac->roam.configParam.nSelect5GHzMargin);
                continue;
            }

       }
#endif
#endif

       /*                                                                                                                  
                                                               */
       if ((RoamRssiDiff > 0)
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
       && !csrRoamIsRoamOffloadScanEnabled(pMac)
#endif
       && ((eSME_ROAM_TRIGGER_SCAN != pNeighborRoamInfo->cfgRoamEn) ||
           (eSME_ROAM_TRIGGER_FAST_ROAM != pNeighborRoamInfo->cfgRoamEn)))
       {
               /*
                                                                           
               */
               if (abs(pScanResult->BssDescriptor.rssi) >
                   pNeighborRoamInfo->currentNeighborLookupThreshold)
               {
                    VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                    "%s: [INFOLOG] new ap rssi (%d) lower than lookup threshold (%d)",
                    __func__, (int)pScanResult->BssDescriptor.rssi * (-1),
                    (int)pNeighborRoamInfo->currentNeighborLookupThreshold * (-1));
                    continue;
               }

               if (abs(CurrAPRssi) < abs(pScanResult->BssDescriptor.rssi))
               {
                       /*                                                     */
                       VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                                 "%s: [INFOLOG]Current AP rssi=%d new ap rssi worse=%d", __func__,
                                 CurrAPRssi,
                                 (int)pScanResult->BssDescriptor.rssi * (-1) );
                       continue;
               } else {
                       /*                                                                                             
                                                                                          */
                       if (abs(abs(CurrAPRssi) - abs(pScanResult->BssDescriptor.rssi)) < RoamRssiDiff)
                       {
                           VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                                 "%s: [INFOLOG]Current AP rssi=%d new ap rssi=%d not good enough, roamRssiDiff=%d", __func__,
                                 CurrAPRssi,
                                 (int)pScanResult->BssDescriptor.rssi * (-1),
                                 RoamRssiDiff);
                          continue;
                       }
                       else {
                                 VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                                            "%s: [INFOLOG]Current AP rssi=%d new ap rssi better=%d", __func__,
                                            CurrAPRssi,
                                            (int)pScanResult->BssDescriptor.rssi * (-1) );
                       }
               }
       }

#ifdef WLAN_FEATURE_VOWIFI_11R
        if (pNeighborRoamInfo->is11rAssoc)
        {
            if (!csrNeighborRoamIsPreauthCandidate(pMac, pScanResult->BssDescriptor.bssId))
            {
                smsLog(pMac, LOGE, FL("BSSID present in pre-auth fail list.. Ignoring"));
                continue;
            }
        }
#endif /*                         */

#ifdef FEATURE_WLAN_ESE
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        if (!csrRoamIsRoamOffloadScanEnabled(pMac))
        {
#endif
          if (pNeighborRoamInfo->isESEAssoc)
          {
              if (!csrNeighborRoamIsPreauthCandidate(pMac, pScanResult->BssDescriptor.bssId))
              {
                  smsLog(pMac, LOGE, FL("BSSID present in pre-auth fail list.. Ignoring"));
                  continue;
              }
          }
          if ((pScanResult->BssDescriptor.QBSSLoad_present) &&
               (pScanResult->BssDescriptor.QBSSLoad_avail))
          {
              if (pNeighborRoamInfo->isVOAdmitted)
              {
                  smsLog(pMac, LOG1, FL("New AP has %x BW available"), (unsigned int)pScanResult->BssDescriptor.QBSSLoad_avail);
                  smsLog(pMac, LOG1, FL("We need %x BW available"),(unsigned int)pNeighborRoamInfo->MinQBssLoadRequired);
                  if (pScanResult->BssDescriptor.QBSSLoad_avail < pNeighborRoamInfo->MinQBssLoadRequired)
                  {
                      VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                          "[INFOLOG]BSSID : "MAC_ADDRESS_STR" has no bandwidth ignoring..not adding to roam list",
                          MAC_ADDR_ARRAY(pScanResult->BssDescriptor.bssId));
                      continue;
                  }
              }
          }
          else
          {
              smsLog(pMac, LOGE, FL("No QBss %x %x"), (unsigned int)pScanResult->BssDescriptor.QBSSLoad_avail, (unsigned int)pScanResult->BssDescriptor.QBSSLoad_present);
              if (pNeighborRoamInfo->isVOAdmitted)
              {
                  VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                      "[INFOLOG]BSSID : "MAC_ADDRESS_STR" has no QBSSLoad IE, ignoring..not adding to roam list",
                      MAC_ADDR_ARRAY(pScanResult->BssDescriptor.bssId));
                  continue;
              }
          }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        }
#endif
#endif /*                  */

#ifdef FEATURE_WLAN_LFR
        //                                          
        //                                                               
        if (csrRoamIsFastRoamEnabled(pMac, CSR_SESSION_ID_INVALID))
        {
            if (!csrNeighborRoamIsPreauthCandidate(pMac, pScanResult->BssDescriptor.bssId))
            {
                smsLog(pMac, LOGE, FL("BSSID present in pre-auth fail list.. Ignoring"));
                continue;
            }
        }
#endif /*                  */

        /*                                                                                               
                       */
        if ((pNeighborRoamInfo->scanRequestTimeStamp >= pScanResult->BssDescriptor.nReceivedTime)
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            && !csrRoamIsRoamOffloadScanEnabled(pMac)
#endif
        )
        {
            smsLog(pMac, LOGE, FL("Ignoring BSS as it is older than the scan request timestamp"));
            continue;
        }

        pBssInfo = vos_mem_malloc(sizeof(tCsrNeighborRoamBSSInfo));
        if (NULL == pBssInfo)
        {
            smsLog(pMac, LOGE, FL("Memory allocation for Neighbor Roam BSS Info failed.. Just ignoring"));
            continue;
        }

        pBssInfo->pBssDescription = vos_mem_malloc(pScanResult->BssDescriptor.length + sizeof(pScanResult->BssDescriptor.length));
        if (pBssInfo->pBssDescription != NULL)
        {
            vos_mem_copy(pBssInfo->pBssDescription, &pScanResult->BssDescriptor, 
                    pScanResult->BssDescriptor.length + sizeof(pScanResult->BssDescriptor.length));
        }
        else
        {
            smsLog(pMac, LOGE, FL("Memory allocation for Neighbor Roam BSS Descriptor failed.. Just ignoring"));
            vos_mem_free(pBssInfo);
            continue;
            
        }
        pBssInfo->apPreferenceVal = 10; //                                                                                          

        /*                                                                 */
        csrLLInsertTail(&pNeighborRoamInfo->roamableAPList, &pBssInfo->List, LL_ACCESS_LOCK);

#if  defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_ESE) || defined(FEATURE_WLAN_LFR)
        if ((eSME_ROAM_TRIGGER_SCAN == pNeighborRoamInfo->cfgRoamEn) ||
            (eSME_ROAM_TRIGGER_FAST_ROAM == pNeighborRoamInfo->cfgRoamEn))
        {
           roamNow = eANI_BOOLEAN_FALSE;
        }
        else if ((abs(abs(CurrAPRssi) - abs(pScanResult->BssDescriptor.rssi)) >= immediateRoamRssiDiff)
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            && !csrRoamIsRoamOffloadScanEnabled(pMac)
#endif
        )
        {
            VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                       "%s: [INFOLOG] potential candidate to roam immediately (diff=%ld, expected=%d)",
                       __func__, abs(abs(CurrAPRssi) - abs(pScanResult->BssDescriptor.rssi)),
                       immediateRoamRssiDiff);
            roamNow = eANI_BOOLEAN_TRUE;
        }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        /*                                                                     
                                    */
        if(csrRoamIsRoamOffloadScanEnabled(pMac))
        {
            roamNow = eANI_BOOLEAN_TRUE;
        }
#endif
#endif
    }

    /*                                                                                                                            */
    csrScanResultPurge(pMac, *pScanResultList);

    return roamNow;
}

/*                                                                            

                                            

                                                                               
                                                                                  
                                                                                  
                                                               
                                                
                                                                             
                                                                   
                                                                              
                                                                     
                                             
                                                                            
                                                                        
                                                                           
                                                                            
                                                                         
                                                                             
                                                                                  
                                                  

                                                                
                                                                             
                                                                                   
                                                                                
                                                                              
                                                                             
                                                                                      
                                                                                 
                                                                   
                                                                             
                                                                                     
                                                                                       
                                                                                   
                                               
                                                                             
                                                                                      
                                                                      
                                                                            
                                                                             
                                                                                     
                                                                                       
                                                                                   
                                               

                                                                                  

                                                  

                                                                             

                                                                           */
static VOS_STATUS csrNeighborRoamHandleEmptyScanResult(tpAniSirGlobal pMac)
{
    VOS_STATUS  vosStatus = VOS_STATUS_SUCCESS;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus  status = eHAL_STATUS_SUCCESS;
#ifdef FEATURE_WLAN_LFR
    tANI_BOOLEAN performPeriodicScan =
        (pNeighborRoamInfo->cfgParams.emptyScanRefreshPeriod) ? TRUE : FALSE;
#endif

    /*                          */
    vos_timer_stop(&pNeighborRoamInfo->neighborScanTimer);
    /*
                                                     
                                                    
                                                    
                  
     */
#ifdef FEATURE_WLAN_LFR
    if ((++pNeighborRoamInfo->uEmptyScanCount) > eFifthEmptyScan)
    {
        pNeighborRoamInfo->uEmptyScanCount = eFifthEmptyScan;
    }
    if (((0 != pNeighborRoamInfo->cfgParams.channelInfo.numOfChannels) ||
         (abs(pNeighborRoamInfo->lookupDOWNRssi) >
         abs(pNeighborRoamInfo->cfgParams.neighborReassocThreshold))) &&
        ((pNeighborRoamInfo->uEmptyScanCount == eSecondEmptyScan) ||
         (pNeighborRoamInfo->uEmptyScanCount == eFourthEmptyScan)))
    {
        /*
                                                                               
                                                                            
                                                                           
                         
                                                                             
                                                                             
                                                                             
                                                                              
                                                                              
                                          
         */
        ++pNeighborRoamInfo->uEmptyScanCount;
        NEIGHBOR_ROAM_DEBUG(pMac, LOG2, "Extra increment of empty scan count (=%d)"
            " in contiguous scan mode", pNeighborRoamInfo->uEmptyScanCount);
    }
#endif
    if (((pNeighborRoamInfo->currentNeighborLookupThreshold+3) <
        pNeighborRoamInfo->cfgParams.neighborReassocThreshold)
#ifdef FEATURE_WLAN_LFR
        && ((pNeighborRoamInfo->uEmptyScanCount % 2) == 1)
#endif
        )
    {
        pNeighborRoamInfo->currentNeighborLookupThreshold += 3;
    }

#ifdef WLAN_FEATURE_VOWIFI_11R
    /*                                           */
    vos_mem_zero(&pNeighborRoamInfo->FTRoamInfo.neighboReportBssInfo, sizeof(tCsrNeighborReportBssInfo) * MAX_BSS_IN_NEIGHBOR_RPT);
#endif

    /*                               */
    CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_CONNECTED);
        
    /*                                                                               */
    csrNeighborRoamResetConnectedStateControlInfo(pMac);
        
#ifdef FEATURE_WLAN_LFR
    if (pNeighborRoamInfo->uEmptyScanCount == eFirstEmptyScan)
    {
#endif
        /*                                       */
        /*                                                             */
        NEIGHBOR_ROAM_DEBUG(pMac, LOGE,
            FL("Registering DOWN event neighbor lookup callback with TL for RSSI = %d"),
            pNeighborRoamInfo->currentNeighborLookupThreshold * (-1));

        vosStatus = WLANTL_RegRSSIIndicationCB(pMac->roam.gVosContext,
                        (v_S7_t)pNeighborRoamInfo->currentNeighborLookupThreshold * (-1),
                        WLANTL_HO_THRESHOLD_DOWN,
                        csrNeighborRoamNeighborLookupDOWNCallback,
                        VOS_MODULE_ID_SME, pMac);

        if(!VOS_IS_STATUS_SUCCESS(vosStatus))
        {
            smsLog(pMac, LOGW,
                   FL("Couldn't re-register csrNeighborRoamNeighborLookupDOWNCallback"
                      " with TL: Status = %d"), status);
        }
#ifdef FEATURE_WLAN_LFR
        pNeighborRoamInfo->lookupDOWNRssi = 0;
    }
    else if ((pNeighborRoamInfo->uEmptyScanCount == eSecondEmptyScan) ||
             (pNeighborRoamInfo->uEmptyScanCount == eFourthEmptyScan))
    {
        /*                                                  */

        /*                                                   */
        csrNeighborRoamTransitToCFGChanScan(pMac);
    }
    else if (pNeighborRoamInfo->uEmptyScanCount >= eThirdEmptyScan)
    {
        /*                                       */
        if (performPeriodicScan)
        {
            smsLog(pMac, LOGE, FL("Performing periodic scan, uEmptyScanCount=%d"),
                   pNeighborRoamInfo->uEmptyScanCount);

            /*
                                                                      
                                                         
             */
            pNeighborRoamInfo->uEmptyScanCount = eMaxEmptyScan;

            /*                                                          */
            pNeighborRoamInfo->uScanMode = SPLIT_SCAN_OCCUPIED_LIST;

            /*                                */
            if (VOS_STATUS_SUCCESS !=
                vos_timer_start(&pNeighborRoamInfo->emptyScanRefreshTimer,
                    pNeighborRoamInfo->cfgParams.emptyScanRefreshPeriod))
            {
                smsLog(pMac, LOGE, FL("Empty scan refresh timer failed to start (%d)"),
                        status);
                vos_mem_free(pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList);
                pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = NULL;
                pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels = 0;
                vosStatus = VOS_STATUS_E_FAILURE;
            }
            else
            {
                smsLog(pMac, LOGE, FL("Empty scan refresh timer started (%d ms)"),
                        (pNeighborRoamInfo->cfgParams.emptyScanRefreshPeriod));
            }
        }
        else if (eThirdEmptyScan == pNeighborRoamInfo->uEmptyScanCount)
        {
            /*                                           */
            if (VOS_STATUS_SUCCESS !=
                    vos_timer_start(&pNeighborRoamInfo->neighborResultsRefreshTimer,
                        pNeighborRoamInfo->cfgParams.neighborResultsRefreshPeriod))
            {
                smsLog(pMac, LOGE, FL("Neighbor results refresh timer failed to start (%d)"),
                        status);
                vos_mem_free(pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList);
                pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = NULL;
                pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels = 0;
                vosStatus = VOS_STATUS_E_FAILURE;
            }
            else
            {
                smsLog(pMac, LOG2, FL("Neighbor results refresh timer started (%d ms)"),
                        (pNeighborRoamInfo->cfgParams.neighborResultsRefreshPeriod * PAL_TIMER_TO_MS_UNIT));
            }
        }
    }

    NEIGHBOR_ROAM_DEBUG(pMac, LOG2, "Neighbor roam empty scan count=%d scan mode=%d",
        pNeighborRoamInfo->uEmptyScanCount, pNeighborRoamInfo->uScanMode);
#endif
    return vosStatus;
}


static eHalStatus csrNeighborRoamProcessScanComplete (tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tCsrScanResultFilter    scanFilter;
    tScanResultHandle       scanResult;
    tANI_U32                tempVal = 0;
    tANI_BOOLEAN            roamNow = eANI_BOOLEAN_FALSE;
    eHalStatus              hstatus;

#if  defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_ESE) || defined(FEATURE_WLAN_LFR)
        /*                                                                                              
                                                                    */
        if ((eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN == pNeighborRoamInfo->neighborRoamState)
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        && (!csrRoamIsRoamOffloadScanEnabled(pMac))
#endif
        )
        {
            hstatus = csrNeighborRoamBssIdScanFilter(pMac, &scanFilter);
            NEIGHBOR_ROAM_DEBUG(pMac, LOGW, FL("11R or ESE Association: Prepare scan filter status  with neighbor AP = %d"), hstatus);
            tempVal = 1;
        }
        else
#endif
        {
            hstatus = csrNeighborRoamPrepareScanProfileFilter(pMac, &scanFilter);
            NEIGHBOR_ROAM_DEBUG(pMac, LOGW, FL("11R/ESE/Other Association: Prepare scan to find neighbor AP filter status  = %d"), hstatus);
        }
        if (eHAL_STATUS_SUCCESS != hstatus)
        {
            smsLog(pMac, LOGE, FL("Scan Filter preparation failed for Assoc type %d.. Bailing out.."), tempVal);
            return eHAL_STATUS_FAILURE;
        }
        hstatus = csrScanGetResult(pMac, &scanFilter, &scanResult);
        if (hstatus != eHAL_STATUS_SUCCESS)
        {
            NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("Get Scan Result status code %d"), hstatus);
        }
        /*                                                      */
        roamNow = csrNeighborRoamProcessScanResults(pMac, &scanResult);

        /*                      */
        csrFreeScanFilter(pMac, &scanFilter);

        tempVal = csrLLCount(&pNeighborRoamInfo->roamableAPList);

#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        if(!csrRoamIsRoamOffloadScanEnabled(pMac))
        {
#endif
         switch(pNeighborRoamInfo->neighborRoamState)
         {
            case eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN:
                if (tempVal)
                {
#ifdef FEATURE_WLAN_LFR
                    /*
                                                                
                                                              
                     */
                    pNeighborRoamInfo->uEmptyScanCount = 0;
                    pNeighborRoamInfo->uScanMode = DEFAULT_SCAN;
#endif
#ifdef WLAN_FEATURE_VOWIFI_11R
                    /*                                                                                                  
                                                                    */
                    if (pNeighborRoamInfo->is11rAssoc)
                    {
                        /*                                                                        */
                        CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN)
                    }
                    else
#endif
#ifdef FEATURE_WLAN_ESE
                    /*                                                                                                  
                                                                    */
                    if (pNeighborRoamInfo->isESEAssoc)
                    {
                        /*                                                                        */
                        CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN)
                    }
                    else
#endif
#ifdef FEATURE_WLAN_LFR
                    /*                                                                                   
                                                                    */
                    if (csrRoamIsFastRoamEnabled(pMac, CSR_SESSION_ID_INVALID))
                    {
                        /*                                                                        */
                        CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN)
                    }
                    else
#endif
                    {
                       
                        NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("Completed scanning of CFG CHAN LIST in non-11r association. Registering reassoc callback"));
                        /*                                                                                              */
                        /*                                                                                                    
                                                                                                                       
                                                   */
                        
//                                                                              
                    }
                }
                else
                {
                    NEIGHBOR_ROAM_DEBUG(pMac, LOGE,
                    FL("No candidate found after scanning in state %s .. "),
                    macTraceGetNeighbourRoamState(
                    pNeighborRoamInfo->neighborRoamState));
                    /*                         */
                    csrNeighborRoamHandleEmptyScanResult(pMac);
                }
                break;
#ifdef WLAN_FEATURE_VOWIFI_11R                
            case eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN:
                if (!tempVal)
                {
                    smsLog(pMac, LOGE, FL("No candidate found after scanning"
                           "in state %s .. "),
                           macTraceGetNeighbourRoamState(
                           pNeighborRoamInfo->neighborRoamState));
                    /*                                                                                    */
                    csrNeighborRoamTransitToCFGChanScan(pMac);
                }
                break;
#endif /*                         */
            default:
                //                                                                               
                //                                                                                      
                //                                                                            
                VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO, 
                           FL("State %s"),
                           macTraceGetNeighbourRoamState(
                           pNeighborRoamInfo->neighborRoamState));

                //                             
                return eHAL_STATUS_SUCCESS;
         }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        }
#endif

        if (tempVal)
        {
            VOS_STATUS  vosStatus = VOS_STATUS_SUCCESS;

            if (roamNow)
            {
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
                if(!csrRoamIsRoamOffloadScanEnabled(pMac))
                {
#endif
                  NEIGHBOR_ROAM_DEBUG(pMac, LOG2,
                      FL("Immediate roam-deregister UP indication. RSSI = %d"),
                      NEIGHBOR_ROAM_LOOKUP_UP_THRESHOLD * (-1));

                  vosStatus = WLANTL_DeregRSSIIndicationCB(pMac->roam.gVosContext,
                          (v_S7_t)NEIGHBOR_ROAM_LOOKUP_UP_THRESHOLD * (-1),
                          WLANTL_HO_THRESHOLD_UP,
                          csrNeighborRoamNeighborLookupUPCallback,
                          VOS_MODULE_ID_SME);

                  if(!VOS_IS_STATUS_SUCCESS(vosStatus))
                  {
                      smsLog(pMac, LOGW,
                          FL("Couldn't deregister lookup UP callback with TL: Status = %d"), vosStatus);
                  }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
                }
#endif

                csrNeighborRoamTriggerHandoff(pMac, pNeighborRoamInfo);
                return eHAL_STATUS_SUCCESS;
            }

        hstatus = vos_timer_start(&pNeighborRoamInfo->neighborResultsRefreshTimer,
                    pNeighborRoamInfo->cfgParams.neighborResultsRefreshPeriod);

           /*                                                                                                                  
                                                                                                                             */
        if( hstatus != eHAL_STATUS_SUCCESS)
            {
            smsLog(pMac, LOGE, FL("Neighbor results refresh timer failed to start, status = %d"), hstatus);
                vos_mem_free(pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList);
                pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = NULL;
                pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels = 0;
                return eHAL_STATUS_FAILURE;
            }

            NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Registering DOWN event Reassoc callback with TL. RSSI = %d"), pNeighborRoamInfo->cfgParams.neighborReassocThreshold * (-1));
            /*                                        */
            vosStatus = WLANTL_RegRSSIIndicationCB(pMac->roam.gVosContext, (v_S7_t)pNeighborRoamInfo->cfgParams.neighborReassocThreshold * (-1),
                                            WLANTL_HO_THRESHOLD_DOWN, 
                                            csrNeighborRoamReassocIndCallback,
                                            VOS_MODULE_ID_SME, pMac);
            
            if(!VOS_IS_STATUS_SUCCESS(vosStatus))
            {
               //       
               smsLog(pMac, LOGW, FL(" Couldn't register csrNeighborRoamReassocIndCallback with TL: Status = %d"), vosStatus);
            }
 
        }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        if (csrRoamIsRoamOffloadScanEnabled(pMac))
        {
            if (!tempVal || !roamNow)
            {
                if((eSME_ROAM_TRIGGER_SCAN == pNeighborRoamInfo->cfgRoamEn) ||
                   (eSME_ROAM_TRIGGER_FAST_ROAM == pNeighborRoamInfo->cfgRoamEn))
                {
                    //                                                           
                    //                           
                    VOS_TRACE( VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_ERROR,
                            "tempVal = %u, roamNow = %d uOsRequestedHandoff = %d",
                            tempVal, roamNow, pNeighborRoamInfo->uOsRequestedHandoff);
                }
                else
                {
                    if (pNeighborRoamInfo->uOsRequestedHandoff)
                    {
                        csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_START,
                            REASON_NO_CAND_FOUND_OR_NOT_ROAMING_NOW);
                        pNeighborRoamInfo->uOsRequestedHandoff = 0;
                    }
                    else if (pNeighborRoamInfo->isForcedInitialRoamTo5GH)
                    {
                        smsLog(pMac, LOGE, FL("Forced roam to 5G No candidate found, starting fw offload scan again, status = %d"), hstatus);
                        csrNeighborRoamStartLfrScan(pMac, REASON_INITIAL_FORCED_ROAM_TO_5G);
                    }
                    else
                    {
                        /*                                                 
                                                                       */
                        csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_RESTART,
                            REASON_NO_CAND_FOUND_OR_NOT_ROAMING_NOW);
                    }
                }
                CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_CONNECTED);
            }
        }
#endif
    return eHAL_STATUS_SUCCESS;
}


/*                                                                            

                                          

                                                                                     
                                                                                          
                                                                                               
                                                                                              
                                                                                        
                   

                                                       
                               
                             
                             

                                                                              

                                                                           */
static eHalStatus csrNeighborRoamScanRequestCallback(tHalHandle halHandle, void *pContext,
                         tANI_U32 scanId, eCsrScanStatus status)
{
    tpAniSirGlobal                  pMac = (tpAniSirGlobal) halHandle;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tANI_U8                         currentChanIndex;
    eHalStatus              hstatus;
#ifdef FEATURE_WLAN_LFR
    tANI_U32 sessionId = CSR_SESSION_ID_INVALID;

    if (NULL != pContext)
    {
        sessionId = *((tANI_U32*)pContext);

        if (!csrRoamIsStaMode(pMac, sessionId))
        {
            smsLog(pMac, LOGE, FL("Ignoring scan request callback on non-infra"
                   "session %d in state %s"),
                    sessionId, macTraceGetNeighbourRoamState(
                    pNeighborRoamInfo->neighborRoamState));
            vos_mem_free(pContext);
            return eHAL_STATUS_SUCCESS;
        }

        if (!csrRoamIsFastRoamEnabled(pMac,sessionId))
        {
            smsLog(pMac, LOGE, FL("Received when fast roam is disabled. Ignore it"));
            vos_mem_free(pContext);
            return eHAL_STATUS_SUCCESS;
        }
    }
#endif
    pMac->roam.neighborRoamInfo.scanRspPending = eANI_BOOLEAN_FALSE;
    
    /*                                                                                                  */
    if (eCSR_NEIGHBOR_ROAM_STATE_CONNECTED == pNeighborRoamInfo->neighborRoamState)
    {
        smsLog(pMac, LOGE, FL("Received in CONNECTED state. Must be because a UP event from TL after issuing scan request. Ignore it"));
        if (NULL != pContext)
           vos_mem_free(pContext);
        return eHAL_STATUS_SUCCESS;
    }

    /*                                                                                                     */
    currentChanIndex = (pMac->roam.neighborRoamInfo.roamChannelInfo.currentChanIndex) ? (pMac->roam.neighborRoamInfo.roamChannelInfo.currentChanIndex - 1) : 0;

    /*                 */
    if (pMac->roam.neighborRoamInfo.roamChannelInfo.currentChannelListInfo.ChannelList) {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGW, FL("csrNeighborRoamScanRequestCallback received for Channel = %d, ChanIndex = %d"),
                    pMac->roam.neighborRoamInfo.roamChannelInfo.currentChannelListInfo.ChannelList[currentChanIndex], currentChanIndex);
    }
    else
    {
        smsLog(pMac, LOG1, FL("Received during clean-up. Silently ignore scan completion event."));
        if (NULL != pContext)
           vos_mem_free(pContext);
        return eHAL_STATUS_SUCCESS;
    }

    if (eANI_BOOLEAN_FALSE == pNeighborRoamInfo->roamChannelInfo.chanListScanInProgress)
    {
        /*                                                                                      
                                                       */
        /*                                                                                                       
                                                                                                          */
        NEIGHBOR_ROAM_DEBUG(pMac, LOGW, FL("Channel list scan completed. Current chan index = %d"), currentChanIndex);
        VOS_ASSERT(pNeighborRoamInfo->roamChannelInfo.currentChanIndex == 0);

        hstatus = csrNeighborRoamProcessScanComplete(pMac);

        if (eHAL_STATUS_SUCCESS != hstatus)
        {
            smsLog(pMac, LOGE, FL("Neighbor scan process complete failed with status %d"), hstatus);
            if (NULL != pContext)
                vos_mem_free(pContext);
            return eHAL_STATUS_FAILURE;
        }
    }
    else
    {

        /*                                                                      */
        hstatus = vos_timer_start(&pNeighborRoamInfo->neighborScanTimer,
                    pNeighborRoamInfo->cfgParams.neighborScanPeriod);
        if (eHAL_STATUS_SUCCESS != hstatus)
        {
            /*                                               */
            smsLog(pMac, LOGE, FL("Neighbor scan PAL Timer start failed, status = %d, Ignoring state transition"), status);
            vos_mem_free(pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList);
            pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = NULL;
            pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels = 0;
            if (NULL != pContext)
                vos_mem_free(pContext);
            return eHAL_STATUS_FAILURE;
        }
    }

    if (NULL != pContext)
        vos_mem_free(pContext);
    return eHAL_STATUS_SUCCESS;
}

#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
/*                                                                            

                                                

                                                                                             
                                                                                         
                                                                                              

                                                       
                               
                             
                             

                                                                              

                                                                           */
static eHalStatus csrNeighborRoamScanResultRequestCallback(tHalHandle halHandle, void *pContext,
                                                           tANI_U32 scanId, eCsrScanStatus status)
{
    tpAniSirGlobal                  pMac = (tpAniSirGlobal) halHandle;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus              hstatus;

    smsLog(pMac, LOG2, FL("called "));
    pMac->roam.neighborRoamInfo.scanRspPending = eANI_BOOLEAN_FALSE;

    /*                                                 */
    if (eCSR_NEIGHBOR_ROAM_STATE_CONNECTED != pNeighborRoamInfo->neighborRoamState)
    {
        smsLog(pMac, LOGW, FL("Received in not CONNECTED state. Ignore it"));
        return eHAL_STATUS_SUCCESS;
    }

    /*                                                                                                       
                                                                                                      */

    hstatus = csrNeighborRoamProcessScanComplete(pMac);

    if (eHAL_STATUS_SUCCESS != hstatus)
    {
        smsLog(pMac, LOGE, FL("Neighbor scan process complete failed with status %d"), hstatus);
        return eHAL_STATUS_FAILURE;
    }
    return eHAL_STATUS_SUCCESS;
}
#endif //                              

#ifdef FEATURE_WLAN_LFR
static eHalStatus csrNeighborRoamForceRoamTo5GhScanCb(tHalHandle halHandle,
        void *pContext, tANI_U32 scanId, eCsrScanStatus status)
{
    tpAniSirGlobal                  pMac = (tpAniSirGlobal) halHandle;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus hstatus = eHAL_STATUS_SUCCESS;
    tANI_U32 sessionId = CSR_SESSION_ID_INVALID;

    if (NULL != pContext)
    {
        sessionId = *((tANI_U32*)pContext);
        if (!csrRoamIsFastRoamEnabled(pMac,sessionId))
        {
            smsLog(pMac, LOGE, FL("Received when fast roam is disabled. Ignore it"));
            hstatus = eHAL_STATUS_FAILURE;
            goto end;
        }
    }

    pMac->roam.neighborRoamInfo.scanRspPending = eANI_BOOLEAN_FALSE;

    /*                                                                                                  */
    if (eCSR_NEIGHBOR_ROAM_STATE_CONNECTED == pNeighborRoamInfo->neighborRoamState)
    {
        smsLog(pMac, LOGE, FL("Received in CONNECTED state. Must be because a UP event from TL after issuing scan request. Ignore it"));
        hstatus = eHAL_STATUS_FAILURE;
        goto end;
    }

    if (eCSR_NEIGHBOR_ROAM_STATE_INIT == pNeighborRoamInfo->neighborRoamState)
    {
        smsLog(pMac, LOGE, FL("Received in INIT state. Must have disconnected. Ignore it"));
        hstatus = eHAL_STATUS_FAILURE;
        goto end;
    }

    NEIGHBOR_ROAM_DEBUG(pMac, LOGW, "%s: process scan results", __func__);
    hstatus = csrNeighborRoamProcessScanComplete(pMac);

    //                                      
    pNeighborRoamInfo->isForcedInitialRoamTo5GH = 0;

    if (eHAL_STATUS_SUCCESS != hstatus)
    {
        smsLog(pMac, LOGE, FL("Force Roam To 5GhScanCb failed with status %d"), hstatus);
        goto end;
    }

    if (NULL != pContext)
        vos_mem_free(pContext);
    return hstatus;

end:
    if (NULL != pContext)
        vos_mem_free(pContext);
    if (hstatus != eHAL_STATUS_SUCCESS)
          csrNeighborRoamStartLfrScan(pMac, REASON_INITIAL_FORCED_ROAM_TO_5G);
    return hstatus;
}
#endif

#ifdef FEATURE_WLAN_LFR
static eHalStatus csrNeighborRoamContiguousScanRequestCallback(tHalHandle halHandle,
        void *pContext, tANI_U32 scanId, eCsrScanStatus status)
{
    tpAniSirGlobal                  pMac = (tpAniSirGlobal) halHandle;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus hstatus = eHAL_STATUS_SUCCESS;
    tANI_U32 sessionId = CSR_SESSION_ID_INVALID;

    if (NULL != pContext)
    {
        sessionId = *((tANI_U32*)pContext);
        if (!csrRoamIsFastRoamEnabled(pMac,sessionId))
        {
            smsLog(pMac, LOGE, FL("Received when fast roam is disabled. Ignore it"));
            vos_mem_free(pContext);
            return eHAL_STATUS_SUCCESS;
        }
    }

    pMac->roam.neighborRoamInfo.scanRspPending = eANI_BOOLEAN_FALSE;

    /*                                                                                                  */
    if (eCSR_NEIGHBOR_ROAM_STATE_CONNECTED == pNeighborRoamInfo->neighborRoamState)
    {
        smsLog(pMac, LOGE, FL("Received in CONNECTED state. Must be because a UP event from TL after issuing scan request. Ignore it"));
        if (NULL != pContext)
           vos_mem_free(pContext);
        return eHAL_STATUS_SUCCESS;
    }

    if (eCSR_NEIGHBOR_ROAM_STATE_INIT == pNeighborRoamInfo->neighborRoamState)
    {
        smsLog(pMac, LOGE, FL("Received in INIT state. Must have disconnected. Ignore it"));
        if (NULL != pContext)
           vos_mem_free(pContext);
        return eHAL_STATUS_SUCCESS;
    }

    NEIGHBOR_ROAM_DEBUG(pMac, LOGW, "%s: process scan results", __func__);
    hstatus = csrNeighborRoamProcessScanComplete(pMac);

    if (eHAL_STATUS_SUCCESS != hstatus)
    {
        smsLog(pMac, LOGE, FL("Neighbor scan process complete failed with status %d"), hstatus);
    }

    if (NULL != pContext)
        vos_mem_free(pContext);

    return hstatus;
}
#endif

/*                                                                            

                                         

                                                                                          
                  

                                                  
                                                                                  

                                                                              

                                                                           */
eHalStatus csrNeighborRoamIssueBgScanRequest(tpAniSirGlobal pMac, 
                                             tCsrBGScanRequest *pBgScanParams,
                                             tANI_U32 sessionId,
                                             csrScanCompleteCallback callbackfn)
{
    eHalStatus status = eHAL_STATUS_SUCCESS;
    tANI_U32 scanId;
    tCsrScanRequest scanReq;
    tANI_U8 channel;
    void * userData = NULL;
    
    if (1 == pBgScanParams->ChannelInfo.numOfChannels)
        NEIGHBOR_ROAM_DEBUG(pMac, LOGW, FL("Channel = %d, ChanIndex = %d"),
            pBgScanParams->ChannelInfo.ChannelList[0], 
            pMac->roam.neighborRoamInfo.roamChannelInfo.currentChanIndex);

    //                                                           
    vos_mem_set(&scanReq, sizeof(tCsrScanRequest), 0);
    /*                       */
    scanReq.SSIDs.numOfSSIDs = 1;
    scanReq.SSIDs.SSIDList = vos_mem_malloc(sizeof(tCsrSSIDInfo) * scanReq.SSIDs.numOfSSIDs);
    if (NULL == scanReq.SSIDs.SSIDList)
    {
       //       
       smsLog(pMac, LOGE, FL("Couldn't allocate memory for the SSID..Freeing memory allocated for Channel List"));
       return eHAL_STATUS_FAILURE;
    }
    vos_mem_zero(scanReq.SSIDs.SSIDList, sizeof(tCsrSSIDInfo) * scanReq.SSIDs.numOfSSIDs);

    scanReq.SSIDs.SSIDList[0].handoffPermitted = eANI_BOOLEAN_TRUE;
    scanReq.SSIDs.SSIDList[0].ssidHidden = eANI_BOOLEAN_TRUE;
    vos_mem_copy((void *)&scanReq.SSIDs.SSIDList[0].SSID, (void *)&pBgScanParams->SSID, sizeof(pBgScanParams->SSID));
    
    scanReq.ChannelInfo.numOfChannels = pBgScanParams->ChannelInfo.numOfChannels;
    if (1 == pBgScanParams->ChannelInfo.numOfChannels)
    {
        channel = pBgScanParams->ChannelInfo.ChannelList[0];
        scanReq.ChannelInfo.ChannelList = &channel;    
    }
    else
    {
        scanReq.ChannelInfo.ChannelList = pBgScanParams->ChannelInfo.ChannelList;
    }

    scanReq.BSSType = eCSR_BSS_TYPE_INFRASTRUCTURE;
    scanReq.scanType = eSIR_ACTIVE_SCAN;
    scanReq.requestType = eCSR_SCAN_HO_BG_SCAN;
    scanReq.maxChnTime = pBgScanParams->maxChnTime;
    scanReq.minChnTime = pBgScanParams->minChnTime;

    userData = vos_mem_malloc(sizeof(tANI_U32));
    if (NULL == userData)
    {
        smsLog(pMac, LOGE, FL("Failed to allocate memory for scan request"));
        vos_mem_free(scanReq.SSIDs.SSIDList);
        return eHAL_STATUS_FAILURE;
    }
    *((tANI_U32*)userData) = sessionId;
    status = csrScanRequest(pMac, CSR_SESSION_ID_INVALID, &scanReq,
                        &scanId, callbackfn, (void *) userData);
    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("CSR Scan Request failed with status %d"), status);
        vos_mem_free(scanReq.SSIDs.SSIDList);
        vos_mem_free(userData);
        return status;
    }
    pMac->roam.neighborRoamInfo.scanRspPending = eANI_BOOLEAN_TRUE;

    vos_mem_free(scanReq.SSIDs.SSIDList);
    if (1 == pBgScanParams->ChannelInfo.numOfChannels)
        NEIGHBOR_ROAM_DEBUG(pMac, LOG1, FL("Channel List Address = %p, Actual index = %d"),
                &pMac->roam.neighborRoamInfo.roamChannelInfo.currentChannelListInfo.ChannelList[0], 
                pMac->roam.neighborRoamInfo.roamChannelInfo.currentChanIndex);

    return status;
}

static void csrNeighborRoamFillNonChannelBgScanParams (tpAniSirGlobal pMac, 
                                                       tpCsrBGScanRequest bgScanParams)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tANI_U8             broadcastBssid[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

    vos_mem_copy(bgScanParams->bssid, broadcastBssid, sizeof(tCsrBssid));
    bgScanParams->SSID.length = pMac->roam.roamSession[pNeighborRoamInfo->csrSessionId].connectedProfile.SSID.length;
    vos_mem_copy(bgScanParams->SSID.ssId, 
        pMac->roam.roamSession[pNeighborRoamInfo->csrSessionId].connectedProfile.SSID.ssId,
        pMac->roam.roamSession[pNeighborRoamInfo->csrSessionId].connectedProfile.SSID.length);

    bgScanParams->minChnTime = pNeighborRoamInfo->cfgParams.minChannelScanTime;
    bgScanParams->maxChnTime = pNeighborRoamInfo->cfgParams.maxChannelScanTime;
}

/*                                                                            

                                    

                                                                                   
                                                                                 
                                                                                   
                   

                                                  

                                                                              

                                                                           */
eHalStatus csrNeighborRoamPerformBgScan(tpAniSirGlobal pMac, tANI_U32 sessionId)
{
    eHalStatus      status = eHAL_STATUS_SUCCESS;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tCsrBGScanRequest   bgScanParams;
    tANI_U8             channel = 0;

    if ( pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList &&
         pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels )
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOG1, FL("Channel List Address = %p"), &pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList[0]);
    }
    else 
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("Channel List Empty"));
        //                                                              
        //                                                                 
        //                                                                      
        //                                
        csrNeighborRoamHandleEmptyScanResult(pMac);
        return status;
    }

    /*                                                                                    */
    if ( pNeighborRoamInfo->roamChannelInfo.currentChanIndex
            > pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels)
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("Invalid channel index: %d"), pNeighborRoamInfo->roamChannelInfo.currentChanIndex);
        //                     
        csrNeighborRoamHandleEmptyScanResult(pMac);
        return status;
    }

    /*                                                   */

    vos_mem_set(&bgScanParams, sizeof(tCsrBGScanRequest), 0);

    channel = pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList[pNeighborRoamInfo->roamChannelInfo.currentChanIndex];
    bgScanParams.ChannelInfo.numOfChannels = 1;
    bgScanParams.ChannelInfo.ChannelList = &channel;

    csrNeighborRoamFillNonChannelBgScanParams(pMac, &bgScanParams);

    /*                                              */
    if ((TRUE == CSR_IS_CHANNEL_DFS(channel)) &&
         (TRUE == pMac->roam.configParam.allowDFSChannelRoam))
    {
         bgScanParams.minChnTime = pMac->roam.configParam.nPassiveMinChnTime;
         bgScanParams.maxChnTime = pMac->roam.configParam.nPassiveMaxChnTime;
    }

    status = csrNeighborRoamIssueBgScanRequest(pMac, &bgScanParams,
                                               sessionId, csrNeighborRoamScanRequestCallback);
    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("Issue of BG Scan request failed: Status = %d"), status);
    }

    pNeighborRoamInfo->roamChannelInfo.currentChanIndex++;
    if (pNeighborRoamInfo->roamChannelInfo.currentChanIndex >= 
            pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels)
    {      
        NEIGHBOR_ROAM_DEBUG(pMac, LOG1, FL("Completed scanning channels in Channel List: CurrChanIndex = %d, Num Channels = %d"),
                                            pNeighborRoamInfo->roamChannelInfo.currentChanIndex, 
                                            pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels);
        /*                                             */
        pNeighborRoamInfo->roamChannelInfo.currentChanIndex = 0;
        /*                                                                                                      
                                              */
        if (eANI_BOOLEAN_TRUE == pNeighborRoamInfo->roamChannelInfo.chanListScanInProgress)
        {
            pNeighborRoamInfo->roamChannelInfo.chanListScanInProgress = eANI_BOOLEAN_FALSE;
        }
    }

    if (eHAL_STATUS_SUCCESS != status)
    {
        /*
                                                                     
                                                                
         */
        csrNeighborRoamScanRequestCallback(pMac, NULL, 0, eCSR_SCAN_FAILURE);
    }

    return status;
}

#ifdef FEATURE_WLAN_LFR
eHalStatus csrNeighborRoamScanForInitialForced5GRoaming(tpAniSirGlobal pMac, tANI_U32 sessionId)
{
    eHalStatus      status = eHAL_STATUS_SUCCESS;
    tCsrBGScanRequest   bgScanParams;
    tANI_U8   numOfChannels = 0, i = 0;
    tANI_U8   tempChannelList[WNI_CFG_VALID_CHANNEL_LIST_LEN];
    tANI_U8   channelList[WNI_CFG_VALID_CHANNEL_LIST_LEN];
    tANI_U8   tempNumOfChannels = 0;

    vos_mem_set(&bgScanParams, sizeof(tCsrBGScanRequest), 0);
    /*                                                */
    NEIGHBOR_ROAM_DEBUG(pMac, LOG2, "%s: get valid channel list", __func__);
    tempNumOfChannels = sizeof(pMac->roam.validChannelList);

    if(HAL_STATUS_SUCCESS(csrGetCfgValidChannels(pMac,
                    (tANI_U8 *)pMac->roam.validChannelList,
                    (tANI_U32 *) &tempNumOfChannels)))
    {
        //                                               
        //                                                       
        csrNeighborRoamChannelsFilterByBand(
                     pMac,
                     pMac->roam.validChannelList,
                     tempNumOfChannels,
                     tempChannelList,
                     &tempNumOfChannels,
                     SIR_BAND_5_GHZ
                     );
        for (i = 0; (i < tempNumOfChannels &&(i < WNI_CFG_VALID_CHANNEL_LIST_LEN)); i++)
        {
            /*                                                    
                                                           */
            if (CSR_IS_CHANNEL_DFS(tempChannelList[i]))
            {
                if (pMac->roam.configParam.allowDFSChannelRoam == TRUE)
                {
                    channelList[numOfChannels++] = tempChannelList[i];
                }
            }
            else
            {
                channelList[numOfChannels++] = tempChannelList[i];
            }
        }
    }
    else
    {
        smsLog(pMac, LOGW, FL("csrGetCfgValidChannels got failed "));
        return eHAL_STATUS_FAILURE;
    }

    if(numOfChannels == 0)
    {
        smsLog(pMac, LOGE,
               FL(" No valid 5Ghz channel present so skipping Initial Forced 5Gh roaming"));
        return VOS_STATUS_E_EMPTY;
    }
    if (numOfChannels > WNI_CFG_VALID_CHANNEL_LIST_LEN)
    {
        numOfChannels = WNI_CFG_VALID_CHANNEL_LIST_LEN;
    }

    bgScanParams.ChannelInfo.numOfChannels = numOfChannels;
    bgScanParams.ChannelInfo.ChannelList = channelList;
    for (i = 0; i < numOfChannels; i++)
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGW, "%s: valid channel list = %d",
                __func__, bgScanParams.ChannelInfo.ChannelList[i]);
    }
    csrNeighborRoamFillNonChannelBgScanParams(pMac, &bgScanParams);

    status = csrNeighborRoamIssueBgScanRequest(pMac, &bgScanParams,
                                               sessionId, csrNeighborRoamForceRoamTo5GhScanCb);

    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("Forced intial roam to 5Gh request failed: Status = %d"), status);
    }

    return status;
}
#endif

#ifdef FEATURE_WLAN_LFR
eHalStatus csrNeighborRoamPerformContiguousBgScan(tpAniSirGlobal pMac, tANI_U32 sessionId)
{
    eHalStatus      status = eHAL_STATUS_SUCCESS;
    tCsrBGScanRequest   bgScanParams;
    tANI_U8   numOfChannels = 0, i = 0;
    tANI_U8   *channelList = NULL;
    tANI_U8   *pInChannelList = NULL;
    tANI_U8   tmpChannelList[WNI_CFG_VALID_CHANNEL_LIST_LEN];

    vos_mem_set(&bgScanParams, sizeof(tCsrBGScanRequest), 0);

    /*                                                */
    NEIGHBOR_ROAM_DEBUG(pMac, LOG2, "%s: get valid channel list", __func__);

    numOfChannels = sizeof(pMac->roam.validChannelList);

    if(!HAL_STATUS_SUCCESS(csrGetCfgValidChannels(pMac,
                          (tANI_U8 *)pMac->roam.validChannelList,
                          (tANI_U32 *) &numOfChannels)))
    {
        smsLog(pMac, LOGE, FL("Could not get valid channel list"));
        return eHAL_STATUS_FAILURE;
    }
    pInChannelList = pMac->roam.validChannelList;

    if (CSR_IS_ROAM_INTRA_BAND_ENABLED(pMac))
    {
        csrNeighborRoamChannelsFilterByBand(
                             pMac,
                             pInChannelList,
                             numOfChannels,
                             tmpChannelList,
                             &numOfChannels,
                             GetRFBand(pMac->roam.neighborRoamInfo.currAPoperationChannel));
        pInChannelList = tmpChannelList;
    }

    channelList = vos_mem_malloc(numOfChannels);
    if ( NULL == channelList )
    {
        smsLog(pMac, LOGE, FL("could not allocate memory for channelList"));
        return eHAL_STATUS_FAILURE;
    }
    vos_mem_copy(channelList, (tANI_U8 *)pInChannelList,
                 numOfChannels * sizeof(tANI_U8));

    bgScanParams.ChannelInfo.numOfChannels = numOfChannels;
    bgScanParams.ChannelInfo.ChannelList = channelList;
    for (i = 0; i < numOfChannels; i++)
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGW, "%s: valid channel list = %d",
                __func__, bgScanParams.ChannelInfo.ChannelList[i]);
    }
    csrNeighborRoamFillNonChannelBgScanParams(pMac, &bgScanParams);

    status = csrNeighborRoamIssueBgScanRequest(pMac, &bgScanParams,
                                               sessionId, csrNeighborRoamContiguousScanRequestCallback);

    vos_mem_free(channelList);

    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("Issue of BG Scan request failed: Status = %d"), status);
    }

    return status;
}
#endif

/*                                                                            

                                                

                                                                                   
                                                                        

                                                                          

                

                                                                           */
void csrNeighborRoamNeighborScanTimerCallback(void *pv)
{
    tCsrTimerInfo *pInfo = (tCsrTimerInfo *)pv;
    tpAniSirGlobal pMac = pInfo->pMac;
    tANI_U32         sessionId = pInfo->sessionId;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

    //                                                                          
    if(eANI_BOOLEAN_TRUE == pNeighborRoamInfo->scanRspPending)
    {
       //   
       smsLog(pMac, LOGW, FL("Already BgScanRsp is Pending"));
       return;
    }

    VOS_ASSERT(sessionId == pNeighborRoamInfo->csrSessionId);

    switch (pNeighborRoamInfo->neighborRoamState)
    {
#ifdef WLAN_FEATURE_VOWIFI_11R
        case eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN:
            switch(pNeighborRoamInfo->prevNeighborRoamState)
            {
                case eCSR_NEIGHBOR_ROAM_STATE_REPORT_QUERY:
                    csrNeighborRoamPerformBgScan(pMac, sessionId);
                    break;
                default:
                    smsLog(pMac, LOGE, FL("Neighbor scan callback received in"
                          "state %s, prev state = %s"),
                           macTraceGetNeighbourRoamState(
                           pNeighborRoamInfo->neighborRoamState),
                           macTraceGetNeighbourRoamState(
                           pNeighborRoamInfo->prevNeighborRoamState));
                    break;
            }
            break;
#endif /*                         */
        case eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN:     
            csrNeighborRoamPerformBgScan(pMac, sessionId);
            break;
        default:
            break;
    }
    return;
}

void csrNeighborRoamEmptyScanRefreshTimerCallback(void *context)
{
    tCsrTimerInfo *pInfo = (tCsrTimerInfo *)context;
    tpAniSirGlobal pMac = pInfo->pMac;
    VOS_STATUS     vosStatus = VOS_STATUS_SUCCESS;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

    /*                                                             */
    csrNeighborRoamResetConnectedStateControlInfo(pMac);

#if defined WLAN_FEATURE_VOWIFI_11R && defined WLAN_FEATURE_VOWIFI
    if ((pNeighborRoamInfo->is11rAssoc) && (pMac->rrm.rrmSmeContext.rrmConfig.rrmEnabled))
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("11R Association:Neighbor Lookup Down event received in CONNECTED state"));
        vosStatus = csrNeighborRoamIssueNeighborRptRequest(pMac);
        if (VOS_STATUS_SUCCESS != vosStatus)
        {
            smsLog(pMac, LOGE, FL("Neighbor report request failed. status = %d"), vosStatus);
            return;
        }
        /*                                                                                           */
        pNeighborRoamInfo->FTRoamInfo.currentNeighborRptRetryNum++;
        pNeighborRoamInfo->FTRoamInfo.neighborRptPending = eANI_BOOLEAN_TRUE;
        CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REPORT_QUERY)
    }
    else
#endif
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("Non 11R or ESE Association:empty scan refresh timer expired"));
        vosStatus = csrNeighborRoamTransitToCFGChanScan(pMac);
        if (VOS_STATUS_SUCCESS != vosStatus)
        {
            return;
        }
    }
    return;
}

/*                                                                            

                                                  

                                                                                   
                                                                                    
                                                                                     
                                  

                                                                               

                

                                                                           */
void csrNeighborRoamResultsRefreshTimerCallback(void *context)
{
    tCsrTimerInfo *pInfo = (tCsrTimerInfo *)context;
    tpAniSirGlobal pMac = pInfo->pMac;
    VOS_STATUS     vosStatus = VOS_STATUS_SUCCESS;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
     
    NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Deregistering DOWN event reassoc callback with TL. RSSI = %d"), pNeighborRoamInfo->cfgParams.neighborReassocThreshold * (-1));

    /*                                                   */
    vosStatus = WLANTL_DeregRSSIIndicationCB(pMac->roam.gVosContext, (v_S7_t)pNeighborRoamInfo->cfgParams.neighborReassocThreshold * (-1),
                                                        WLANTL_HO_THRESHOLD_DOWN, 
                                                        csrNeighborRoamReassocIndCallback,
                                                        VOS_MODULE_ID_SME);
                        
    if(!VOS_IS_STATUS_SUCCESS(vosStatus))
    {
        //       
        smsLog(pMac, LOGW, FL(" Couldn't deregister csrNeighborRoamReassocIndCallback with TL: Status = %d"), vosStatus);
    }

    /*                                                             */
    csrNeighborRoamResetConnectedStateControlInfo(pMac);

#if defined WLAN_FEATURE_VOWIFI_11R && defined WLAN_FEATURE_VOWIFI
    if ((pNeighborRoamInfo->is11rAssoc) && (pMac->rrm.rrmSmeContext.rrmConfig.rrmEnabled))
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("11R Association:Neighbor Lookup Down event received in CONNECTED state"));
        vosStatus = csrNeighborRoamIssueNeighborRptRequest(pMac);
        if (VOS_STATUS_SUCCESS != vosStatus)
        {
            smsLog(pMac, LOGE, FL("Neighbor report request failed. status = %d"), vosStatus);
            return;
        }
        /*                                                                                           */
        pNeighborRoamInfo->FTRoamInfo.currentNeighborRptRetryNum++;
        pNeighborRoamInfo->FTRoamInfo.neighborRptPending = eANI_BOOLEAN_TRUE;
        CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REPORT_QUERY)
    }
    else
#endif      
    {
        NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("Non 11R or ESE Association:results refresh timer expired"));
        vosStatus = csrNeighborRoamTransitToCFGChanScan(pMac);
        if (VOS_STATUS_SUCCESS != vosStatus)
        {
            return;
        }
    }
    return;
}

/*                                                                            

                                              

                                                                       
                                                            

                                                                               

                

                                                                           */

void csrForcedInitialRoamTo5GHTimerCallback(void *context)
{
    tCsrTimerInfo  *pInfo = (tCsrTimerInfo *)context;
    tpAniSirGlobal pMac = pInfo->pMac;
    eHalStatus status = eHAL_STATUS_SUCCESS;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

    NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("forcedInitialRoamTo5GHTimer timer expired"));

    //                                        
    vos_timer_stop(&pNeighborRoamInfo->forcedInitialRoamTo5GHTimer);

    //                                               
    if (eCSR_NEIGHBOR_ROAM_STATE_CONNECTED != pNeighborRoamInfo->neighborRoamState)
    {
        smsLog(pMac, LOGE, FL("Received in not CONNECTED state. Ignore it"));
        return;
    }

    //                                                                  
    //                                     
    if(GetRFBand(pMac->roam.neighborRoamInfo.currAPoperationChannel) == SIR_BAND_5_GHZ)
    {
        smsLog(pMac, LOGE,
               FL("DUT is already connected to 5GH ap, so no need to trigger forced roam."));
        return;
    }

    //                                                                 
    pNeighborRoamInfo->isForcedInitialRoamTo5GH = 1;

    //                                                         
    //            
    status = csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_STOP,
                                REASON_INITIAL_FORCED_ROAM_TO_5G);
    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("csrRoamOffloadScan stop scan cmd got failed status = %d"), status);
        return;
    }

    //                                                         
    //                                                       
    status = csrNeighborRoamTransitToCFGChanScan(pMac);
    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE,
               FL("csrNeighborRoamTransitToCFGChanScan failed status=%d"), status);
         //                                
         csrNeighborRoamStartLfrScan(pMac, REASON_INITIAL_FORCED_ROAM_TO_5G);
    }
}

#if defined WLAN_FEATURE_VOWIFI_11R && defined WLAN_FEATURE_VOWIFI
/*                                                                            

                                              

                                                                                       
                                                                                          
                                                             

                                                  

                                                                             

                                                                           */
VOS_STATUS csrNeighborRoamIssueNeighborRptRequest(tpAniSirGlobal pMac)
{
    tRrmNeighborRspCallbackInfo callbackInfo;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tRrmNeighborReq neighborReq;


    neighborReq.no_ssid = 0;

    /*                  */
    neighborReq.ssid.length = pMac->roam.roamSession[pNeighborRoamInfo->csrSessionId].connectedProfile.SSID.length;
    vos_mem_copy(neighborReq.ssid.ssId, pMac->roam.roamSession[pNeighborRoamInfo->csrSessionId].connectedProfile.SSID.ssId, 
                                    pMac->roam.roamSession[pNeighborRoamInfo->csrSessionId].connectedProfile.SSID.length);
    
    callbackInfo.neighborRspCallback = csrNeighborRoamRRMNeighborReportResult;
    callbackInfo.neighborRspCallbackContext = pMac;
    callbackInfo.timeout = pNeighborRoamInfo->FTRoamInfo.neighborReportTimeout;

    return sme_NeighborReportRequest(pMac,(tANI_U8) pNeighborRoamInfo->csrSessionId, &neighborReq, &callbackInfo);
}

/*                                                                            

                                           

                                                            
                                            

                                                  
                                                      
                                                                             
                                                        
                                                                               
                                                                                                 
                                                                                       

                                                                             

                                                                           */

VOS_STATUS csrNeighborRoamChannelsFilterByBand(
                      tpAniSirGlobal pMac,
                      tANI_U8*  pInputChannelList,
                      tANI_U8   inputNumOfChannels,
                      tANI_U8*  pOutputChannelList,
                      tANI_U8*  pMergedOutputNumOfChannels,
                      tSirRFBand band
                      )
{
    tANI_U8 i = 0;
    tANI_U8 numChannels = 0;

    //                       
    if (!pInputChannelList) return VOS_STATUS_E_INVAL;

    //                       
    if (!pOutputChannelList) return VOS_STATUS_E_INVAL;

    if (inputNumOfChannels > WNI_CFG_VALID_CHANNEL_LIST_LEN)
    {
         VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_ERROR,
             "%s: Wrong Number of Input Channels %d",
             __func__, inputNumOfChannels);
         return VOS_STATUS_E_INVAL;
    }
    for (i = 0; i < inputNumOfChannels; i++)
    {
        if (band == GetRFBand(pInputChannelList[i]))
        {
            pOutputChannelList[numChannels] = pInputChannelList[i];
            numChannels++;
        }
    }

    //                                
    *pMergedOutputNumOfChannels = numChannels;

    return VOS_STATUS_SUCCESS;
}

/*                                                                            

                                         

                                                            
                                                                      
                                                                                

                                                  
                                                                                                 
                                                                   
                                                                            
                                                                                                
                                                                                                   

                                                                             

                                                                           */
VOS_STATUS csrNeighborRoamMergeChannelLists( 
        tpAniSirGlobal pMac, 
        tANI_U8   *pInputChannelList, 
        tANI_U8  inputNumOfChannels,
        tANI_U8   *pOutputChannelList,
        tANI_U8  outputNumOfChannels,
        tANI_U8  *pMergedOutputNumOfChannels
        )
{
    tANI_U8 i = 0;
    tANI_U8 j = 0;
    tANI_U8 numChannels = outputNumOfChannels;

    //                       
    if (!pInputChannelList) return VOS_STATUS_E_INVAL;

    //                       
    if (!pOutputChannelList) return VOS_STATUS_E_INVAL;

    if (inputNumOfChannels > WNI_CFG_VALID_CHANNEL_LIST_LEN)
    {
         VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_ERROR,
             "%s: Wrong Number of Input Channels %d",
             __func__, inputNumOfChannels);
         return VOS_STATUS_E_INVAL;
    }
    if (outputNumOfChannels > WNI_CFG_VALID_CHANNEL_LIST_LEN)
    {
         VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_ERROR,
             "%s: Wrong Number of Output Channels %d",
             __func__, inputNumOfChannels);
         return VOS_STATUS_E_INVAL;
    }

    /*                                                                        
                                                                            
                            */
    for (i = 0; (i < inputNumOfChannels) && (numChannels < WNI_CFG_VALID_CHANNEL_LIST_LEN); i++)
    {
        for (j = 0; j < outputNumOfChannels; j++)
        {
            if (pInputChannelList[i] == pOutputChannelList[j])
                break;
        }
        if (j == outputNumOfChannels)
        {
            if (pInputChannelList[i])
            {
                VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO, 
                        "%s: [INFOLOG] Adding extra %d to Neighbor channel list", __func__,
                        pInputChannelList[i]); 
                pOutputChannelList[numChannels] = pInputChannelList[i]; 
                numChannels++; 
            }
        }
    }

    //                                
    *pMergedOutputNumOfChannels = numChannels; 

    return VOS_STATUS_SUCCESS;
}

/*                                                                            

                                                       

                                                                              
                                                                                    
                                                                                
                                       

                                                  

                                                                             

                                                                           */
VOS_STATUS csrNeighborRoamCreateChanListFromNeighborReport(tpAniSirGlobal pMac)
{
    tpRrmNeighborReportDesc       pNeighborBssDesc;
    tpCsrNeighborRoamControlInfo  pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tANI_U8                       numChannels = 0;
    tANI_U8                       i = 0;
    tANI_U8                       channelList[MAX_BSS_IN_NEIGHBOR_RPT];
    tANI_U8                       mergedOutputNumOfChannels = 0;

    /*                                                                                           */
    pNeighborRoamInfo->FTRoamInfo.numBssFromNeighborReport = 0;

    pNeighborBssDesc = smeRrmGetFirstBssEntryFromNeighborCache(pMac);

    while (pNeighborBssDesc)
    {
        if (pNeighborRoamInfo->FTRoamInfo.numBssFromNeighborReport >= MAX_BSS_IN_NEIGHBOR_RPT) break;
        
        /*                                                      */
        pNeighborRoamInfo->FTRoamInfo.neighboReportBssInfo[pNeighborRoamInfo->FTRoamInfo.numBssFromNeighborReport].channelNum = 
                                    pNeighborBssDesc->pNeighborBssDescription->channel;
        pNeighborRoamInfo->FTRoamInfo.neighboReportBssInfo[pNeighborRoamInfo->FTRoamInfo.numBssFromNeighborReport].neighborScore = 
                                    (tANI_U8)pNeighborBssDesc->roamScore;
        vos_mem_copy(pNeighborRoamInfo->FTRoamInfo.neighboReportBssInfo[pNeighborRoamInfo->FTRoamInfo.numBssFromNeighborReport].neighborBssId,
                                     pNeighborBssDesc->pNeighborBssDescription->bssId, sizeof(tSirMacAddr));
        pNeighborRoamInfo->FTRoamInfo.numBssFromNeighborReport++;

        /*                                         */
        for (i = 0; (i < numChannels && i < MAX_BSS_IN_NEIGHBOR_RPT); i++)
        {
            if (pNeighborBssDesc->pNeighborBssDescription->channel == channelList[i])
                break;
        }

        if (i == numChannels)
        {
            if (pNeighborBssDesc->pNeighborBssDescription->channel)
            {
                if (CSR_IS_ROAM_INTRA_BAND_ENABLED(pMac))
                {
                    //                                           
                    if (GetRFBand(pNeighborRoamInfo->currAPoperationChannel) ==
                        GetRFBand(pNeighborBssDesc->pNeighborBssDescription->channel))
                    {
                        VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                                   "%s: [INFOLOG] Adding %d to Neighbor channel list (Same band)\n", __func__,
                                    pNeighborBssDesc->pNeighborBssDescription->channel);
                        channelList[numChannels] = pNeighborBssDesc->pNeighborBssDescription->channel;
                        numChannels++;
                    }
                }
                else
                {
                    VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                                "%s: [INFOLOG] Adding %d to Neighbor channel list\n", __func__,
                                pNeighborBssDesc->pNeighborBssDescription->channel);
                    channelList[numChannels] = pNeighborBssDesc->pNeighborBssDescription->channel;
                    numChannels++;
                }
            }
        }
            
        pNeighborBssDesc = smeRrmGetNextBssEntryFromNeighborCache(pMac, pNeighborBssDesc);
    }

    if (pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList)
    {
        vos_mem_free(pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList);
    }

    pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = NULL;
    pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels = 0;
    /*                                                                        */
    if (numChannels)
        pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = vos_mem_malloc((numChannels) * sizeof(tANI_U8));
    if (NULL == pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList)
    {
        smsLog(pMac, LOGE, FL("Memory allocation for Channel list failed.. TL event ignored"));
        return VOS_STATUS_E_RESOURCES;
    }

    vos_mem_copy(pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList, 
                                            channelList, (numChannels) * sizeof(tANI_U8));
    pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels = numChannels;
    /*
                                                                                        
                                                                                         
                                                                                         
       */
    if (pMac->scan.occupiedChannels.numChannels)
    {
       csrNeighborRoamMergeChannelLists(pMac,
                  &pMac->scan.occupiedChannels.channelList[0],
                  pMac->scan.occupiedChannels.numChannels,
                  &pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList[0],
                  pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels,
                  &mergedOutputNumOfChannels);
       pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels =
                  mergedOutputNumOfChannels;

    }
    /*                                                                          
                                                                                
                                            */
    if (numChannels)
    {
        smsLog(pMac, LOG1, FL("IAPP Neighbor list callback received as expected"
               "in state %s."),
               macTraceGetNeighbourRoamState(
               pNeighborRoamInfo->neighborRoamState));
        pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived = eANI_BOOLEAN_TRUE;
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        if (csrRoamIsRoamOffloadScanEnabled(pMac))
        {
           csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_UPDATE_CFG, REASON_CHANNEL_LIST_CHANGED);
        }
#endif
    }
    pNeighborRoamInfo->roamChannelInfo.currentChanIndex = 0;
    pNeighborRoamInfo->roamChannelInfo.chanListScanInProgress = eANI_BOOLEAN_TRUE;
    
    return VOS_STATUS_SUCCESS;
}

/*                                                                            

                                              

                                                                                  
                                                                                
                                                                                
                                                                 
                               

                                                     
                                                               

                

                                                                           */
void csrNeighborRoamRRMNeighborReportResult(void *context, VOS_STATUS vosStatus)
{
    tpAniSirGlobal pMac = PMAC_STRUCT(context);
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus  status = eHAL_STATUS_SUCCESS;

    smsLog(pMac, LOG1, FL("Neighbor report result callback with status = %d"), vosStatus);
    switch (pNeighborRoamInfo->neighborRoamState)
    {
        case eCSR_NEIGHBOR_ROAM_STATE_REPORT_QUERY:
            /*                                   */
            pNeighborRoamInfo->FTRoamInfo.neighborRptPending = eANI_BOOLEAN_FALSE;
            if (VOS_STATUS_SUCCESS == vosStatus)
            {
                /*                                                                                               */
                vosStatus = csrNeighborRoamCreateChanListFromNeighborReport(pMac);
                if (VOS_STATUS_SUCCESS == vosStatus)
                {
                    NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("Channel List created from Neighbor report, Transitioning to NEIGHBOR_SCAN state"));
                }

                /*                                                                                                */
                pNeighborRoamInfo->scanRequestTimeStamp = (tANI_TIMESTAMP)palGetTickCount(pMac->hHdd);
                
                /*                                                               */
                /*                                                                                                       
                                              */
                status = vos_timer_start(&pNeighborRoamInfo->neighborScanTimer,
                                pNeighborRoamInfo->cfgParams.neighborScanPeriod);
                if (eHAL_STATUS_SUCCESS != status)
                {
                    /*                                               */
                    smsLog(pMac, LOGE, FL("PAL Timer start for neighbor scan timer failed, status = %d, Ignoring state transition"), status);
                    vos_mem_free(pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList);
                    pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = NULL;
                    pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels = 0;
                    return;
                }
                pNeighborRoamInfo->FTRoamInfo.currentNeighborRptRetryNum = 0;                
                /*                                                              */
                CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN)
            }
            else
            {
                /*                                                                                                 
                                                                                                         */
                smsLog(pMac, LOGE, FL("Neighbor report result failed after %d retries, MAX RETRIES = %d"),
                     pNeighborRoamInfo->FTRoamInfo.currentNeighborRptRetryNum, pNeighborRoamInfo->cfgParams.maxNeighborRetries);
                if (pNeighborRoamInfo->FTRoamInfo.currentNeighborRptRetryNum >= 
                        pNeighborRoamInfo->cfgParams.maxNeighborRetries)
                {
                    smsLog(pMac, LOGE, FL("Bailing out to CFG Channel list scan.. "));
                    vosStatus = csrNeighborRoamTransitToCFGChanScan(pMac);
                    if (VOS_STATUS_SUCCESS != vosStatus)
                    {
                        smsLog(pMac, LOGE, FL("Transit to CFG Channel list scan state failed with status %d "), vosStatus);
                        return;
                    }
                    /*                                                                               */
                    pNeighborRoamInfo->FTRoamInfo.currentNeighborRptRetryNum = 0;
                }
                else
                {
                    vosStatus = csrNeighborRoamIssueNeighborRptRequest(pMac);
                    if (VOS_STATUS_SUCCESS != vosStatus)
                    {
                        smsLog(pMac, LOGE, FL("Neighbor report request failed. status = %d"), vosStatus);
                        return;
                    }
                    pNeighborRoamInfo->FTRoamInfo.neighborRptPending = eANI_BOOLEAN_TRUE;
                    /*                                                                                           */
                    pNeighborRoamInfo->FTRoamInfo.currentNeighborRptRetryNum++;
                }
            }
            break;
        default:
            smsLog(pMac, LOGE, FL("Neighbor result callback not expected in"
                   "state %s, Ignoring.."),
                   macTraceGetNeighbourRoamState(
                   pNeighborRoamInfo->neighborRoamState));
            break;
    }
    return;
}
#endif /*                         */


#ifdef FEATURE_WLAN_LFR 
tANI_BOOLEAN csrNeighborRoamIsSsidAndSecurityMatch(
        tpAniSirGlobal pMac, 
        tCsrRoamConnectedProfile *pCurProfile,
        tSirBssDescription *pBssDesc,
        tDot11fBeaconIEs *pIes)
{
    tCsrAuthList authType;
    tCsrEncryptionList uCEncryptionType;
    tCsrEncryptionList mCEncryptionType;
    tANI_BOOLEAN fMatch = FALSE;

    authType.numEntries = 1;
    authType.authType[0] = pCurProfile->AuthType;
    uCEncryptionType.numEntries = 1;
    uCEncryptionType.encryptionType[0] = pCurProfile->EncryptionType;
    mCEncryptionType.numEntries = 1;
    mCEncryptionType.encryptionType[0] = pCurProfile->mcEncryptionType;

    if( pIes )
    {
        if(pIes->SSID.present)
        {
            fMatch = csrIsSsidMatch( pMac,
                    (void *)pCurProfile->SSID.ssId, pCurProfile->SSID.length,
                    pIes->SSID.ssid, pIes->SSID.num_ssid,
                    eANI_BOOLEAN_TRUE );
            if(TRUE == fMatch)
            {
                /*
                                                                         
                                                                    
                                                                    
                                    
                  
                                                                       
                                                        
                 */
                fMatch = csrIsSecurityMatch(pMac, &authType, &uCEncryptionType,
                                            &mCEncryptionType,
                                            NULL, NULL, NULL,
                                            pBssDesc, pIes, NULL, NULL, NULL);
                return (fMatch);
            }
            else
            {
                return (fMatch);
            }

        }
        else
        {
            return FALSE;  //                                     
        }
    }
    else
    {
        return FALSE;  //                                          
    }
}

tANI_BOOLEAN csrNeighborRoamIsNewConnectedProfile(
        tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tANI_U8 sessionId   = (tANI_U8)pNeighborRoamInfo->csrSessionId;
    tCsrRoamConnectedProfile *pCurrProfile = NULL;
    tCsrRoamConnectedProfile *pPrevProfile = NULL;
    tDot11fBeaconIEs *pIes = NULL;
    tSirBssDescription *pBssDesc = NULL;
    tANI_BOOLEAN fNew = TRUE;

    if(!(pMac->roam.roamSession && CSR_IS_SESSION_VALID(pMac, sessionId)))
    {
        return (fNew);
    }

    pCurrProfile = &pMac->roam.roamSession[sessionId].connectedProfile;
    if( !pCurrProfile )
    {
        return (fNew);
}

    pPrevProfile = &pNeighborRoamInfo->prevConnProfile;
    if( !pPrevProfile )
    {
        return (fNew);
    }

    pBssDesc = pPrevProfile->pBssDesc;
    if (pBssDesc)
    {
        if (HAL_STATUS_SUCCESS(csrGetParsedBssDescriptionIEs(pMac,
            pBssDesc, &pIes)) &&
            csrNeighborRoamIsSsidAndSecurityMatch(pMac, pCurrProfile, pBssDesc, pIes))
        {
            fNew = FALSE;
        }
        if (pIes)
        {
            vos_mem_free(pIes);
        }
    }

    if (fNew)
    {
        smsLog(pMac, LOG1, FL("Prev roam profile did not match current"));
    }
    else
    {
        smsLog(pMac, LOG1, FL("Prev roam profile matches current"));
    }

    return (fNew);
}

tANI_BOOLEAN csrNeighborRoamConnectedProfileMatch(
        tpAniSirGlobal pMac,
        tCsrScanResult *pResult,
        tDot11fBeaconIEs *pIes)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tANI_U8 sessionId   = (tANI_U8)pNeighborRoamInfo->csrSessionId;
    tCsrRoamConnectedProfile *pCurProfile = NULL;
    tSirBssDescription *pBssDesc = &pResult->Result.BssDescriptor;

    if( !(pMac->roam.roamSession
            && CSR_IS_SESSION_VALID(pMac, sessionId)))
    {
        return FALSE;
    }

    pCurProfile = &pMac->roam.roamSession[sessionId].connectedProfile;

    if( !pCurProfile)
    {
        return FALSE;
    }

    return csrNeighborRoamIsSsidAndSecurityMatch(pMac, pCurProfile, pBssDesc, pIes);
}

/*                                                                            

                                                    

                                                                                
                                                                                 
                 

                                                  
                                                          
                                                                                
                                                                                
                                                                                           

                                                                             

                                                                           */
VOS_STATUS csrNeighborRoamPrepareNonOccupiedChannelList(
        tpAniSirGlobal pMac, 
        tANI_U8   *pInputChannelList, 
        tANI_U8 numOfChannels,
        tANI_U8   *pOutputChannelList,
        tANI_U8 *pOutputNumOfChannels
        )
{
    tANI_U8 i = 0;
    tANI_U8 outputNumOfChannels  = 0; //                                    
    tANI_U8 numOccupiedChannels = pMac->scan.occupiedChannels.numChannels;
    tANI_U8 *pOccupiedChannelList = pMac->scan.occupiedChannels.channelList;

    for (i = 0; (i < numOfChannels &&(i < WNI_CFG_VALID_CHANNEL_LIST_LEN)); i++)
    {
        if (!csrIsChannelPresentInList(pOccupiedChannelList, numOccupiedChannels,
             pInputChannelList[i]))
        {
           /*                                                    
                                              */
            if (CSR_IS_CHANNEL_DFS(pInputChannelList[i]))
            {
                if (pMac->roam.configParam.allowDFSChannelRoam == TRUE)
                {
                    pOutputChannelList[outputNumOfChannels++] = pInputChannelList[i];
                }
            }
            else
            {
                pOutputChannelList[outputNumOfChannels++] = pInputChannelList[i];
            }
        }
    }

    smsLog(pMac, LOG2, FL("Number of channels in the valid channel list=%d; "
           "Number of channels in the non-occupied list list=%d"),
            numOfChannels, outputNumOfChannels);

    //                              
    *pOutputNumOfChannels = outputNumOfChannels; 

    return eHAL_STATUS_SUCCESS;
}
#endif /*                  */

/*                                                                            

                                           

                                                                                    
                                                                                     
                                                                                     
                                                                              

                                                  

                                                                             

                                                                           */
VOS_STATUS csrNeighborRoamTransitToCFGChanScan(tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus  status  = eHAL_STATUS_SUCCESS;
    int i = 0;
    tANI_U8   numOfChannels = 0;
    tANI_U8   channelList[WNI_CFG_VALID_CHANNEL_LIST_LEN];
    tpCsrChannelInfo    currChannelListInfo;
    tANI_U8   scanChannelList[WNI_CFG_VALID_CHANNEL_LIST_LEN];
    int       outputNumOfChannels = 0;
#ifdef FEATURE_WLAN_LFR
    tANI_U32 sessionId = pNeighborRoamInfo->csrSessionId;
#endif
    currChannelListInfo = &pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo;

    if ( 
#ifdef FEATURE_WLAN_ESE
        ((pNeighborRoamInfo->isESEAssoc) &&
                    (pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived == eANI_BOOLEAN_FALSE)) ||
        (pNeighborRoamInfo->isESEAssoc == eANI_BOOLEAN_FALSE) ||
#endif //    
        currChannelListInfo->numOfChannels == 0)
    {
        smsLog(pMac, LOGW, FL("Building channel list to scan"));


        /*                                                                                           
                                                                                                                 
                                        */
        if (NULL != currChannelListInfo->ChannelList)
        {
            vos_mem_free(currChannelListInfo->ChannelList);
            currChannelListInfo->ChannelList = NULL;
            currChannelListInfo->numOfChannels = 0;
        }

        //                                                                                         
        //                                                                                                         
        if (0 != pNeighborRoamInfo->cfgParams.channelInfo.numOfChannels)
        {
            //                                                                                                    
            NEIGHBOR_ROAM_DEBUG(pMac, LOGE, "Using the channel list from cfg.ini");
            status = csrNeighborRoamMergeChannelLists( 
                    pMac, 
                    pNeighborRoamInfo->cfgParams.channelInfo.ChannelList, 
                    pNeighborRoamInfo->cfgParams.channelInfo.numOfChannels, 
                    channelList, 
                    0, //                                                                
                    &numOfChannels );

            if (CSR_IS_ROAM_INTRA_BAND_ENABLED(pMac))
            {
                csrNeighborRoamChannelsFilterByBand(
                             pMac,
                             pNeighborRoamInfo->cfgParams.channelInfo.ChannelList,
                             pNeighborRoamInfo->cfgParams.channelInfo.numOfChannels,
                             channelList,
                             &numOfChannels,
                             GetRFBand(pMac->roam.neighborRoamInfo.currAPoperationChannel));
            }
            if(numOfChannels > WNI_CFG_VALID_CHANNEL_LIST_LEN)
            {
                smsLog(pMac, LOGE, FL("Received wrong number of Channel list"));
                return VOS_STATUS_E_INVAL;
            }
            /*                                                     
                                                    */
            if ( pMac->roam.configParam.allowDFSChannelRoam == FALSE)
            {
                for (i=0; i<numOfChannels; i++)
                {
                    if ( !(CSR_IS_CHANNEL_DFS(channelList[i])))
                    {
                         scanChannelList[outputNumOfChannels++] = channelList[i];
                    }
                }
            }
            else
            {   /*                                                 */
                vos_mem_copy(scanChannelList,
                          channelList,
                          numOfChannels * sizeof(tANI_U8));
                outputNumOfChannels = numOfChannels;
            }
            currChannelListInfo->ChannelList =
                vos_mem_malloc(outputNumOfChannels*sizeof(tANI_U8));
            if (NULL == currChannelListInfo->ChannelList)
            {
                smsLog(pMac, LOGE, FL("Memory allocation for Channel list failed"));
                return VOS_STATUS_E_RESOURCES;
            }
            vos_mem_copy(currChannelListInfo->ChannelList,
                  scanChannelList, outputNumOfChannels * sizeof(tANI_U8));
        } 
        else if(pNeighborRoamInfo->isForcedInitialRoamTo5GH)
        {
            NEIGHBOR_ROAM_DEBUG(pMac, LOG1, "Forced roam to 5G cfg chain list");

            pNeighborRoamInfo->scanRequestTimeStamp = (tANI_TIMESTAMP)palGetTickCount(pMac->hHdd);
            /*                                                                         
                                                                        */
            csrScanFlushSelectiveResultForBand(pMac, VOS_FALSE, SIR_BAND_5_GHZ);

            status = csrNeighborRoamScanForInitialForced5GRoaming(pMac, sessionId);
            if(status != eHAL_STATUS_SUCCESS)
                return VOS_STATUS_E_FAILURE;

            /*                                  */
            CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN);

            return VOS_STATUS_SUCCESS;
        }
#ifdef FEATURE_WLAN_LFR
        else if ((pNeighborRoamInfo->uScanMode == DEFAULT_SCAN) &&
                 (abs(pNeighborRoamInfo->lookupDOWNRssi) >
                  abs(pNeighborRoamInfo->cfgParams.neighborReassocThreshold)))
        {
            /* 
                                                                 
                                                                     
                                                                    
                                                           
             */
            NEIGHBOR_ROAM_DEBUG(pMac, LOGW, "Triggering contiguous scan "
                "(lookupDOWNRssi=%d,reassocThreshold=%d)",
                pNeighborRoamInfo->lookupDOWNRssi,
                pNeighborRoamInfo->cfgParams.neighborReassocThreshold*(-1));

            pNeighborRoamInfo->scanRequestTimeStamp = (tANI_TIMESTAMP)palGetTickCount(pMac->hHdd);

            vos_timer_stop(&pNeighborRoamInfo->neighborScanTimer);

            /*                                           
                                                   */
            csrScanFlushSelectiveResult(pMac, VOS_FALSE);

            csrNeighborRoamPerformContiguousBgScan(pMac, sessionId);

            /*                                  */
            CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN);

            return VOS_STATUS_SUCCESS;
        }
#endif
        else
        {
            numOfChannels = pMac->scan.occupiedChannels.numChannels;
            if (numOfChannels > WNI_CFG_VALID_CHANNEL_LIST_LEN)
            {
                numOfChannels = WNI_CFG_VALID_CHANNEL_LIST_LEN;
            }
            if (numOfChannels
#ifdef FEATURE_WLAN_LFR
                && ((pNeighborRoamInfo->uScanMode == SPLIT_SCAN_OCCUPIED_LIST) ||
                    (pNeighborRoamInfo->uEmptyScanCount == 0) ||
                    ((pNeighborRoamInfo->uEmptyScanCount % 2) == 1))
#endif
                )
            {
                /*
                                                                    
                                                            
                 */
                NEIGHBOR_ROAM_DEBUG(pMac, LOG2, "Switching to occupied channel list"
#ifdef FEATURE_WLAN_LFR
                    "-uScanMode=%d, uEmptyScanCount=%d",
                    pNeighborRoamInfo->uScanMode,
                    pNeighborRoamInfo->uEmptyScanCount
#endif
                 );
                if (CSR_IS_ROAM_INTRA_BAND_ENABLED(pMac))
                {
                    csrNeighborRoamChannelsFilterByBand(
                                 pMac,
                                 pMac->scan.occupiedChannels.channelList,
                                 numOfChannels,
                                 channelList,
                                 &numOfChannels,
                                 GetRFBand(pMac->roam.neighborRoamInfo.currAPoperationChannel));
                }
                else
                {
                    vos_mem_copy(channelList,
                            pMac->scan.occupiedChannels.channelList,
                            numOfChannels * sizeof(tANI_U8));
                }
                /*                                                     
                                                          */
                if ( pMac->roam.configParam.allowDFSChannelRoam == FALSE)
                {
                   for (i=0; i<numOfChannels; i++)
                   {
                       if ( !(CSR_IS_CHANNEL_DFS(channelList[i])))
                       {
                            scanChannelList[outputNumOfChannels++] = channelList[i];
                       }
                   }
                }
                else
                {
                    vos_mem_copy(scanChannelList,
                            channelList,
                            numOfChannels * sizeof(tANI_U8));
                    outputNumOfChannels = numOfChannels;
                }

                currChannelListInfo->ChannelList = vos_mem_malloc(outputNumOfChannels * sizeof(tANI_U8));
                if (NULL == currChannelListInfo->ChannelList)
                {
                    smsLog(pMac, LOGE, FL("Memory allocation for Channel list failed"));
                    return VOS_STATUS_E_RESOURCES;
                }
                vos_mem_copy(currChannelListInfo->ChannelList,
                        scanChannelList,
                        outputNumOfChannels * sizeof(tANI_U8));
            }
            else
            {
                /*                                          */
                NEIGHBOR_ROAM_DEBUG(pMac, LOG2, "Get valid channel list");
                numOfChannels = sizeof(pMac->roam.validChannelList);

                if(HAL_STATUS_SUCCESS(csrGetCfgValidChannels(pMac,
                                (tANI_U8 *)pMac->roam.validChannelList,
                                (tANI_U32 *) &numOfChannels)))
            {
#ifdef FEATURE_WLAN_LFR
                /*
                                                                  
                                                                   
                                 
                 */
                NEIGHBOR_ROAM_DEBUG(pMac, LOG1, "Switching to non-occupied channel list");
                status = csrNeighborRoamPrepareNonOccupiedChannelList(pMac,
                            (tANI_U8 *)pMac->roam.validChannelList,
                            numOfChannels,
                            channelList,
                            &numOfChannels);
#else
                NEIGHBOR_ROAM_DEBUG(pMac, LOG2, "Merging channel list");
                status = csrNeighborRoamMergeChannelLists( 
                            pMac,
                            (tANI_U8 *)pMac->roam.validChannelList,
                            numOfChannels,   //                                               
                            channelList,
                            0, //                                                                
                            &numOfChannels ); //                                                                       
#endif
            }
            else
            {
                smsLog(pMac, LOGE, FL("Could not get valid channel list"));
                return VOS_STATUS_E_FAILURE;
            }

            if (CSR_IS_ROAM_INTRA_BAND_ENABLED(pMac))
            {
                    csrNeighborRoamChannelsFilterByBand(
                             pMac,
                             (tANI_U8 *)pMac->roam.validChannelList,
                             numOfChannels,
                             channelList,
                                 &numOfChannels,
                                 GetRFBand(pMac->roam.neighborRoamInfo.currAPoperationChannel));
            }

            if (numOfChannels > WNI_CFG_VALID_CHANNEL_LIST_LEN)
            {
                numOfChannels = WNI_CFG_VALID_CHANNEL_LIST_LEN;
            }
            currChannelListInfo->ChannelList =
                vos_mem_malloc(numOfChannels*sizeof(tANI_U8));

            if (NULL == currChannelListInfo->ChannelList)
            {
                smsLog(pMac, LOGE, FL("Memory allocation for Channel list failed"));
                return VOS_STATUS_E_RESOURCES;
            }
#ifdef FEATURE_WLAN_LFR
            vos_mem_copy(currChannelListInfo->ChannelList,
                    channelList, numOfChannels * sizeof(tANI_U8));
#else
            vos_mem_copy(currChannelListInfo->ChannelList,
                    (tANI_U8 *)pMac->roam.validChannelList,
                    numOfChannels * sizeof(tANI_U8));
#endif
            }
        }

        /*                                            */
        currChannelListInfo->numOfChannels = numOfChannels;
        NEIGHBOR_ROAM_DEBUG(pMac, LOGW, 
            "Number of channels from CFG (or) (non-)occupied list=%d",
            currChannelListInfo->numOfChannels);
        for (i = 0; i < currChannelListInfo->numOfChannels; i++)
        {
            NEIGHBOR_ROAM_DEBUG(pMac, LOGW, "Channel List from CFG (or) (non-)occupied list"
                    "= %d", currChannelListInfo->ChannelList[i]);
        }
    }

    /*                                                                                                */
    pNeighborRoamInfo->scanRequestTimeStamp = (tANI_TIMESTAMP)palGetTickCount(pMac->hHdd);
    
    vos_timer_stop(&pNeighborRoamInfo->neighborScanTimer);
    /*                                                                                                       
                                       */
    status = vos_timer_start(&pNeighborRoamInfo->neighborScanTimer,
                    pNeighborRoamInfo->cfgParams.neighborScanPeriod);
    
    if (eHAL_STATUS_SUCCESS != status)
    {
        /*                       */
        smsLog(pMac, LOGE, FL("Neighbor scan PAL Timer start failed, status = %d, Ignoring state transition"), status);
        vos_mem_free(currChannelListInfo->ChannelList);
        currChannelListInfo->ChannelList = NULL;
        currChannelListInfo->numOfChannels = 0;
        return VOS_STATUS_E_FAILURE;
    }
    
    pNeighborRoamInfo->roamChannelInfo.currentChanIndex = 0;
    pNeighborRoamInfo->roamChannelInfo.chanListScanInProgress = eANI_BOOLEAN_TRUE;
    /*                                           
                                           */
    csrScanFlushSelectiveResult(pMac, VOS_FALSE);

    /*                                          
                                                   */
    csrNeighborRoamPurgePreauthFailedList(pMac);
    
    /*                                        */
    CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN)

    return VOS_STATUS_SUCCESS;
}

/*                                                                            

                                            

                                                                                  
                                                                                      
                                                             

                                                  

                                                                             

                                                                           */
VOS_STATUS  csrNeighborRoamNeighborLookupUpEvent(tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    VOS_STATUS  vosStatus;
    csrNeighborRoamDeregAllRssiIndication(pMac);

    /*                                            */
    if ((pNeighborRoamInfo->neighborRoamState != eCSR_NEIGHBOR_ROAM_STATE_CONNECTED)
        && (pNeighborRoamInfo->neighborRoamState != eCSR_NEIGHBOR_ROAM_STATE_REASSOCIATING))
        CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_CONNECTED)
#ifdef FEATURE_WLAN_LFR
    if (!csrRoamIsFastRoamEnabled(pMac,pMac->roam.neighborRoamInfo.csrSessionId))
    {
        smsLog(pMac, LOGE, FL("Received when fast roam is disabled. Ignore it"));
        return eHAL_STATUS_SUCCESS;
    }
#endif
    /*                                                                                                                          */
    csrNeighborRoamResetConnectedStateControlInfo(pMac);

    
    NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Registering DOWN event neighbor lookup callback with TL. RSSI = %d,"), pNeighborRoamInfo->currentNeighborLookupThreshold * (-1));
    /*                                                                        */
    vosStatus = WLANTL_RegRSSIIndicationCB(pMac->roam.gVosContext, (v_S7_t)pNeighborRoamInfo->currentNeighborLookupThreshold * (-1),
                                    WLANTL_HO_THRESHOLD_DOWN, 
                                    csrNeighborRoamNeighborLookupDOWNCallback, 
                                    VOS_MODULE_ID_SME, pMac);
#ifdef FEATURE_WLAN_LFR
    pNeighborRoamInfo->lookupDOWNRssi = 0;
#endif
    if(!VOS_IS_STATUS_SUCCESS(vosStatus))
    {
       //       
       smsLog(pMac, LOGW, FL(" Couldn't register csrNeighborRoamNeighborLookupCallback DOWN event with TL: Status = %d"), vosStatus);
    }


    return vosStatus;
}

/*                                                                            

                                              

                                                                                  
                                                                                          
                                                                                          
                                  

                                                  

                                                                             

                                                                           */
VOS_STATUS  csrNeighborRoamNeighborLookupDownEvent(tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    VOS_STATUS  vosStatus = VOS_STATUS_SUCCESS;
    eHalStatus  status = eHAL_STATUS_SUCCESS;

    switch (pNeighborRoamInfo->neighborRoamState)
    {
        case eCSR_NEIGHBOR_ROAM_STATE_CONNECTED:
            
            NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Deregistering DOWN event neighbor lookup callback with TL. RSSI = %d,"),
                                                            pNeighborRoamInfo->currentNeighborLookupThreshold * (-1));
            /*                                                        */
            vosStatus = WLANTL_DeregRSSIIndicationCB(pMac->roam.gVosContext, (v_S7_t)pNeighborRoamInfo->currentNeighborLookupThreshold * (-1),
                                            WLANTL_HO_THRESHOLD_DOWN, 
                                            csrNeighborRoamNeighborLookupDOWNCallback, 
                                            VOS_MODULE_ID_SME);
            
            if(!VOS_IS_STATUS_SUCCESS(vosStatus))
            {
               //       
               smsLog(pMac, LOGW, FL(" Couldn't Deregister csrNeighborRoamNeighborLookupCallback DOWN event from TL: Status = %d"), vosStatus);
            }
#ifdef FEATURE_WLAN_LFR
            if (!csrRoamIsFastRoamEnabled(pMac,pMac->roam.neighborRoamInfo.csrSessionId))
            {
                smsLog(pMac, LOGE, FL("Received when fast roam is disabled. Ignore it"));
                return eHAL_STATUS_SUCCESS;
            }
#endif
           
#if defined WLAN_FEATURE_VOWIFI_11R && defined WLAN_FEATURE_VOWIFI
            if ((pNeighborRoamInfo->is11rAssoc) && (pMac->rrm.rrmSmeContext.rrmConfig.rrmEnabled))
            {
               
                NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("11R Association:Neighbor Lookup Down event received in CONNECTED state"));
                vosStatus = csrNeighborRoamIssueNeighborRptRequest(pMac);
                if (VOS_STATUS_SUCCESS != vosStatus)
                {
                    smsLog(pMac, LOGE, FL("Neighbor report request failed. status = %d"), vosStatus);
                    return vosStatus;
                }
                /*                                                                                           */
                pNeighborRoamInfo->FTRoamInfo.currentNeighborRptRetryNum++;
                pNeighborRoamInfo->FTRoamInfo.neighborRptPending = eANI_BOOLEAN_TRUE;
                CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REPORT_QUERY)
            }
            else
#endif      
            {
                NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Non 11R or ESE Association:Neighbor Lookup Down event received in CONNECTED state"));

                vosStatus = csrNeighborRoamTransitToCFGChanScan(pMac);
                if (VOS_STATUS_SUCCESS != vosStatus)
                {
                    NEIGHBOR_ROAM_DEBUG(pMac, LOGE, FL("csrNeighborRoamTransitToCFGChanScan failed"
                        " with status=%d"), vosStatus);
                    return vosStatus;
                }
            }
            NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Registering UP event neighbor lookup callback with TL. RSSI = %d,"), NEIGHBOR_ROAM_LOOKUP_UP_THRESHOLD * (-1));
            /*                                                                      */
            vosStatus = WLANTL_RegRSSIIndicationCB(pMac->roam.gVosContext,
                                            (v_S7_t)NEIGHBOR_ROAM_LOOKUP_UP_THRESHOLD * (-1),
                                            WLANTL_HO_THRESHOLD_UP, 
                                            csrNeighborRoamNeighborLookupUPCallback, 
                                            VOS_MODULE_ID_SME, pMac);
            if(!VOS_IS_STATUS_SUCCESS(vosStatus))
            {
               //       
               smsLog(pMac, LOGE, FL(" Couldn't register csrNeighborRoamNeighborLookupCallback UP event with TL: Status = %d"), status);
            }
            break;
        default:
            smsLog(pMac, LOGE, FL("DOWN event received in invalid"
                   "state %s ..Ignoring..."),
                   macTraceGetNeighbourRoamState(
                   pNeighborRoamInfo->neighborRoamState));
            break;
            
    }
    return vosStatus;
}

/*                                                                            

                                               

                                                                              
                                                              

                                  
                                                      
                                                                                                      

                                                                             

                                                                           */
VOS_STATUS csrNeighborRoamNeighborLookupUPCallback (v_PVOID_t pAdapter, v_U8_t rssiNotification,
                                                                               v_PVOID_t pUserCtxt,
                                                                               v_S7_t avgRssi)
{
    tpAniSirGlobal pMac = PMAC_STRUCT( pUserCtxt );
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    VOS_STATUS  vosStatus = eHAL_STATUS_SUCCESS;

    NEIGHBOR_ROAM_DEBUG(pMac, LOGW, FL("Neighbor Lookup UP indication callback called with notification %d Reported RSSI = %d"),
                                       rssiNotification,
                                       avgRssi);

    if(!csrIsConnStateConnectedInfra(pMac, pNeighborRoamInfo->csrSessionId))
    {
       smsLog(pMac, LOGW, "Ignoring the indication as we are not connected");
       return VOS_STATUS_SUCCESS;
    }

    VOS_ASSERT(WLANTL_HO_THRESHOLD_UP == rssiNotification);
    vosStatus = csrNeighborRoamNeighborLookupUpEvent(pMac);
    return vosStatus;
}

/*                                                                            

                                                 

                                                                              
                                                                 

                                  
                                                      
                                                                                                      

                                                                             

                                                                           */
VOS_STATUS csrNeighborRoamNeighborLookupDOWNCallback (v_PVOID_t pAdapter, v_U8_t rssiNotification,
                                                                               v_PVOID_t pUserCtxt,
                                                                               v_S7_t avgRssi)
{
    tpAniSirGlobal pMac = PMAC_STRUCT( pUserCtxt );
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    VOS_STATUS  vosStatus = eHAL_STATUS_SUCCESS;

    NEIGHBOR_ROAM_DEBUG(pMac, LOGW, FL("Neighbor Lookup DOWN indication callback called with notification %d Reported RSSI = %d"),
                               rssiNotification,
                               avgRssi);

#ifdef FEATURE_WLAN_LFR
    pNeighborRoamInfo->lookupDOWNRssi = avgRssi;
#endif
    if(!csrIsConnStateConnectedInfra(pMac, pNeighborRoamInfo->csrSessionId))
    {
       smsLog(pMac, LOGW, "Ignoring the indication as we are not connected");
       return VOS_STATUS_SUCCESS;
    }

    VOS_ASSERT(WLANTL_HO_THRESHOLD_DOWN == rssiNotification);
    vosStatus = csrNeighborRoamNeighborLookupDownEvent(pMac);

    return vosStatus;
}

#ifdef RSSI_HACK
extern int dumpCmdRSSI;
#endif

/*                                                                            

                                         

                                                                                   
                                                                                   
                                                                                    
                                                                           

                                                  
                                                            

                                                                              

                                                                           */
eHalStatus csrNeighborRoamIndicateDisconnect(tpAniSirGlobal pMac, tANI_U8 sessionId)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
#ifdef FEATURE_WLAN_LFR
    tCsrRoamConnectedProfile *pPrevProfile = &pNeighborRoamInfo->prevConnProfile;
#endif
    tCsrRoamSession *pSession = CSR_GET_SESSION( pMac, sessionId);

    if (NULL == pSession)
    {
        smsLog(pMac, LOGE, FL("pSession is NULL "));
        return eHAL_STATUS_FAILURE;
    }
    VOS_TRACE(VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_INFO,
                   FL("Disconnect indication on session %d in state %s"
                      "from BSSID : "
                   MAC_ADDRESS_STR), sessionId,
                   macTraceGetNeighbourRoamState(
                   pNeighborRoamInfo->neighborRoamState),
                   MAC_ADDR_ARRAY(pSession->connectedProfile.bssid));
 
#ifdef FEATURE_WLAN_LFR
    /*                                                                               */
    csrRoamFreeConnectProfile(pMac, pPrevProfile);
    csrRoamCopyConnectProfile(pMac, sessionId, pPrevProfile);
#endif
    if (NULL != pSession)
    {
        if (NULL != pSession->pCurRoamProfile)
        {
            if (VOS_STA_MODE != pMac->roam.roamSession[sessionId].pCurRoamProfile->csrPersona)
            {
                smsLog(pMac, LOGE, FL("Ignoring Disconnect indication received from a non STA persona."
                                      "sessionId: %d, csrPersonna %d"), sessionId,
                       (int)pMac->roam.roamSession[sessionId].pCurRoamProfile->csrPersona);
                return eHAL_STATUS_SUCCESS;
            }
        }

#ifdef FEATURE_WLAN_ESE
        if (pSession->connectedProfile.isESEAssoc)
        {
           vos_mem_copy(&pSession->prevApSSID, &pSession->connectedProfile.SSID,
                        sizeof(tSirMacSSid));
           vos_mem_copy(pSession->prevApBssid, pSession->connectedProfile.bssid,
                        sizeof(tSirMacAddr));
           pSession->prevOpChannel = pSession->connectedProfile.operationChannel;
           pSession->isPrevApInfoValid = TRUE;
           pSession->roamTS1 = vos_timer_get_system_time();
        }
#endif
    } //                     
   
#ifdef RSSI_HACK
    dumpCmdRSSI = -40;
#endif
    switch (pNeighborRoamInfo->neighborRoamState)
    {
        case eCSR_NEIGHBOR_ROAM_STATE_REASSOCIATING:
            //                                       
            //                                                           
            //       
            vos_timer_stop(&pNeighborRoamInfo->neighborScanTimer);
            vos_timer_stop(&pNeighborRoamInfo->neighborResultsRefreshTimer);
            vos_timer_stop(&pNeighborRoamInfo->emptyScanRefreshTimer);
            if (!CSR_IS_ROAM_SUBSTATE_DISASSOC_HO( pMac, sessionId )) {
                /*
                                                                          
                                                                            
                                                                           
                                                                             
                                                                        
                                                                          
                                                              
                 */
                CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_INIT);
                pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived = eANI_BOOLEAN_FALSE;
            }
            break;

        case eCSR_NEIGHBOR_ROAM_STATE_INIT:
            csrNeighborRoamResetInitStateControlInfo(pMac);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            if (!csrRoamIsRoamOffloadScanEnabled(pMac))
            {
#endif
              csrNeighborRoamDeregAllRssiIndication(pMac);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            }
#endif
            break; 

        case eCSR_NEIGHBOR_ROAM_STATE_CONNECTED:
            CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_INIT)
            pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived = eANI_BOOLEAN_FALSE;
            csrNeighborRoamResetConnectedStateControlInfo(pMac);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            if (!csrRoamIsRoamOffloadScanEnabled(pMac))
            {
#endif
              csrNeighborRoamDeregAllRssiIndication(pMac);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            }
#endif
            break;

        case eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN:
            CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_INIT);
            pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived = eANI_BOOLEAN_FALSE;
            csrNeighborRoamResetCfgListChanScanControlInfo(pMac);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            if (!csrRoamIsRoamOffloadScanEnabled(pMac))
            {
#endif
              csrNeighborRoamDeregAllRssiIndication(pMac);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            }
#endif
            break;

        case eCSR_NEIGHBOR_ROAM_STATE_PREAUTH_DONE:
            /*                                         */
            vos_timer_stop(&pMac->ft.ftSmeContext.preAuthReassocIntvlTimer);
        case eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN:
        case eCSR_NEIGHBOR_ROAM_STATE_PREAUTHENTICATING:
            CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_INIT)
            pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived = eANI_BOOLEAN_FALSE;
            csrNeighborRoamResetPreauthControlInfo(pMac);
            csrNeighborRoamResetReportScanStateControlInfo(pMac);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            if (!csrRoamIsRoamOffloadScanEnabled(pMac))
            {
#endif
              csrNeighborRoamDeregAllRssiIndication(pMac);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
            }
#endif
            break;

        default:
            NEIGHBOR_ROAM_DEBUG(pMac, LOGW, FL("Received disconnect event"
                                "in state %s"),
                                macTraceGetNeighbourRoamState(
                                pNeighborRoamInfo->neighborRoamState));
            NEIGHBOR_ROAM_DEBUG(pMac, LOGW, FL("Transitioning to INIT state"));
            CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_INIT)
            pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived = eANI_BOOLEAN_FALSE;
            break;
    }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
    /*                                                                  */
    if (csrRoamIsStaMode(pMac, sessionId))
    {
       csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_STOP, REASON_DISCONNECTED);
    }
#endif
    return eHAL_STATUS_SUCCESS;
}

/*                                                                            

                                      

                                                                                    
                                                                              
                                                                      

                                                  
                                                         
                                                      

                                                                              

                                                                           */
eHalStatus csrNeighborRoamIndicateConnect(tpAniSirGlobal pMac, tANI_U8 sessionId, VOS_STATUS vosStatus)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus  status = eHAL_STATUS_SUCCESS;
    VOS_STATUS  vstatus;

#if  defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_ESE) || defined(FEATURE_WLAN_LFR)
    int  init_ft_flag = FALSE;
#endif

    //                                                  
    if (NULL == pNeighborRoamInfo || !CSR_IS_SESSION_VALID(pMac, sessionId) ||
        (NULL == pMac->roam.roamSession[sessionId].pCurRoamProfile))
    {
        return eHAL_STATUS_FAILURE;
    }
    smsLog(pMac, LOG2, FL("Connect indication received with session id %d"
           "in state %s"),
           sessionId, macTraceGetNeighbourRoamState(
           pNeighborRoamInfo->neighborRoamState));

    //                                      
    if (pMac->roam.roamSession[sessionId].pCurRoamProfile->csrPersona != VOS_STA_MODE)
    {
        smsLog(pMac, LOGE, FL("Ignoring Connect indication received from a non STA persona."
                              "sessionId: %d, csrPersonna %d"),
               sessionId,
               (int)pMac->roam.roamSession[sessionId].pCurRoamProfile->csrPersona);
        return eHAL_STATUS_SUCCESS;
    }

    //                                   
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
    if (eANI_BOOLEAN_FALSE == CSR_IS_FASTROAM_IN_CONCURRENCY_INI_FEATURE_ENABLED(pMac))
    {
#endif
        if (csrIsConcurrentSessionRunning(pMac))
        {
            smsLog(pMac, LOGE, FL("Ignoring Connect indication received in multisession %d"),
                                  csrIsConcurrentSessionRunning(pMac));
            return eHAL_STATUS_SUCCESS;
        }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
    }
#endif

    switch (pNeighborRoamInfo->neighborRoamState)
    {
        case eCSR_NEIGHBOR_ROAM_STATE_REASSOCIATING:
            if (VOS_STATUS_SUCCESS != vosStatus)
            {
                /*                                                                                                           */
                CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_INIT)
                pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived = eANI_BOOLEAN_FALSE;
                break;
            }
            /*                                       */
        case eCSR_NEIGHBOR_ROAM_STATE_INIT:
            /*                                    */ 
            csrNeighborRoamResetInitStateControlInfo(pMac);

            pNeighborRoamInfo->csrSessionId = sessionId;

#ifdef FEATURE_WLAN_LFR
            /*
                                                          
                                                                
             */
            if (eCSR_NEIGHBOR_ROAM_STATE_INIT == pNeighborRoamInfo->neighborRoamState)
                csrInitOccupiedChannelsList(pMac);
#endif
            CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_CONNECTED);

            vos_mem_copy(pNeighborRoamInfo->currAPbssid, 
                        pMac->roam.roamSession[sessionId].connectedProfile.bssid, sizeof(tCsrBssid));
            pNeighborRoamInfo->currAPoperationChannel = pMac->roam.roamSession[sessionId].connectedProfile.operationChannel;
            pNeighborRoamInfo->neighborScanTimerInfo.pMac = pMac;
            pNeighborRoamInfo->neighborScanTimerInfo.sessionId = sessionId;
            pNeighborRoamInfo->currentNeighborLookupThreshold =
                pNeighborRoamInfo->cfgParams.neighborLookupThreshold;
#ifdef FEATURE_WLAN_LFR
            pNeighborRoamInfo->uEmptyScanCount = 0;
            pNeighborRoamInfo->lookupDOWNRssi = 0;
            pNeighborRoamInfo->uScanMode = DEFAULT_SCAN;
#endif

            
#if  defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_ESE) || defined(FEATURE_WLAN_LFR)
            /*                                                                            */
            csrNeighborRoamFreeRoamableBSSList(pMac, &pMac->roam.neighborRoamInfo.FTRoamInfo.preAuthDoneList);
#endif
            
#ifdef WLAN_FEATURE_VOWIFI_11R
            //                                            
            if ( csrIsAuthType11r( pMac->roam.roamSession[sessionId].connectedProfile.AuthType, 
                                   pMac->roam.roamSession[sessionId].connectedProfile.MDID.mdiePresent))
            {
                if (pMac->roam.configParam.isFastTransitionEnabled)
                    init_ft_flag = TRUE;
                pNeighborRoamInfo->is11rAssoc = eANI_BOOLEAN_TRUE;
            }
            else
                pNeighborRoamInfo->is11rAssoc = eANI_BOOLEAN_FALSE;
            NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("11rAssoc is = %d"), pNeighborRoamInfo->is11rAssoc);
#endif

#ifdef FEATURE_WLAN_ESE
            //                                            
            if (pMac->roam.roamSession[sessionId].connectedProfile.isESEAssoc)
            {
                if (pMac->roam.configParam.isFastTransitionEnabled)
                    init_ft_flag = TRUE;
                pNeighborRoamInfo->isESEAssoc = eANI_BOOLEAN_TRUE;
            }
            else
                pNeighborRoamInfo->isESEAssoc = eANI_BOOLEAN_FALSE;
            NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("isESEAssoc is = %d ft = %d"),
                                pNeighborRoamInfo->isESEAssoc, init_ft_flag);
                            
#endif

#ifdef FEATURE_WLAN_LFR
            //                                     
            if (csrRoamIsFastRoamEnabled(pMac, sessionId))
            {
                init_ft_flag = TRUE;
            }
#endif

#if  defined (WLAN_FEATURE_VOWIFI_11R) || defined (FEATURE_WLAN_ESE) || defined(FEATURE_WLAN_LFR)
            if ( init_ft_flag == TRUE )
            {
                /*                                                                  */
                pNeighborRoamInfo->FTRoamInfo.currentNeighborRptRetryNum = 0;
                csrNeighborRoamPurgePreauthFailedList(pMac);
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
              if (csrRoamIsRoamOffloadScanEnabled(pMac))
              {
                 /*                                                             
                                                                                    
                                */
                 if(csrRoamIsStaMode(pMac, sessionId))
                 {
                     pNeighborRoamInfo->uOsRequestedHandoff = 0;
                     csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_START, REASON_CONNECT);
                 }
              } else {
#endif

                NEIGHBOR_ROAM_DEBUG(pMac, LOG2, FL("Registering neighbor lookup DOWN event with TL, RSSI = %d"), pNeighborRoamInfo->currentNeighborLookupThreshold);
                /*                                                                         */
                vstatus = WLANTL_RegRSSIIndicationCB(pMac->roam.gVosContext, (v_S7_t)pNeighborRoamInfo->currentNeighborLookupThreshold * (-1),
                                            WLANTL_HO_THRESHOLD_DOWN, 
                                            csrNeighborRoamNeighborLookupDOWNCallback, 
                                            VOS_MODULE_ID_SME, pMac);
#ifdef FEATURE_WLAN_LFR
                pNeighborRoamInfo->lookupDOWNRssi = 0;
#endif
                if(!VOS_IS_STATUS_SUCCESS(vstatus))
                {
                   //       
                   smsLog(pMac, LOGW, FL(" Couldn't register csrNeighborRoamNeighborLookupDOWNCallback with TL: Status = %d"), vstatus);
                   status = eHAL_STATUS_FAILURE;
                }
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
              }
#endif /*                                */
            }
#endif
            break;
        default:
            smsLog(pMac, LOGE, FL("Connect event received in invalid state %s"
                   "..Ignoring..."),
                   macTraceGetNeighbourRoamState(
                   pNeighborRoamInfo->neighborRoamState));
            break;
    }
    return status;
}


#ifdef WLAN_FEATURE_VOWIFI_11R
/*                                                                            

                                             

                                                                                

                                                  

                

                                                                           */
void csrNeighborRoamPurgePreauthFailedList(tpAniSirGlobal pMac)
{
    tANI_U8 i;

    for (i = 0; i < pMac->roam.neighborRoamInfo.FTRoamInfo.preAuthFailList.numMACAddress; i++)
    {
        vos_mem_zero(pMac->roam.neighborRoamInfo.FTRoamInfo.preAuthFailList.macAddress[i], sizeof(tSirMacAddr));
    }
    pMac->roam.neighborRoamInfo.FTRoamInfo.preAuthFailList.numMACAddress = 0;

    return;
}

/*                                                                            

                                       

                                                                               

                                                  

                                                                              

                                                                           */
eHalStatus csrNeighborRoamInit11rAssocInfo(tpAniSirGlobal pMac)
{
    eHalStatus  status;
    tpCsr11rAssocNeighborInfo   pFTRoamInfo = &pMac->roam.neighborRoamInfo.FTRoamInfo;

    pMac->roam.neighborRoamInfo.is11rAssoc = eANI_BOOLEAN_FALSE;
    pMac->roam.neighborRoamInfo.cfgParams.maxNeighborRetries = pMac->roam.configParam.neighborRoamConfig.nMaxNeighborRetries;
    pFTRoamInfo->neighborReportTimeout = CSR_NEIGHBOR_ROAM_REPORT_QUERY_TIMEOUT;
    pFTRoamInfo->PEPreauthRespTimeout = CSR_NEIGHBOR_ROAM_PREAUTH_RSP_WAIT_MULTIPLIER * pMac->roam.neighborRoamInfo.cfgParams.neighborScanPeriod;
    pFTRoamInfo->neighborRptPending = eANI_BOOLEAN_FALSE;
    pFTRoamInfo->preauthRspPending = eANI_BOOLEAN_FALSE;
    
    pMac->roam.neighborRoamInfo.FTRoamInfo.currentNeighborRptRetryNum = 0;
    pMac->roam.neighborRoamInfo.FTRoamInfo.numBssFromNeighborReport = 0;
    vos_mem_zero(pMac->roam.neighborRoamInfo.FTRoamInfo.neighboReportBssInfo, 
                            sizeof(tCsrNeighborReportBssInfo) * MAX_BSS_IN_NEIGHBOR_RPT);

    
    status = csrLLOpen(pMac->hHdd, &pFTRoamInfo->preAuthDoneList);
    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("LL Open of preauth done AP List failed"));
        return eHAL_STATUS_RESOURCES;
    }
    return status;
}
#endif /*                         */

/*                                                                            

                           

                                                                   

                                                  

                                                                              

                                                                           */
eHalStatus csrNeighborRoamInit(tpAniSirGlobal pMac)
{
    eHalStatus status;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

    pNeighborRoamInfo->neighborRoamState       =   eCSR_NEIGHBOR_ROAM_STATE_CLOSED;
    pNeighborRoamInfo->prevNeighborRoamState   =   eCSR_NEIGHBOR_ROAM_STATE_CLOSED;
    pNeighborRoamInfo->csrSessionId            =   CSR_SESSION_ID_INVALID;
    pNeighborRoamInfo->cfgParams.maxChannelScanTime = pMac->roam.configParam.neighborRoamConfig.nNeighborScanMaxChanTime;
    pNeighborRoamInfo->cfgParams.minChannelScanTime = pMac->roam.configParam.neighborRoamConfig.nNeighborScanMinChanTime;
    pNeighborRoamInfo->cfgParams.maxNeighborRetries = 0;
    pNeighborRoamInfo->cfgParams.neighborLookupThreshold = pMac->roam.configParam.neighborRoamConfig.nNeighborLookupRssiThreshold;
    pNeighborRoamInfo->cfgParams.neighborReassocThreshold = pMac->roam.configParam.neighborRoamConfig.nNeighborReassocRssiThreshold;
    pNeighborRoamInfo->cfgParams.neighborScanPeriod = pMac->roam.configParam.neighborRoamConfig.nNeighborScanTimerPeriod;
    pNeighborRoamInfo->cfgParams.neighborResultsRefreshPeriod = pMac->roam.configParam.neighborRoamConfig.nNeighborResultsRefreshPeriod;
    pNeighborRoamInfo->cfgParams.emptyScanRefreshPeriod = pMac->roam.configParam.neighborRoamConfig.nEmptyScanRefreshPeriod;
    pNeighborRoamInfo->cfgParams.neighborInitialForcedRoamTo5GhEnable = pMac->roam.configParam.neighborRoamConfig.nNeighborInitialForcedRoamTo5GhEnable;

    pNeighborRoamInfo->cfgParams.channelInfo.numOfChannels   =
                        pMac->roam.configParam.neighborRoamConfig.neighborScanChanList.numChannels;

    pNeighborRoamInfo->cfgParams.channelInfo.ChannelList =
                vos_mem_malloc(pMac->roam.configParam.neighborRoamConfig.neighborScanChanList.numChannels);

    if (NULL == pNeighborRoamInfo->cfgParams.channelInfo.ChannelList)
    {
        smsLog(pMac, LOGE, FL("Memory Allocation for CFG Channel List failed"));
        return eHAL_STATUS_RESOURCES;
    }

    /*                                           */
    vos_mem_copy(pNeighborRoamInfo->cfgParams.channelInfo.ChannelList,
                        pMac->roam.configParam.neighborRoamConfig.neighborScanChanList.channelList,
                        pMac->roam.configParam.neighborRoamConfig.neighborScanChanList.numChannels);

    vos_mem_set(pNeighborRoamInfo->currAPbssid, sizeof(tCsrBssid), 0);
    pNeighborRoamInfo->currentNeighborLookupThreshold = pMac->roam.neighborRoamInfo.cfgParams.neighborLookupThreshold;
#ifdef FEATURE_WLAN_LFR
    pNeighborRoamInfo->lookupDOWNRssi = 0;
    pNeighborRoamInfo->uEmptyScanCount = 0;
    pNeighborRoamInfo->uScanMode = DEFAULT_SCAN;
    vos_mem_set(&pNeighborRoamInfo->prevConnProfile, sizeof(tCsrRoamConnectedProfile), 0);
#endif
    pNeighborRoamInfo->scanRspPending = eANI_BOOLEAN_FALSE;

    pNeighborRoamInfo->neighborScanTimerInfo.pMac = pMac;
    pNeighborRoamInfo->neighborScanTimerInfo.sessionId = CSR_SESSION_ID_INVALID;
    status = vos_timer_init(&pNeighborRoamInfo->neighborScanTimer, VOS_TIMER_TYPE_SW,
                    csrNeighborRoamNeighborScanTimerCallback, (void *)&pNeighborRoamInfo->neighborScanTimerInfo);

    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("Neighbor scan timer allocation failed"));
        vos_mem_free(pNeighborRoamInfo->cfgParams.channelInfo.ChannelList);
        pNeighborRoamInfo->cfgParams.channelInfo.ChannelList = NULL;
        return eHAL_STATUS_RESOURCES;
    }

    status = vos_timer_init(&pNeighborRoamInfo->neighborResultsRefreshTimer, VOS_TIMER_TYPE_SW,
                    csrNeighborRoamResultsRefreshTimerCallback, (void *)&pNeighborRoamInfo->neighborScanTimerInfo);

    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("Neighbor results refresh timer allocation failed"));
        vos_mem_free(pNeighborRoamInfo->cfgParams.channelInfo.ChannelList);
        pNeighborRoamInfo->cfgParams.channelInfo.ChannelList = NULL;
        vos_timer_destroy(&pNeighborRoamInfo->neighborScanTimer);
        return eHAL_STATUS_RESOURCES;
    }

    status = vos_timer_init(&pNeighborRoamInfo->emptyScanRefreshTimer, VOS_TIMER_TYPE_SW,
                csrNeighborRoamEmptyScanRefreshTimerCallback,
                (void *)&pNeighborRoamInfo->neighborScanTimerInfo);

    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("Empty scan refresh timer allocation failed"));
        vos_mem_free(pNeighborRoamInfo->cfgParams.channelInfo.ChannelList);
        pNeighborRoamInfo->cfgParams.channelInfo.ChannelList = NULL;
        vos_timer_destroy(&pNeighborRoamInfo->neighborScanTimer);
        vos_timer_destroy(&pNeighborRoamInfo->neighborResultsRefreshTimer);
        return eHAL_STATUS_RESOURCES;
    }

    status = vos_timer_init(&pNeighborRoamInfo->forcedInitialRoamTo5GHTimer, VOS_TIMER_TYPE_SW,
                csrForcedInitialRoamTo5GHTimerCallback, (void *)&pNeighborRoamInfo->neighborScanTimerInfo);

    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("forcedInitialRoamTo5GHTimer timer allocation failed"));
        vos_mem_free(pNeighborRoamInfo->cfgParams.channelInfo.ChannelList);
        pNeighborRoamInfo->cfgParams.channelInfo.ChannelList = NULL;
        vos_timer_destroy(&pNeighborRoamInfo->neighborScanTimer);
        vos_timer_destroy(&pNeighborRoamInfo->neighborResultsRefreshTimer);
        vos_timer_destroy(&pNeighborRoamInfo->emptyScanRefreshTimer);
        return eHAL_STATUS_RESOURCES;
    }

    status = csrLLOpen(pMac->hHdd, &pNeighborRoamInfo->roamableAPList);
    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("LL Open of roamable AP List failed"));
        vos_mem_free(pNeighborRoamInfo->cfgParams.channelInfo.ChannelList);
        pNeighborRoamInfo->cfgParams.channelInfo.ChannelList = NULL;
        vos_timer_destroy(&pNeighborRoamInfo->neighborScanTimer);
        vos_timer_destroy(&pNeighborRoamInfo->neighborResultsRefreshTimer);
        vos_timer_destroy(&pNeighborRoamInfo->emptyScanRefreshTimer);
        vos_timer_destroy(&pNeighborRoamInfo->forcedInitialRoamTo5GHTimer);
        return eHAL_STATUS_RESOURCES;
    }

    pNeighborRoamInfo->roamChannelInfo.currentChanIndex = CSR_NEIGHBOR_ROAM_INVALID_CHANNEL_INDEX;
    pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels = 0;
    pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = NULL;
    pNeighborRoamInfo->roamChannelInfo.chanListScanInProgress = eANI_BOOLEAN_FALSE;
    pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived = eANI_BOOLEAN_FALSE;

#ifdef WLAN_FEATURE_VOWIFI_11R
    status = csrNeighborRoamInit11rAssocInfo(pMac);
    if (eHAL_STATUS_SUCCESS != status)
    {
        smsLog(pMac, LOGE, FL("LL Open of roamable AP List failed"));
        vos_mem_free(pNeighborRoamInfo->cfgParams.channelInfo.ChannelList);
        pNeighborRoamInfo->cfgParams.channelInfo.ChannelList = NULL;
        vos_timer_destroy(&pNeighborRoamInfo->neighborScanTimer);
        vos_timer_destroy(&pNeighborRoamInfo->neighborResultsRefreshTimer);
        vos_timer_destroy(&pNeighborRoamInfo->emptyScanRefreshTimer);
        vos_timer_destroy(&pNeighborRoamInfo->forcedInitialRoamTo5GHTimer);
        csrLLClose(&pNeighborRoamInfo->roamableAPList);
        return eHAL_STATUS_RESOURCES;
    }
#endif
    /*                                             */
    pNeighborRoamInfo->scanRequestTimeStamp = (tANI_TIMESTAMP)palGetTickCount(pMac->hHdd);

    CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_INIT)
    pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived = eANI_BOOLEAN_FALSE;
    return eHAL_STATUS_SUCCESS;
}

/*                                                                            

                            

                                                                            

                                                  

                

                                                                           */
void csrNeighborRoamClose(tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

    if (eCSR_NEIGHBOR_ROAM_STATE_CLOSED == pNeighborRoamInfo->neighborRoamState)
    {
        smsLog(pMac, LOGW, FL("Neighbor Roam Algorithm Already Closed"));
        return;
    }

    if (pNeighborRoamInfo->cfgParams.channelInfo.ChannelList)
        vos_mem_free(pNeighborRoamInfo->cfgParams.channelInfo.ChannelList);
   
    pNeighborRoamInfo->cfgParams.channelInfo.ChannelList = NULL;
    
    pNeighborRoamInfo->neighborScanTimerInfo.pMac = NULL;
    pNeighborRoamInfo->neighborScanTimerInfo.sessionId = CSR_SESSION_ID_INVALID;
    vos_timer_destroy(&pNeighborRoamInfo->neighborScanTimer);
    vos_timer_destroy(&pNeighborRoamInfo->neighborResultsRefreshTimer);
    vos_timer_destroy(&pNeighborRoamInfo->emptyScanRefreshTimer);
    vos_timer_destroy(&pNeighborRoamInfo->forcedInitialRoamTo5GHTimer);

    /*                                                                            */
    csrNeighborRoamFreeRoamableBSSList(pMac, &pNeighborRoamInfo->roamableAPList);
    csrLLClose(&pNeighborRoamInfo->roamableAPList);
    
    if (pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList)
    {
        vos_mem_free(pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList);
    }

    pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = NULL;
    pNeighborRoamInfo->roamChannelInfo.currentChanIndex = CSR_NEIGHBOR_ROAM_INVALID_CHANNEL_INDEX;
    pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.numOfChannels = 0;
    pNeighborRoamInfo->roamChannelInfo.currentChannelListInfo.ChannelList = NULL;
    pNeighborRoamInfo->roamChannelInfo.chanListScanInProgress = eANI_BOOLEAN_FALSE;    
    pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived = eANI_BOOLEAN_FALSE;

    /*                    */ 
    csrReleaseProfile(pMac, &pNeighborRoamInfo->csrNeighborRoamProfile);
#ifdef FEATURE_WLAN_LFR    
    csrRoamFreeConnectProfile(pMac, &pNeighborRoamInfo->prevConnProfile);
#endif
#ifdef WLAN_FEATURE_VOWIFI_11R
    pMac->roam.neighborRoamInfo.FTRoamInfo.currentNeighborRptRetryNum = 0;
    pMac->roam.neighborRoamInfo.FTRoamInfo.numBssFromNeighborReport = 0;
    vos_mem_zero(pMac->roam.neighborRoamInfo.FTRoamInfo.neighboReportBssInfo, 
                            sizeof(tCsrNeighborReportBssInfo) * MAX_BSS_IN_NEIGHBOR_RPT);
    csrNeighborRoamFreeRoamableBSSList(pMac, &pMac->roam.neighborRoamInfo.FTRoamInfo.preAuthDoneList);
    csrLLClose(&pMac->roam.neighborRoamInfo.FTRoamInfo.preAuthDoneList);
#endif /*                         */

    CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_CLOSED)
    
    return;
}

/*                                                                            

                                     

                                                                              
                                                                                    
                                                                   

                                                  

                

                                                                           */
void csrNeighborRoamRequestHandoff(tpAniSirGlobal pMac)
{

    tCsrRoamInfo roamInfo;
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tANI_U32 sessionId = pNeighborRoamInfo->csrSessionId;
    tCsrNeighborRoamBSSInfo     handoffNode;
    extern void csrRoamRoamingStateDisassocRspProcessor( tpAniSirGlobal pMac, tSirSmeDisassocRsp *pSmeDisassocRsp );
    tANI_U32 roamId = 0;
    eHalStatus status;

#ifdef FEATURE_WLAN_LFR_METRICS
    tCsrRoamInfo *roamInfoMetrics;
#endif

    if (pMac->roam.neighborRoamInfo.neighborRoamState != eCSR_NEIGHBOR_ROAM_STATE_PREAUTH_DONE) 
    {
        smsLog(pMac, LOGE, FL("Roam requested when Neighbor roam is in %s state"),
               macTraceGetNeighbourRoamState(
               pMac->roam.neighborRoamInfo.neighborRoamState));
        return;
    }

    if (eANI_BOOLEAN_FALSE ==
         csrNeighborRoamGetHandoffAPInfo(pMac, &handoffNode))
    {
        VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_ERROR,
                   FL("failed to obtain handoff AP"));
        return;
    }

    VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_DEBUG,
               FL("HANDOFF CANDIDATE BSSID "MAC_ADDRESS_STR),
                   MAC_ADDR_ARRAY(handoffNode.pBssDescription->bssId));

    vos_mem_zero(&roamInfo, sizeof(tCsrRoamInfo));
    csrRoamCallCallback(pMac, pNeighborRoamInfo->csrSessionId, &roamInfo, roamId, eCSR_ROAM_FT_START, 
                eSIR_SME_SUCCESS);

    vos_mem_zero(&roamInfo, sizeof(tCsrRoamInfo));
    CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_REASSOCIATING)
    
#ifdef FEATURE_WLAN_LFR_METRICS
    /*                                          
                                                                         */
    roamInfoMetrics = vos_mem_malloc(sizeof(tCsrRoamInfo));
    if (NULL == roamInfoMetrics)
    {
        smsLog(pMac, LOG1, FL("Memory allocation failed!"));
    }
    else
    {
        vos_mem_copy((void *)roamInfoMetrics->bssid,
            (void *)&handoffNode.pBssDescription->bssId, sizeof(tCsrBssid));
        csrRoamCallCallback(pMac, pNeighborRoamInfo->csrSessionId,
            roamInfoMetrics, 0, eCSR_ROAM_HANDOVER_SUCCESS, 0);
        vos_mem_free(roamInfoMetrics);
    }
#endif

    /*                                                               */ 
    csrReleaseProfile(pMac, &pNeighborRoamInfo->csrNeighborRoamProfile);
    /*                                                                                                                 
                                                     */
    status = csrRoamCopyConnectedProfile(pMac,
                                  pNeighborRoamInfo->csrSessionId,
                                 &pNeighborRoamInfo->csrNeighborRoamProfile);
    if(eHAL_STATUS_SUCCESS != status)
    {
        VOS_TRACE (VOS_MODULE_ID_SME, VOS_TRACE_LEVEL_ERROR,
                          FL("csrRoamCopyConnectedProfile returned failed %d"), status);
        return;
    }

    vos_mem_copy(pNeighborRoamInfo->csrNeighborRoamProfile.BSSIDs.bssid, handoffNode.pBssDescription->bssId, sizeof(tSirMacAddr));
    pNeighborRoamInfo->csrNeighborRoamProfile.ChannelInfo.ChannelList[0] = handoffNode.pBssDescription->channelId;
    
    NEIGHBOR_ROAM_DEBUG(pMac, LOGW, " csrRoamHandoffRequested: disassociating with current AP");

    if(!HAL_STATUS_SUCCESS(csrRoamIssueDisassociateCmd(pMac, sessionId, eCSR_DISCONNECT_REASON_HANDOFF)))
    {
        smsLog(pMac, LOGW, "csrRoamHandoffRequested:  fail to issue disassociate");
        return;
    }                       

    //                                               
    roamInfo.reasonCode = eCsrRoamReasonBetterAP;

    vos_mem_copy(roamInfo.bssid, 
                 handoffNode.pBssDescription->bssId, 
                 sizeof( tCsrBssid ));

    csrRoamCallCallback(pMac, sessionId, &roamInfo, 0, eCSR_ROAM_ROAMING_START, eCSR_ROAM_RESULT_NONE);


    return;
}

/*                                                                            

                                          

                                                                                 
                                           

                                                  
                                                                            

                                                                                  

                                                                           */
tANI_BOOLEAN csrNeighborRoamIsHandoffInProgress(tpAniSirGlobal pMac)
{
    if (eCSR_NEIGHBOR_ROAM_STATE_REASSOCIATING == pMac->roam.neighborRoamInfo.neighborRoamState)
        return eANI_BOOLEAN_TRUE;

    return eANI_BOOLEAN_FALSE;
}

#if defined(WLAN_FEATURE_VOWIFI_11R) || defined(WLAN_FEATURE_NEIGHBOR_ROAMING)
/*                                                                            

                                 

                                                                                       

                                                  

                                                                                   

                                                                           */
tANI_BOOLEAN csrNeighborRoamIs11rAssoc(tpAniSirGlobal pMac)
{
    return pMac->roam.neighborRoamInfo.is11rAssoc;
}
#endif /*                         */


/*                                                                            

                                       

                                                                                     
                                                                                        
                                               

                                                  
                                                                         

                                                                                   

                                                                           */
tANI_BOOLEAN csrNeighborRoamGetHandoffAPInfo(tpAniSirGlobal pMac, tpCsrNeighborRoamBSSInfo pHandoffNode)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tpCsrNeighborRoamBSSInfo        pBssNode = NULL;
    
    VOS_ASSERT(NULL != pHandoffNode); 
        
#ifdef WLAN_FEATURE_VOWIFI_11R
    if (pNeighborRoamInfo->is11rAssoc)
    {
        /*                                                          */
        pBssNode = csrNeighborRoamGetRoamableAPListNextEntry(pMac, &pNeighborRoamInfo->FTRoamInfo.preAuthDoneList, NULL);
        NEIGHBOR_ROAM_DEBUG(pMac, LOG1, FL("Number of Handoff candidates = %d"), csrLLCount(&pNeighborRoamInfo->FTRoamInfo.preAuthDoneList));
    }
    else
#endif
#ifdef FEATURE_WLAN_ESE
    if (pNeighborRoamInfo->isESEAssoc)
    {
        /*                                                          */
        pBssNode = csrNeighborRoamGetRoamableAPListNextEntry(pMac, &pNeighborRoamInfo->FTRoamInfo.preAuthDoneList, NULL);
        NEIGHBOR_ROAM_DEBUG(pMac, LOG1, FL("Number of Handoff candidates = %d"), csrLLCount(&pNeighborRoamInfo->FTRoamInfo.preAuthDoneList));
    }
    else
#endif
#ifdef FEATURE_WLAN_LFR
    if (csrRoamIsFastRoamEnabled(pMac, CSR_SESSION_ID_INVALID))
    {
        /*                                                          */
        pBssNode = csrNeighborRoamGetRoamableAPListNextEntry(pMac, &pNeighborRoamInfo->FTRoamInfo.preAuthDoneList, NULL);
        NEIGHBOR_ROAM_DEBUG(pMac, LOG1, FL("Number of Handoff candidates = %d"), csrLLCount(&pNeighborRoamInfo->FTRoamInfo.preAuthDoneList));
    }
    else
#endif
    {
        pBssNode = csrNeighborRoamGetRoamableAPListNextEntry(pMac, &pNeighborRoamInfo->roamableAPList, NULL);
        NEIGHBOR_ROAM_DEBUG(pMac, LOG1, FL("Number of Handoff candidates = %d"), csrLLCount(&pNeighborRoamInfo->roamableAPList));
    }

    if (NULL == pBssNode)
    {
        return eANI_BOOLEAN_FALSE;
    }

    vos_mem_copy(pHandoffNode, pBssNode, sizeof(tCsrNeighborRoamBSSInfo));

    return eANI_BOOLEAN_TRUE;
}

/*                                                                            
                                                               

                                                  

                   

                                                                           */
tANI_BOOLEAN csrNeighborRoamStatePreauthDone(tpAniSirGlobal pMac)
{
    return (pMac->roam.neighborRoamInfo.neighborRoamState == 
               eCSR_NEIGHBOR_ROAM_STATE_PREAUTH_DONE);
}

/*                                                                            
                                                                    
                                                                       
         
                                                                         
                                                                      
                                                                         
           

                                                  

                   
                                                                           */
void csrNeighborRoamTranistionPreauthDoneToDisconnected(tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    if (pMac->roam.neighborRoamInfo.neighborRoamState != 
               eCSR_NEIGHBOR_ROAM_STATE_PREAUTH_DONE) return;

    //           
    vos_timer_stop(&pMac->ft.ftSmeContext.preAuthReassocIntvlTimer);

    //                         
    CSR_NEIGHBOR_ROAM_STATE_TRANSITION(eCSR_NEIGHBOR_ROAM_STATE_INIT)
    pNeighborRoamInfo->roamChannelInfo.IAPPNeighborListReceived = eANI_BOOLEAN_FALSE;
}

/*                                                                            
                                                                      
                               

                                                    

                   

                                                                           */
tANI_BOOLEAN csrNeighborRoamScanRspPending (tHalHandle hHal)
{
    tpAniSirGlobal pMac = PMAC_STRUCT(hHal);
    return (pMac->roam.neighborRoamInfo.scanRspPending);
}

/*                                                                            
                                                                                

                                                    

                   

                                                                           */
tANI_BOOLEAN csrNeighborMiddleOfRoaming (tHalHandle hHal)
{
    tpAniSirGlobal pMac = PMAC_STRUCT(hHal);
    tANI_BOOLEAN val = (eCSR_NEIGHBOR_ROAM_STATE_REASSOCIATING == pMac->roam.neighborRoamInfo.neighborRoamState) ||
                       (eCSR_NEIGHBOR_ROAM_STATE_PREAUTHENTICATING == pMac->roam.neighborRoamInfo.neighborRoamState) ||
                       (eCSR_NEIGHBOR_ROAM_STATE_PREAUTH_DONE == pMac->roam.neighborRoamInfo.neighborRoamState) ||
                       (eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN == pMac->roam.neighborRoamInfo.neighborRoamState) ||
                       (eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN == pMac->roam.neighborRoamInfo.neighborRoamState);
    return (val);
}
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
/*                                                                            

                                            

                                                                            
                                                 

                                                  
                                 

                                                                              

                                                                           */
eHalStatus csrNeighborRoamCandidateFoundIndHdlr(tpAniSirGlobal pMac, void* pMsg)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus status = eHAL_STATUS_SUCCESS;
    /*                                                 */
    if ((eCSR_NEIGHBOR_ROAM_STATE_CONNECTED != pNeighborRoamInfo->neighborRoamState)
        || (pNeighborRoamInfo->uOsRequestedHandoff))
    {
        smsLog(pMac, LOGE, FL("Received in not CONNECTED state OR uOsRequestedHandoff is set. Ignore it"));
        status = eHAL_STATUS_FAILURE;
    }
    else
    {
        /*                                          
                                               */
        csrScanFlushSelectiveResult(pMac, VOS_FALSE);
        /*                                                                        
                                                                          
                                               
        */
        status = csrScanRequestLfrResult(pMac, pNeighborRoamInfo->csrSessionId,
                                         csrNeighborRoamScanResultRequestCallback, pMac);
    }

    return status;
}

/*                                                                            

                                        

                                                                              
                                    

                                                  

                                                                              

                                                                           */
eHalStatus csrNeighborRoamProcessHandoffReq(tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus status = eHAL_STATUS_SUCCESS;
    tANI_U32 roamId;
    tCsrRoamProfile *pProfile = NULL;
    tCsrRoamSession *pSession = CSR_GET_SESSION( pMac, pNeighborRoamInfo->csrSessionId );
    tANI_U8 i = 0;

    if (NULL == pSession)
    {
        smsLog(pMac, LOGE, FL("pSession is NULL "));
        return eHAL_STATUS_FAILURE;
    }

    do
    {
        roamId = GET_NEXT_ROAM_ID(&pMac->roam);
        pProfile = vos_mem_malloc(sizeof(tCsrRoamProfile));
        if ( NULL == pProfile )
        {
            smsLog(pMac, LOGE, FL("Memory alloc failed"));
            return eHAL_STATUS_FAILURE;
        }
        vos_mem_set(pProfile, sizeof(tCsrRoamProfile), 0);
        status = csrRoamCopyProfile(pMac, pProfile, pSession->pCurRoamProfile);
        if(!HAL_STATUS_SUCCESS(status))
        {
            smsLog(pMac, LOGE, FL("Profile copy failed"));
            break;
        }

        //                       
        pProfile->BSSIDs.numOfBSSIDs = 1;
        pProfile->BSSIDs.bssid = vos_mem_malloc(sizeof(tSirMacAddr) * pProfile->BSSIDs.numOfBSSIDs);
        if (NULL == pProfile->BSSIDs.bssid)
        {
            smsLog(pMac, LOGE, FL("mem alloc failed for BSSID"));
            status = eHAL_STATUS_FAILURE;
            break;
        }

        vos_mem_zero(pProfile->BSSIDs.bssid, sizeof(tSirMacAddr) * pProfile->BSSIDs.numOfBSSIDs);

        /*                                                        */
        for (i = 0; i < pProfile->BSSIDs.numOfBSSIDs; i++)
        {
            vos_mem_copy(&pProfile->BSSIDs.bssid[i],
                         pNeighborRoamInfo->handoffReqInfo.bssid, sizeof(tSirMacAddr));
        }

        pProfile->ChannelInfo.numOfChannels = 1;
        pProfile->ChannelInfo.ChannelList =
        vos_mem_malloc(sizeof(*pProfile->ChannelInfo.ChannelList) *
                           pProfile->ChannelInfo.numOfChannels);
        if (NULL == pProfile->ChannelInfo.ChannelList)
        {
            smsLog(pMac, LOGE, FL("mem alloc failed for ChannelList"));
            status = eHAL_STATUS_FAILURE;
            break;
        }
        pProfile->ChannelInfo.ChannelList[0] = pNeighborRoamInfo->handoffReqInfo.channel;

        //                        
        //                                             
        //              
        status = csrScanForSSID(pMac, pNeighborRoamInfo->csrSessionId, pProfile, roamId, FALSE);
        if(!HAL_STATUS_SUCCESS(status))
        {
            smsLog(pMac, LOGE, FL("SSID scan failed"));
        }
    }while(0);

    if(NULL != pProfile)
    {
        csrReleaseProfile(pMac, pProfile);
        vos_mem_free(pProfile);
    }

    return status;
}

/*                                                                            

                                    

                                                                               
                                                                                
                       

                                                  

                                                                              

                                                                           */
eHalStatus csrNeighborRoamSssidScanDone(tpAniSirGlobal pMac, eHalStatus status)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus                      hstatus;

    smsLog(pMac, LOGE, FL("called "));

    /*                                                 */
    if (eCSR_NEIGHBOR_ROAM_STATE_CONNECTED != pNeighborRoamInfo->neighborRoamState)
    {
        smsLog(pMac, LOGE, FL("Received in not CONNECTED state. Ignore it"));
        return eHAL_STATUS_FAILURE;
    }

    //                                                                                
    if(!HAL_STATUS_SUCCESS(status))
    {
        smsLog(pMac, LOGE, FL("Add an entry to csr scan cache"));
        hstatus = csrScanCreateEntryInScanCache(pMac, pNeighborRoamInfo->csrSessionId,
                                                pNeighborRoamInfo->handoffReqInfo.bssid,
                                                pNeighborRoamInfo->handoffReqInfo.channel);
        if (eHAL_STATUS_SUCCESS != hstatus)
        {
            smsLog(pMac, LOGE, FL("csrScanCreateEntryInScanCache failed with status %d"), hstatus);
            return eHAL_STATUS_FAILURE;
        }
    }

    /*                                                                                    */
    hstatus = csrNeighborRoamProcessScanComplete(pMac);

    if (eHAL_STATUS_SUCCESS != hstatus)
    {
        smsLog(pMac, LOGE, FL("Neighbor scan process complete failed with status %d"), hstatus);
        return eHAL_STATUS_FAILURE;
    }
    return eHAL_STATUS_SUCCESS;
}

/*                                                                            

                                     

                                                                               
                                

                                                  
                                  

                                                                              

                                                                           */
eHalStatus csrNeighborRoamHandoffReqHdlr(tpAniSirGlobal pMac, void* pMsg)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    tAniHandoffReq                 *pHandoffReqInfo;
    eHalStatus status = eHAL_STATUS_SUCCESS;
    /*                                                 */
    if (eCSR_NEIGHBOR_ROAM_STATE_CONNECTED != pNeighborRoamInfo->neighborRoamState)
    {
        smsLog(pMac, LOGE, FL("Received in not CONNECTED state. Ignore it"));
        status = eHAL_STATUS_FAILURE;
    }
    else
    {
        //                                                              
        pHandoffReqInfo = (tAniHandoffReq *)pMsg;
        if (NULL != pHandoffReqInfo)
        {
            //            
            if (VOS_FALSE == vos_mem_compare(pHandoffReqInfo->bssid,
                                             pNeighborRoamInfo->currAPbssid,
                                             sizeof(tSirMacAddr)))
            {

                pNeighborRoamInfo->handoffReqInfo.channel = pHandoffReqInfo->channel;
                vos_mem_copy(pNeighborRoamInfo->handoffReqInfo.bssid,
                             pHandoffReqInfo->bssid,
                             6);
                pNeighborRoamInfo->uOsRequestedHandoff = 1;
                status = csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_STOP,
                                            REASON_OS_REQUESTED_ROAMING_NOW);
                if (eHAL_STATUS_SUCCESS != status)
                {
                    smsLog(pMac, LOGE, FL("csrRoamOffloadScan failed"));
                    pNeighborRoamInfo->uOsRequestedHandoff = 0;
                }
            }
            else
            {
                smsLog(pMac, LOGE, FL("Received req has same BSSID as current AP!!"));
                status = eHAL_STATUS_FAILURE;
            }
        }
        else
        {
            smsLog(pMac, LOGE, FL("Received msg is NULL"));
            status = eHAL_STATUS_FAILURE;
        }
    }

    return status;
}

/*                                                                            

                                            

                                                                          
                                                                              

                                                  

                                                                              

                                                                           */
eHalStatus csrNeighborRoamProceedWithHandoffReq(tpAniSirGlobal pMac)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;
    eHalStatus status = eHAL_STATUS_SUCCESS;
    /*                                                 */
    if ((eCSR_NEIGHBOR_ROAM_STATE_CONNECTED != pNeighborRoamInfo->neighborRoamState)
        || (!pNeighborRoamInfo->uOsRequestedHandoff))
    {
        smsLog(pMac, LOGE, FL("Received in not CONNECTED state or uOsRequestedHandoff is not set. Ignore it"));
        status = eHAL_STATUS_FAILURE;
    }
    else
    {
        //                           
        status = csrNeighborRoamProcessHandoffReq(pMac);
    }
    if(!HAL_STATUS_SUCCESS(status))
    {
        pNeighborRoamInfo->uOsRequestedHandoff = 0;
    }
    return status;
}

/*                                                                            

                                   

                                                                            
                                                                           
                                                   

                                                  

                                                                              

                                                                           */
eHalStatus csrNeighborRoamStartLfrScan(tpAniSirGlobal pMac, tANI_U8 OffloadCmdStopReason)
{
    tpCsrNeighborRoamControlInfo    pNeighborRoamInfo = &pMac->roam.neighborRoamInfo;

    smsLog(pMac, LOGE,
           FL(" uOsRequestedHandoff=%d isForcedInitialRoamTo5GH=%d OffloadCmdStopReason = %d"),
           pNeighborRoamInfo->uOsRequestedHandoff,
           pNeighborRoamInfo->isForcedInitialRoamTo5GH,
           OffloadCmdStopReason);

    if(OffloadCmdStopReason == REASON_OS_REQUESTED_ROAMING_NOW)
    pNeighborRoamInfo->uOsRequestedHandoff = 0;
    if(OffloadCmdStopReason == REASON_INITIAL_FORCED_ROAM_TO_5G)
        pNeighborRoamInfo->isForcedInitialRoamTo5GH = 0;
    /*                                                 
                                                   */
    csrRoamOffloadScan(pMac, ROAM_SCAN_OFFLOAD_START, REASON_NO_CAND_FOUND_OR_NOT_ROAMING_NOW);

    return eHAL_STATUS_SUCCESS;
}
#endif //                              
#endif /*                               */
