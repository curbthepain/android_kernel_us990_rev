/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *
 * File: wpa.c
 *
 * Purpose: Handles the Basic Service Set & Node Database functions
 *
 * Functions:
 *      WPA_ParseRSN - Parse RSN IE.
 *
 * Revision History:
 *
 * Author: Kyle Hsu
 *
 * Date: July 14, 2003
 *
 */

#include "ttype.h"
#include "tmacro.h"
#include "tether.h"
#include "device.h"
#include "80211hdr.h"
#include "bssdb.h"
#include "wmgr.h"
#include "wpa.h"
#include "80211mgr.h"

/*                                                                   */
static int          msglevel                =MSG_LEVEL_INFO;

const unsigned char abyOUI00[4] = { 0x00, 0x50, 0xf2, 0x00 };
const unsigned char abyOUI01[4] = { 0x00, 0x50, 0xf2, 0x01 };
const unsigned char abyOUI02[4] = { 0x00, 0x50, 0xf2, 0x02 };
const unsigned char abyOUI03[4] = { 0x00, 0x50, 0xf2, 0x03 };
const unsigned char abyOUI04[4] = { 0x00, 0x50, 0xf2, 0x04 };
const unsigned char abyOUI05[4] = { 0x00, 0x50, 0xf2, 0x05 };


/* 
  
               
                                       
  
              
       
                            
        
            
  
                      
  
 */

void
WPA_ClearRSN (
    PKnownBSS        pBSSList
    )
{
    int ii;
    pBSSList->byGKType = WPA_TKIP;
    for (ii=0; ii < 4; ii ++)
        pBSSList->abyPKType[ii] = WPA_TKIP;
    pBSSList->wPKCount = 0;
    for (ii=0; ii < 4; ii ++)
        pBSSList->abyAuthType[ii] = WPA_AUTH_IEEE802_1X;
    pBSSList->wAuthCount = 0;
    pBSSList->byDefaultK_as_PK = 0;
    pBSSList->byReplayIdx = 0;
    pBSSList->sRSNCapObj.bRSNCapExist = false;
    pBSSList->sRSNCapObj.wRSNCap = 0;
    pBSSList->bWPAValid = false;
}


/* 
  
               
                   
  
              
       
                            
                                     
        
            
  
                      
  
 */
void
WPA_ParseRSN (
    PKnownBSS        pBSSList,
    PWLAN_IE_RSN_EXT pRSN
    )
{
    PWLAN_IE_RSN_AUTH  pIE_RSN_Auth = NULL;
    int                i, j, m, n = 0;
    unsigned char *pbyCaps;

    WPA_ClearRSN(pBSSList);

    DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"WPA_ParseRSN: [%d]\n", pRSN->len);

    //                                       
    if ((pRSN->len >= 6) //               
         && (pRSN->byElementID == WLAN_EID_RSN_WPA) &&  !memcmp(pRSN->abyOUI, abyOUI01, 4)
         && (pRSN->wVersion == 1)) {

        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"Legal RSN\n");
        //                                                                    
        if (pRSN->len >= 10) //                         
        {
            if ( !memcmp(pRSN->abyMulticast, abyOUI01, 4))
                pBSSList->byGKType = WPA_WEP40;
            else if ( !memcmp(pRSN->abyMulticast, abyOUI02, 4))
                pBSSList->byGKType = WPA_TKIP;
            else if ( !memcmp(pRSN->abyMulticast, abyOUI03, 4))
                pBSSList->byGKType = WPA_AESWRAP;
            else if ( !memcmp(pRSN->abyMulticast, abyOUI04, 4))
                pBSSList->byGKType = WPA_AESCCMP;
            else if ( !memcmp(pRSN->abyMulticast, abyOUI05, 4))
                pBSSList->byGKType = WPA_WEP104;
            else
                //                       
                pBSSList->byGKType = WPA_NONE;

            DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"byGKType: %x\n", pBSSList->byGKType);
        }

        if (pRSN->len >= 12) //                               
        {
            j = 0;
            DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"wPKCount: %d, sizeof(pBSSList->abyPKType): %zu\n", pRSN->wPKCount, sizeof(pBSSList->abyPKType));
            for(i = 0; (i < pRSN->wPKCount) && (j < sizeof(pBSSList->abyPKType)/sizeof(unsigned char)); i++) {
                if(pRSN->len >= 12+i*4+4) { //                                        
                    if ( !memcmp(pRSN->PKSList[i].abyOUI, abyOUI00, 4))
                        pBSSList->abyPKType[j++] = WPA_NONE;
                    else if ( !memcmp(pRSN->PKSList[i].abyOUI, abyOUI02, 4))
                        pBSSList->abyPKType[j++] = WPA_TKIP;
                    else if ( !memcmp(pRSN->PKSList[i].abyOUI, abyOUI03, 4))
                        pBSSList->abyPKType[j++] = WPA_AESWRAP;
                    else if ( !memcmp(pRSN->PKSList[i].abyOUI, abyOUI04, 4))
                        pBSSList->abyPKType[j++] = WPA_AESCCMP;
                    else
                        //                       
                        ;
                }
                else
                    break;
                //                                                                      
            } //   
            pBSSList->wPKCount = (unsigned short)j;
            DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"wPKCount: %d\n", pBSSList->wPKCount);
        }

        m = pRSN->wPKCount;
        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"m: %d\n", m);
        DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"14+m*4: %d\n", 14+m*4);

        if (pRSN->len >= 14+m*4) { //                                               
            //                                                 
            pIE_RSN_Auth = (PWLAN_IE_RSN_AUTH) pRSN->PKSList[m].abyOUI;
            j = 0;
            DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"wAuthCount: %d, sizeof(pBSSList->abyAuthType): %zu\n",
                          pIE_RSN_Auth->wAuthCount, sizeof(pBSSList->abyAuthType));
            for(i = 0; (i < pIE_RSN_Auth->wAuthCount) && (j < sizeof(pBSSList->abyAuthType)/sizeof(unsigned char)); i++) {
                if(pRSN->len >= 14+4+(m+i)*4) { //                                                        
                    if ( !memcmp(pIE_RSN_Auth->AuthKSList[i].abyOUI, abyOUI01, 4))
                        pBSSList->abyAuthType[j++] = WPA_AUTH_IEEE802_1X;
                    else if ( !memcmp(pIE_RSN_Auth->AuthKSList[i].abyOUI, abyOUI02, 4))
                        pBSSList->abyAuthType[j++] = WPA_AUTH_PSK;
                    else
                    //                       
                    ;
                }
                else
                    break;
                //                                                                          
            }
            if(j > 0)
                pBSSList->wAuthCount = (unsigned short)j;
            DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"wAuthCount: %d\n", pBSSList->wAuthCount);
        }

        if (pIE_RSN_Auth != NULL) {

            n = pIE_RSN_Auth->wAuthCount;

            DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"n: %d\n", n);
            DBG_PRT(MSG_LEVEL_DEBUG, KERN_INFO"14+4+(m+n)*4: %d\n", 14+4+(m+n)*4);

            if(pRSN->len+2 >= 14+4+(m+n)*4) { //                                                               
                pbyCaps = (unsigned char *)pIE_RSN_Auth->AuthKSList[n].abyOUI;
                pBSSList->byDefaultK_as_PK = (*pbyCaps) & WPA_GROUPFLAG;
                pBSSList->byReplayIdx = 2 << ((*pbyCaps >> WPA_REPLAYBITSSHIFT) & WPA_REPLAYBITS);
                pBSSList->sRSNCapObj.bRSNCapExist = true;
                pBSSList->sRSNCapObj.wRSNCap = *(unsigned short *)pbyCaps;
                //                                           
                //                                                                      
                //                                                            
            }
        }
        pBSSList->bWPAValid = true;
    }
}

/* 
  
               
                                        
  
              
       
                              
                                
                           
        
            
  
                      
  
 */
bool
WPA_SearchRSN (
    unsigned char byCmd,
    unsigned char byEncrypt,
    PKnownBSS        pBSSList
    )
{
    int ii;
    unsigned char byPKType = WPA_NONE;

    if (pBSSList->bWPAValid == false)
        return false;

    switch(byCmd) {
    case 0:

        if (byEncrypt != pBSSList->byGKType)
            return false;

        if (pBSSList->wPKCount > 0) {
            for (ii = 0; ii < pBSSList->wPKCount; ii ++) {
                if (pBSSList->abyPKType[ii] == WPA_AESCCMP)
                    byPKType = WPA_AESCCMP;
                else if ((pBSSList->abyPKType[ii] == WPA_TKIP) && (byPKType != WPA_AESCCMP))
                     byPKType = WPA_TKIP;
                else if ((pBSSList->abyPKType[ii] == WPA_WEP40) && (byPKType != WPA_AESCCMP) && (byPKType != WPA_TKIP))
                     byPKType = WPA_WEP40;
                else if ((pBSSList->abyPKType[ii] == WPA_WEP104) && (byPKType != WPA_AESCCMP) && (byPKType != WPA_TKIP))
                     byPKType = WPA_WEP104;
            }
            if (byEncrypt != byPKType)
                return false;
        }
        return true;
//                                     
//                                                        
//                                                        
//                          
        break;

    default:
        break;
    }
    return false;
}

/* 
  
               
                                  
  
              
       
                                     
        
            
  
                      
  
 */
bool
WPAb_Is_RSN (
    PWLAN_IE_RSN_EXT pRSN
    )
{
    if (pRSN == NULL)
        return false;

    if ((pRSN->len >= 6) && //               
        (pRSN->byElementID == WLAN_EID_RSN_WPA) &&  !memcmp(pRSN->abyOUI, abyOUI01, 4) &&
        (pRSN->wVersion == 1)) {
        return true;
    }
    else
        return false;
}

