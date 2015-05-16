/*
 * Custom OID/ioctl definitions for
 * Broadcom 802.11abg Networking Device Driver
 *
 * Definitions subject to change without notice.
 *
 * Copyright (C) 1999-2014, Broadcom Corporation
 * 
 *      Unless you and Broadcom execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2 (the "GPL"),
 * available at http://www.broadcom.com/licenses/GPLv2.php, with the
 * following added to such license:
 * 
 *      As a special exception, the copyright holders of this software give you
 * permission to link this software with independent modules, and to copy and
 * distribute the resulting executable under terms of your choice, provided that
 * you also meet, for each linked independent module, the terms and conditions of
 * the license of that module.  An independent module is a module which is not
 * derived from this software.  The special exception does not apply to any
 * modifications of the software.
 * 
 *      Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other Broadcom software provided under a license
 * other than the GPL, without Broadcom's express prior written consent.
 *
 * $Id: wlioctl_defs.h 403826 2013-05-22 16:40:55Z $
 */


#ifndef wlioctl_defs_h
#define wlioctl_defs_h





/*                                               */
#undef  D11AC_IOTYPES
#define D11AC_IOTYPES

/*                                       */
#define WL_RSPEC_RATE_MASK      0x000000FF      /*                      */
#define WL_RSPEC_VHT_MCS_MASK   0x0000000F      /*               */
#define WL_RSPEC_VHT_NSS_MASK   0x000000F0      /*               */
#define WL_RSPEC_VHT_NSS_SHIFT  4               /*                     */
#define WL_RSPEC_TXEXP_MASK     0x00000300
#define WL_RSPEC_TXEXP_SHIFT    8
#define WL_RSPEC_BW_MASK        0x00070000      /*                */
#define WL_RSPEC_BW_SHIFT       16              /*                 */
#define WL_RSPEC_STBC           0x00100000      /*                               */
#define WL_RSPEC_TXBF           0x00200000      /*                         */
#define WL_RSPEC_LDPC           0x00400000      /*                                 */
#define WL_RSPEC_SGI            0x00800000      /*               */
#define WL_RSPEC_ENCODING_MASK  0x03000000      /*                            */
#define WL_RSPEC_OVERRIDE_RATE  0x40000000      /*                                   */
#define WL_RSPEC_OVERRIDE_MODE  0x80000000      /*                                         */

/*                              */
#define WL_RSPEC_ENCODE_RATE    0x00000000      /*                                          */
#define WL_RSPEC_ENCODE_HT      0x01000000      /*                                     */
#define WL_RSPEC_ENCODE_VHT     0x02000000      /*                                              */

/*                        */
#define WL_RSPEC_BW_UNSPECIFIED 0
#define WL_RSPEC_BW_20MHZ       0x00010000
#define WL_RSPEC_BW_40MHZ       0x00020000
#define WL_RSPEC_BW_80MHZ       0x00030000
#define WL_RSPEC_BW_160MHZ      0x00040000

/*                                    */
#define OLD_NRATE_MCS_INUSE         0x00000080 /*                                        */
#define OLD_NRATE_RATE_MASK         0x0000007f /*                */
#define OLD_NRATE_STF_MASK          0x0000ff00 /*                                     */
#define OLD_NRATE_STF_SHIFT         8          /*                */
#define OLD_NRATE_OVERRIDE          0x80000000 /*                                         */
#define OLD_NRATE_OVERRIDE_MCS_ONLY 0x40000000 /*                                   */
#define OLD_NRATE_SGI               0x00800000 /*          */
#define OLD_NRATE_LDPC_CODING       0x00400000 /*                                 */

#define OLD_NRATE_STF_SISO	0		/*               */
#define OLD_NRATE_STF_CDD	1		/*              */
#define OLD_NRATE_STF_STBC	2		/*               */
#define OLD_NRATE_STF_SDM	3		/*              */

#define HIGHEST_SINGLE_STREAM_MCS	7 /*                                                      */

#define GET_PRO_PRIETARY_11N_MCS_NSS(mcs) (1 + ((mcs) - 85) / 8)

#define GET_11N_MCS_NSS(mcs) ((mcs) < 32 ? (1 + ((mcs) / 8)) \
				: ((mcs) == 32 ? 1 : GET_PRO_PRIETARY_11N_MCS_NSS(mcs)))

#define MAX_CCA_CHANNELS 38	/*                                    */
#define MAX_CCA_SECS	60	/*                                     */

#define IBSS_MED        15	/*                                     */
#define IBSS_HI         25	/*                                 */
#define OBSS_MED        12
#define OBSS_HI         25
#define INTERFER_MED    5
#define INTERFER_HI     10

#define  CCA_FLAG_2G_ONLY		0x01	/*                                    */
#define  CCA_FLAG_5G_ONLY		0x02	/*                                    */
#define  CCA_FLAG_IGNORE_DURATION	0x04	/*                                    */
#define  CCA_FLAGS_PREFER_1_6_11	0x10
#define  CCA_FLAG_IGNORE_INTERFER 	0x20 /*                                               */

#define CCA_ERRNO_BAND 		1	/*                                                */
#define CCA_ERRNO_DURATION	2	/*                                               */
#define CCA_ERRNO_PREF_CHAN	3	/*                                                */
#define CCA_ERRNO_INTERFER	4	/*                                                   */
#define CCA_ERRNO_TOO_FEW	5	/*                          */

#define WL_STA_AID(a)		((a) &~ 0xc000)

/*                                                   */
#define WL_STA_BRCM		0x00000001	/*                           */
#define WL_STA_WME		0x00000002	/*                 */
#define WL_STA_NONERP		0x00000004	/*        */
#define WL_STA_AUTHE		0x00000008	/*               */
#define WL_STA_ASSOC		0x00000010	/*            */
#define WL_STA_AUTHO		0x00000020	/*            */
#define WL_STA_WDS		0x00000040	/*                              */
#define WL_STA_WDS_LINKUP	0x00000080	/*                                     */
#define WL_STA_PS		0x00000100	/*                                               */
#define WL_STA_APSD_BE		0x00000200	/*                                                */
#define WL_STA_APSD_BK		0x00000400	/*                                                */
#define WL_STA_APSD_VI		0x00000800	/*                                                */
#define WL_STA_APSD_VO		0x00001000	/*                                                */
#define WL_STA_N_CAP		0x00002000	/*                     */
#define WL_STA_SCBSTATS		0x00004000	/*                     */
#define WL_STA_AMPDU_CAP	0x00008000	/*                   */
#define WL_STA_AMSDU_CAP	0x00010000	/*                   */
#define WL_STA_MIMO_PS		0x00020000	/*                         */
#define WL_STA_MIMO_RTS		0x00040000	/*                          */
#define WL_STA_RIFS_CAP		0x00080000	/*              */
#define WL_STA_VHT_CAP		0x00100000	/*                       */
#define WL_STA_WPS		0x00200000	/*           */

#define WL_WDS_LINKUP		WL_STA_WDS_LINKUP	/*            */

/*                   */
#define WL_STA_CAP_LDPC_CODING		0x0001	/*                                   */
#define WL_STA_CAP_40MHZ		0x0002  /*                                      */
#define WL_STA_CAP_MIMO_PS_MASK		0x000C  /*              */
#define WL_STA_CAP_MIMO_PS_SHIFT	0x0002	/*               */
#define WL_STA_CAP_MIMO_PS_OFF		0x0003	/*                         */
#define WL_STA_CAP_MIMO_PS_RTS		0x0001	/*                                          */
#define WL_STA_CAP_MIMO_PS_ON		0x0000	/*                          */
#define WL_STA_CAP_GF			0x0010	/*                             */
#define WL_STA_CAP_SHORT_GI_20		0x0020	/*                                    */
#define WL_STA_CAP_SHORT_GI_40		0x0040	/*                                    */
#define WL_STA_CAP_TX_STBC		0x0080	/*                 */
#define WL_STA_CAP_RX_STBC_MASK		0x0300	/*              */
#define WL_STA_CAP_RX_STBC_SHIFT	8	/*               */
#define WL_STA_CAP_DELAYED_BA		0x0400	/*                    */
#define WL_STA_CAP_MAX_AMSDU		0x0800	/*                                          */
#define WL_STA_CAP_DSSS_CCK		0x1000	/*                               */
#define WL_STA_CAP_PSMP			0x2000	/*                               */
#define WL_STA_CAP_40MHZ_INTOLERANT	0x4000	/*                  */
#define WL_STA_CAP_LSIG_TXOP		0x8000	/*                               */

#define WL_STA_CAP_RX_STBC_NO		0x0	/*                    */
#define WL_STA_CAP_RX_STBC_ONE_STREAM	0x1	/*                                     */
#define WL_STA_CAP_RX_STBC_TWO_STREAM	0x2	/*                                        */
#define WL_STA_CAP_RX_STBC_THREE_STREAM	0x3	/*                                        */

/*               */
#define WL_STA_VHT_LDPCCAP	0x0001
#define WL_STA_SGI80		0x0002
#define WL_STA_SGI160		0x0004
#define WL_STA_VHT_TX_STBCCAP	0x0008
#define WL_STA_VHT_RX_STBCCAP	0x0010
#define WL_STA_SU_BEAMFORMER	0x0020
#define WL_STA_SU_BEAMFORMEE	0x0040
#define WL_STA_MU_BEAMFORMER	0x0080
#define WL_STA_MU_BEAMFORMEE	0x0100
#define WL_STA_VHT_TXOP_PS	0x0200
#define WL_STA_HTC_VHT_CAP	0x0400

/*                                    */
#define WLC_TXFILTER_OVERRIDE_DISABLED  0
#define WLC_TXFILTER_OVERRIDE_ENABLED   1

#define WL_IOCTL_ACTION_GET				0x0
#define WL_IOCTL_ACTION_SET				0x1
#define WL_IOCTL_ACTION_OVL_IDX_MASK	0x1e
#define WL_IOCTL_ACTION_OVL_RSV			0x20
#define WL_IOCTL_ACTION_OVL				0x40
#define WL_IOCTL_ACTION_MASK			0x7e
#define WL_IOCTL_ACTION_OVL_SHIFT		1

#define WL_BSSTYPE_INFRA 1
#define WL_BSSTYPE_INDEP 0
#define WL_BSSTYPE_ANY   2

/*                       */
#define WL_SCANFLAGS_PASSIVE	0x01	/*                    */
#define WL_SCANFLAGS_RESERVED	0x02	/*          */
#define WL_SCANFLAGS_PROHIBITED	0x04	/*                                    */
#define WL_SCANFLAGS_OFFCHAN	0x08	/*                                          */
#define WL_SCANFLAGS_HOTSPOT	0x10	/*                               */
#define WL_SCANFLAGS_SWTCHAN	0x20	/*                                                */

/*                                */
#define WL_SCAN_RESULTS_SUCCESS	0
#define WL_SCAN_RESULTS_PARTIAL	1
#define WL_SCAN_RESULTS_PENDING	2
#define WL_SCAN_RESULTS_ABORTED	3
#define WL_SCAN_RESULTS_NO_MEM  4

#define SCANOL_ENABLED			(1 << 0)
#define SCANOL_BCAST_SSID		(1 << 1)
#define SCANOL_NOTIFY_BCAST_SSID	(1 << 2)
#define SCANOL_RESULTS_PER_CYCLE	(1 << 3)

/*                            */
#define SCANOL_HOME_TIME		45	/*                             */
#define SCANOL_ASSOC_TIME		20	/*                                     */
#define SCANOL_UNASSOC_TIME		40	/*                                       */
#define SCANOL_PASSIVE_TIME		110	/*                                     */
#define SCANOL_AWAY_LIMIT		100	/*                                       */
#define SCANOL_IDLE_REST_TIME		40
#define SCANOL_IDLE_REST_MULTIPLIER	0
#define SCANOL_ACTIVE_REST_TIME		20
#define SCANOL_ACTIVE_REST_MULTIPLIER	0
#define SCANOL_CYCLE_IDLE_REST_TIME	300000	/*                                          */
#define SCANOL_CYCLE_IDLE_REST_MULTIPLIER	0	/*                           */
#define SCANOL_CYCLE_ACTIVE_REST_TIME	200
#define SCANOL_CYCLE_ACTIVE_REST_MULTIPLIER	0
#define SCANOL_MAX_REST_TIME		3600000	/*                                         */
#define SCANOL_CYCLE_DEFAULT		0	/*                                         */
#define SCANOL_CYCLE_MAX		864000	/*                */
						/*                               */
#define SCANOL_NPROBES			2	/*                                                */
#define SCANOL_NPROBES_MAX		5	/*                                                */
#define SCANOL_SCAN_START_DLY		10	/*                                   */
#define SCANOL_SCAN_START_DLY_MAX	240	/*                                   */
#define SCANOL_MULTIPLIER_MAX		10	/*                */
#define SCANOL_UNASSOC_TIME_MAX		100	/*                                           */
#define SCANOL_PASSIVE_TIME_MAX		500	/*                                          */
#define SCANOL_SSID_MAX			16	/*                              */

/*                                  */
#define WL_SCAN_PARAMS_COUNT_MASK 0x0000ffff
#define WL_SCAN_PARAMS_NSSID_SHIFT 16

#define WL_SCAN_ACTION_START      1
#define WL_SCAN_ACTION_CONTINUE   2
#define WL_SCAN_ACTION_ABORT      3

#if defined(SIMPLE_ISCAN)
#define ISCAN_RETRY_CNT   5
#define ISCAN_STATE_IDLE   0
#define ISCAN_STATE_SCANING 1
#define ISCAN_STATE_PENDING 2
#endif /*              */

#define ANTENNA_NUM_1	1		/*                                     */
#define ANTENNA_NUM_2	2
#define ANTENNA_NUM_3	3
#define ANTENNA_NUM_4	4

#define ANT_SELCFG_AUTO		0x80	/*                                */
#define ANT_SELCFG_MASK		0x33	/*                            */
#define ANT_SELCFG_TX_UNICAST	0	/*                                  */
#define ANT_SELCFG_RX_UNICAST	1	/*                                  */
#define ANT_SELCFG_TX_DEF	2	/*                                  */
#define ANT_SELCFG_RX_DEF	3	/*                                  */

/*                                                       */
#define ITFR_MODE_DISABLE	0	/*                 */
#define ITFR_MODE_MANUAL_ENABLE	1	/*                         */
#define ITFR_MODE_AUTO_ENABLE	2	/*                       */

/*                                                         */
#define ITFR_INTERFERENCED	1	/*                       */
#define ITFR_HOME_CHANNEL	2	/*                               */
#define ITFR_NOISY_ENVIRONMENT	4	/*                                      */

#define WL_NUM_RPI_BINS		8
#define WL_RM_TYPE_BASIC	1
#define WL_RM_TYPE_CCA		2
#define WL_RM_TYPE_RPI		3
#define WL_RM_TYPE_ABORT	-1	/*                                  */

#define WL_RM_FLAG_PARALLEL	(1<<0)

#define WL_RM_FLAG_LATE		(1<<1)
#define WL_RM_FLAG_INCAPABLE	(1<<2)
#define WL_RM_FLAG_REFUSED	(1<<3)

/*       */
#define WLC_ASSOC_REQ_IS_REASSOC 0x01 /*                                  */

#define WLC_CIS_DEFAULT	0	/*                  */
#define WLC_CIS_SROM	1	/*                 */
#define WLC_CIS_OTP	2	/*               */

/*                          */
/*                                                */
#define WL_ATTEN_APP_INPUT_PCL_OFF	0	/*                                    */
#define WL_ATTEN_PCL_ON			1	/*             */
/*                                    */
#define WL_ATTEN_PCL_OFF		2	/*               */

#define	PLC_CMD_FAILOVER	1
#define	PLC_CMD_MAC_COST	2
#define	PLC_CMD_LINK_COST	3
#define	PLC_CMD_NODE_LIST	4

#define NODE_TYPE_UNKNOWN	0	/*              */
#define NODE_TYPE_WIFI_ONLY	1	/*                        */
#define NODE_TYPE_PLC_ONLY	2	/*                    */
#define NODE_TYPE_WIFI_PLC	3	/*                       */

/*                                                              */
/*                                    */
#define WL_PWRIDX_PCL_OFF	-2	/*                */
#define WL_PWRIDX_PCL_ON	-1	/*             */
#define WL_PWRIDX_LOWER_LIMIT	-2	/*             */
#define WL_PWRIDX_UPPER_LIMIT	63	/*             */
/*                  
                                  
                  
 */

#define BCM_MAC_STATUS_INDICATION	(0x40010200L)

/*                                    */
#define WLC_TXFILTER_OVERRIDE_DISABLED  0
#define WLC_TXFILTER_OVERRIDE_ENABLED   1

/*                                               */
#define WL_TXFIFO_SZ_MAGIC	0xa5a5

/*                         */
#define WLC_IOCTL_MAGIC		0x14e46c77

/*                      */
#define WL_BSS_FLAGS_FROM_BEACON	0x01	/*                              */
#define WL_BSS_FLAGS_FROM_CACHE		0x02	/*                               */
#define WL_BSS_FLAGS_RSSI_ONCHANNEL	0x04	/*                                               */
#define WL_BSS_FLAGS_HS20		0x08	/*                     */
#define WL_BSS_FLAGS_RSSI_INVALID	0x10	/*                           */
#define WL_BSS_FLAGS_RSSI_INACCURATE	0x20	/*                              */
#define WL_BSS_FLAGS_SNR_INVALID	0x40	/*                          */
#define WL_BSS_FLAGS_NF_INVALID		0x80	/*                                  */

/*                           */
#define VHT_BI_SGI_80MHZ			0x00000100
#define VHT_BI_80MHZ			    0x00000200
#define VHT_BI_160MHZ			    0x00000400
#define VHT_BI_8080MHZ			    0x00000800

/*                                                        */
#define ioctl_subtype	set		/*               */
#define ioctl_pid	used		/*           */
#define ioctl_status	needed		/*              */


/*                             */
#define	CRYPTO_ALGO_OFF			0
#define	CRYPTO_ALGO_WEP1		1
#define	CRYPTO_ALGO_TKIP		2
#define	CRYPTO_ALGO_WEP128		3
#define CRYPTO_ALGO_AES_CCM		4
#define CRYPTO_ALGO_AES_OCB_MSDU	5
#define CRYPTO_ALGO_AES_OCB_MPDU	6
#if !defined(BCMCCX) && !defined(BCMEXTCCX)
#define CRYPTO_ALGO_NALG		7
#else
#define CRYPTO_ALGO_CKIP		7
#define CRYPTO_ALGO_CKIP_MMH	8
#define CRYPTO_ALGO_WEP_MMH		9
#define CRYPTO_ALGO_NALG		10
#endif /*                       */

#define CRYPTO_ALGO_SMS4		11
#define CRYPTO_ALGO_PMK			12	/*                                         */
#define CRYPTO_ALGO_BIP			13  /*                        */

#define CRYPTO_ALGO_AES_GCM     14  /*             */
#define CRYPTO_ALGO_AES_CCM256  15  /*             */
#define CRYPTO_ALGO_AES_GCM256  16  /*             */
#define CRYPTO_ALGO_BIP_CMAC256 17  /*                  */
#define CRYPTO_ALGO_BIP_GMAC    18  /*                  */
#define CRYPTO_ALGO_BIP_GMAC256 19  /*                  */

#define CRYPTO_ALGO_NONE        CRYPTO_ALGO_OFF

#define WSEC_GEN_MIC_ERROR	0x0001
#define WSEC_GEN_REPLAY		0x0002
#define WSEC_GEN_ICV_ERROR	0x0004
#define WSEC_GEN_MFP_ACT_ERROR	0x0008
#define WSEC_GEN_MFP_DISASSOC_ERROR	0x0010
#define WSEC_GEN_MFP_DEAUTH_ERROR	0x0020

#define WL_SOFT_KEY	(1 << 0)	/*                                          */
#define WL_PRIMARY_KEY	(1 << 1)	/*                                               */
#if defined(BCMCCX) || defined(BCMEXTCCX)
#define WL_CKIP_KP	(1 << 4)	/*      */
#define WL_CKIP_MMH	(1 << 5)	/*      */
#else
#define WL_KF_RES_4	(1 << 4)	/*                              */
#define WL_KF_RES_5	(1 << 5)	/*                              */
#endif /*                     */
#define WL_IBSS_PEER_GROUP_KEY	(1 << 6)	/*                                       */

/*                          */
#define WEP_ENABLED		0x0001
#define TKIP_ENABLED		0x0002
#define AES_ENABLED		0x0004
#define WSEC_SWFLAG		0x0008
#ifdef BCMCCX
#define CKIP_KP_ENABLED		0x0010
#define CKIP_MIC_ENABLED	0x0020
#endif /*        */
#define SES_OW_ENABLED		0x0040	/*                                                */
#ifdef BCMWAPI_WPI
#define SMS4_ENABLED		0x0100
#endif /*             */

/*                                                    */
#define WSEC_WEP_ENABLED(wsec)	((wsec) & WEP_ENABLED)
#define WSEC_TKIP_ENABLED(wsec)	((wsec) & TKIP_ENABLED)
#define WSEC_AES_ENABLED(wsec)	((wsec) & AES_ENABLED)

#ifdef BCMCCX
#define WSEC_CKIP_KP_ENABLED(wsec)	((wsec) & CKIP_KP_ENABLED)
#define WSEC_CKIP_MIC_ENABLED(wsec)	((wsec) & CKIP_MIC_ENABLED)
#define WSEC_CKIP_ENABLED(wsec)	((wsec) & (CKIP_KP_ENABLED|CKIP_MIC_ENABLED))

#ifdef BCMWAPI_WPI
#define WSEC_ENABLED(wsec) \
	((wsec) & (WEP_ENABLED | TKIP_ENABLED | AES_ENABLED | CKIP_KP_ENABLED |	\
	  CKIP_MIC_ENABLED | SMS4_ENABLED))
#else /*             */
#define WSEC_ENABLED(wsec) \
		((wsec) & \
		 (WEP_ENABLED | TKIP_ENABLED | AES_ENABLED | CKIP_KP_ENABLED | CKIP_MIC_ENABLED))
#endif /*             */
#else /*                */
#ifdef BCMWAPI_WPI
#define WSEC_ENABLED(wsec)	((wsec) & (WEP_ENABLED | TKIP_ENABLED | AES_ENABLED | SMS4_ENABLED))
#else /*             */
#define WSEC_ENABLED(wsec)	((wsec) & (WEP_ENABLED | TKIP_ENABLED | AES_ENABLED))
#endif /*             */
#endif /*        */
#define WSEC_SES_OW_ENABLED(wsec)	((wsec) & SES_OW_ENABLED)
#ifdef BCMWAPI_WAI
#define WSEC_SMS4_ENABLED(wsec)	((wsec) & SMS4_ENABLED)
#endif /*             */

#define MFP_CAPABLE		0x0200
#define MFP_REQUIRED	0x0400
#define MFP_SHA256		0x0800 /*                                                    */

/*                                */
#define WPA_AUTH_DISABLED	0x0000	/*                        */
#define WPA_AUTH_NONE		0x0001	/*             */
#define WPA_AUTH_UNSPECIFIED	0x0002	/*             */
#define WPA_AUTH_PSK		0x0004	/*                */
#if defined(BCMCCX) || defined(BCMEXTCCX)
#define WPA_AUTH_CCKM		0x0008	/*      */
#define WPA2_AUTH_CCKM		0x0010	/*       */
#endif	/*                     */
/*                               */	/*                  */
#define WPA2_AUTH_UNSPECIFIED	0x0040	/*             */
#define WPA2_AUTH_PSK		0x0080	/*                */
#define BRCM_AUTH_PSK           0x0100  /*                   */
#define BRCM_AUTH_DPT		0x0200	/*                            */
#if defined(BCMWAPI_WAI) || defined(BCMWAPI_WPI)
#define WPA_AUTH_WAPI           0x0400
#define WAPI_AUTH_NONE		WPA_AUTH_NONE	/*             */
#define WAPI_AUTH_UNSPECIFIED	0x0400	/*         */
#define WAPI_AUTH_PSK		0x0800	/*                */
#endif /*                            */
#define WPA2_AUTH_MFP           0x1000  /*                              */
#define WPA2_AUTH_TPK		0x2000 	/*               */
#define WPA2_AUTH_FT		0x4000 	/*                  */
#define WPA_AUTH_PFN_ANY	0xffffffff	/*                          */

/*       */
#define	MAXPMKID		16

#ifdef SROM12
#define	WLC_IOCTL_MAXLEN		10000	/*                                  */
#else
#define	WLC_IOCTL_MAXLEN		8192	/*                                  */
#endif /*        */

#define	WLC_IOCTL_SMLEN			256	/*                                      */
#define WLC_IOCTL_MEDLEN		1536    /*                                    */
#if defined(LCNCONF) || defined(LCN40CONF)
#define WLC_SAMPLECOLLECT_MAXLEN	1024	/*                           */
#else
#define WLC_SAMPLECOLLECT_MAXLEN	10240	/*                                         */
#endif
#define WLC_SAMPLECOLLECT_MAXLEN_LCN40  8192

/*                          */
#define WLC_GET_MAGIC				0
#define WLC_GET_VERSION				1
#define WLC_UP					2
#define WLC_DOWN				3
#define WLC_GET_LOOP				4
#define WLC_SET_LOOP				5
#define WLC_DUMP				6
#define WLC_GET_MSGLEVEL			7
#define WLC_SET_MSGLEVEL			8
#define WLC_GET_PROMISC				9
#define WLC_SET_PROMISC				10
/*                                */ /*               */
#define WLC_GET_RATE				12
#define WLC_GET_MAX_RATE			13
#define WLC_GET_INSTANCE			14
/*                            */ /*                     */
/*                            */ /*                     */
/*                           */ /*                     */
/*                           */ /*                     */
#define WLC_GET_INFRA				19
#define WLC_SET_INFRA				20
#define WLC_GET_AUTH				21
#define WLC_SET_AUTH				22
#define WLC_GET_BSSID				23
#define WLC_SET_BSSID				24
#define WLC_GET_SSID				25
#define WLC_SET_SSID				26
#define WLC_RESTART				27
#define WLC_TERMINATED				28
/*                            */ /*                     */
#define WLC_GET_CHANNEL				29
#define WLC_SET_CHANNEL				30
#define WLC_GET_SRL				31
#define WLC_SET_SRL				32
#define WLC_GET_LRL				33
#define WLC_SET_LRL				34
#define WLC_GET_PLCPHDR				35
#define WLC_SET_PLCPHDR				36
#define WLC_GET_RADIO				37
#define WLC_SET_RADIO				38
#define WLC_GET_PHYTYPE				39
#define WLC_DUMP_RATE				40
#define WLC_SET_RATE_PARAMS			41
#define WLC_GET_FIXRATE				42
#define WLC_SET_FIXRATE				43
/*                           */ /*                     */
/*                           */ /*                     */
#define WLC_GET_KEY				44
#define WLC_SET_KEY				45
#define WLC_GET_REGULATORY			46
#define WLC_SET_REGULATORY			47
#define WLC_GET_PASSIVE_SCAN			48
#define WLC_SET_PASSIVE_SCAN			49
#define WLC_SCAN				50
#define WLC_SCAN_RESULTS			51
#define WLC_DISASSOC				52
#define WLC_REASSOC				53
#define WLC_GET_ROAM_TRIGGER			54
#define WLC_SET_ROAM_TRIGGER			55
#define WLC_GET_ROAM_DELTA			56
#define WLC_SET_ROAM_DELTA			57
#define WLC_GET_ROAM_SCAN_PERIOD		58
#define WLC_SET_ROAM_SCAN_PERIOD		59
#define WLC_EVM					60	/*      */
#define WLC_GET_TXANT				61
#define WLC_SET_TXANT				62
#define WLC_GET_ANTDIV				63
#define WLC_SET_ANTDIV				64
/*                            */ /*                     */
/*                            */ /*                     */
#define WLC_GET_CLOSED				67
#define WLC_SET_CLOSED				68
#define WLC_GET_MACLIST				69
#define WLC_SET_MACLIST				70
#define WLC_GET_RATESET				71
#define WLC_SET_RATESET				72
/*                             */ /*                     */
#define WLC_LONGTRAIN				74
#define WLC_GET_BCNPRD				75
#define WLC_SET_BCNPRD				76
#define WLC_GET_DTIMPRD				77
#define WLC_SET_DTIMPRD				78
#define WLC_GET_SROM				79
#define WLC_SET_SROM				80
#define WLC_GET_WEP_RESTRICT			81
#define WLC_SET_WEP_RESTRICT			82
#define WLC_GET_COUNTRY				83
#define WLC_SET_COUNTRY				84
#define WLC_GET_PM				85
#define WLC_SET_PM				86
#define WLC_GET_WAKE				87
#define WLC_SET_WAKE				88
/*                              */ /*                     */
#define WLC_GET_FORCELINK			90	/*           */
#define WLC_SET_FORCELINK			91	/*           */
#define WLC_FREQ_ACCURACY			92	/*      */
#define WLC_CARRIER_SUPPRESS			93	/*      */
#define WLC_GET_PHYREG				94
#define WLC_SET_PHYREG				95
#define WLC_GET_RADIOREG			96
#define WLC_SET_RADIOREG			97
#define WLC_GET_REVINFO				98
#define WLC_GET_UCANTDIV			99
#define WLC_SET_UCANTDIV			100
#define WLC_R_REG				101
#define WLC_W_REG				102
/*                                               */
/*                                 */ /*                          */
#define WLC_GET_MACMODE				105
#define WLC_SET_MACMODE				106
#define WLC_GET_MONITOR				107
#define WLC_SET_MONITOR				108
#define WLC_GET_GMODE				109
#define WLC_SET_GMODE				110
#define WLC_GET_LEGACY_ERP			111
#define WLC_SET_LEGACY_ERP			112
#define WLC_GET_RX_ANT				113
#define WLC_GET_CURR_RATESET			114	/*                 */
#define WLC_GET_SCANSUPPRESS			115
#define WLC_SET_SCANSUPPRESS			116
#define WLC_GET_AP				117
#define WLC_SET_AP				118
#define WLC_GET_EAP_RESTRICT			119
#define WLC_SET_EAP_RESTRICT			120
#define WLC_SCB_AUTHORIZE			121
#define WLC_SCB_DEAUTHORIZE			122
#define WLC_GET_WDSLIST				123
#define WLC_SET_WDSLIST				124
#define WLC_GET_ATIM				125
#define WLC_SET_ATIM				126
#define WLC_GET_RSSI				127
#define WLC_GET_PHYANTDIV			128
#define WLC_SET_PHYANTDIV			129
#define WLC_AP_RX_ONLY				130
#define WLC_GET_TX_PATH_PWR			131
#define WLC_SET_TX_PATH_PWR			132
#define WLC_GET_WSEC				133
#define WLC_SET_WSEC				134
#define WLC_GET_PHY_NOISE			135
#define WLC_GET_BSS_INFO			136
#define WLC_GET_PKTCNTS				137
#define WLC_GET_LAZYWDS				138
#define WLC_SET_LAZYWDS				139
#define WLC_GET_BANDLIST			140

#define WLC_GET_BAND				141
#define WLC_SET_BAND				142
#define WLC_SCB_DEAUTHENTICATE			143
#define WLC_GET_SHORTSLOT			144
#define WLC_GET_SHORTSLOT_OVERRIDE		145
#define WLC_SET_SHORTSLOT_OVERRIDE		146
#define WLC_GET_SHORTSLOT_RESTRICT		147
#define WLC_SET_SHORTSLOT_RESTRICT		148
#define WLC_GET_GMODE_PROTECTION		149
#define WLC_GET_GMODE_PROTECTION_OVERRIDE	150
#define WLC_SET_GMODE_PROTECTION_OVERRIDE	151
#define WLC_UPGRADE				152
/*                             */ /*                     */
/*                             */ /*                     */
#define WLC_GET_IGNORE_BCNS			155
#define WLC_SET_IGNORE_BCNS			156
#define WLC_GET_SCB_TIMEOUT			157
#define WLC_SET_SCB_TIMEOUT			158
#define WLC_GET_ASSOCLIST			159
#define WLC_GET_CLK				160
#define WLC_SET_CLK				161
#define WLC_GET_UP				162
#define WLC_OUT					163
#define WLC_GET_WPA_AUTH			164
#define WLC_SET_WPA_AUTH			165
#define WLC_GET_UCFLAGS				166
#define WLC_SET_UCFLAGS				167
#define WLC_GET_PWRIDX				168
#define WLC_SET_PWRIDX				169
#define WLC_GET_TSSI				170
#define WLC_GET_SUP_RATESET_OVERRIDE		171
#define WLC_SET_SUP_RATESET_OVERRIDE		172
/*                                  */ /*                     */
/*                                  */ /*                     */
/*                                  */ /*                     */
/*                                  */ /*                     */
/*                                */ /*                     */
#define WLC_GET_PROTECTION_CONTROL		178
#define WLC_SET_PROTECTION_CONTROL		179
#define WLC_GET_PHYLIST				180
#define WLC_ENCRYPT_STRENGTH			181	/*           */
#define WLC_DECRYPT_STATUS			182	/*           */
#define WLC_GET_KEY_SEQ				183
#define WLC_GET_SCAN_CHANNEL_TIME		184
#define WLC_SET_SCAN_CHANNEL_TIME		185
#define WLC_GET_SCAN_UNASSOC_TIME		186
#define WLC_SET_SCAN_UNASSOC_TIME		187
#define WLC_GET_SCAN_HOME_TIME			188
#define WLC_SET_SCAN_HOME_TIME			189
#define WLC_GET_SCAN_NPROBES			190
#define WLC_SET_SCAN_NPROBES			191
#define WLC_GET_PRB_RESP_TIMEOUT		192
#define WLC_SET_PRB_RESP_TIMEOUT		193
#define WLC_GET_ATTEN				194
#define WLC_SET_ATTEN				195
#define WLC_GET_SHMEM				196	/*      */
#define WLC_SET_SHMEM				197	/*      */
/*                                           */ /*                     */
/*                                           */ /*                     */
#define WLC_SET_WSEC_TEST			200
#define WLC_SCB_DEAUTHENTICATE_FOR_REASON	201
#define WLC_TKIP_COUNTERMEASURES		202
#define WLC_GET_PIOMODE				203
#define WLC_SET_PIOMODE				204
#define WLC_SET_ASSOC_PREFER			205
#define WLC_GET_ASSOC_PREFER			206
#define WLC_SET_ROAM_PREFER			207
#define WLC_GET_ROAM_PREFER			208
#define WLC_SET_LED				209
#define WLC_GET_LED				210
#define WLC_GET_INTERFERENCE_MODE		211
#define WLC_SET_INTERFERENCE_MODE		212
#define WLC_GET_CHANNEL_QA			213
#define WLC_START_CHANNEL_QA			214
#define WLC_GET_CHANNEL_SEL			215
#define WLC_START_CHANNEL_SEL			216
#define WLC_GET_VALID_CHANNELS			217
#define WLC_GET_FAKEFRAG			218
#define WLC_SET_FAKEFRAG			219
#define WLC_GET_PWROUT_PERCENTAGE		220
#define WLC_SET_PWROUT_PERCENTAGE		221
#define WLC_SET_BAD_FRAME_PREEMPT		222
#define WLC_GET_BAD_FRAME_PREEMPT		223
#define WLC_SET_LEAP_LIST			224
#define WLC_GET_LEAP_LIST			225
#define WLC_GET_CWMIN				226
#define WLC_SET_CWMIN				227
#define WLC_GET_CWMAX				228
#define WLC_SET_CWMAX				229
#define WLC_GET_WET				230
#define WLC_SET_WET				231
#define WLC_GET_PUB				232
/*                                    */ /*                     */
/*                                    */ /*                     */
#define WLC_GET_KEY_PRIMARY			235
#define WLC_SET_KEY_PRIMARY			236


/*                                  */ /*                     */
#define WLC_GET_ACI_ARGS			238
#define WLC_SET_ACI_ARGS			239
#define WLC_UNSET_CALLBACK			240
#define WLC_SET_CALLBACK			241
#define WLC_GET_RADAR				242
#define WLC_SET_RADAR				243
#define WLC_SET_SPECT_MANAGMENT			244
#define WLC_GET_SPECT_MANAGMENT			245
#define WLC_WDS_GET_REMOTE_HWADDR		246	/*                               */
#define WLC_WDS_GET_WPA_SUP			247
#define WLC_SET_CS_SCAN_TIMER			248
#define WLC_GET_CS_SCAN_TIMER			249
#define WLC_MEASURE_REQUEST			250
#define WLC_INIT				251
#define WLC_SEND_QUIET				252
#define WLC_KEEPALIVE			253
#define WLC_SEND_PWR_CONSTRAINT			254
#define WLC_UPGRADE_STATUS			255
#define WLC_CURRENT_PWR				256
#define WLC_GET_SCAN_PASSIVE_TIME		257
#define WLC_SET_SCAN_PASSIVE_TIME		258
#define WLC_LEGACY_LINK_BEHAVIOR		259
#define WLC_GET_CHANNELS_IN_COUNTRY		260
#define WLC_GET_COUNTRY_LIST			261
#define WLC_GET_VAR				262	/*                             */
#define WLC_SET_VAR				263	/*                             */
#define WLC_NVRAM_GET				264	/*            */
#define WLC_NVRAM_SET				265
#define WLC_NVRAM_DUMP				266
#define WLC_REBOOT				267
#define WLC_SET_WSEC_PMK			268
#define WLC_GET_AUTH_MODE			269
#define WLC_SET_AUTH_MODE			270
#define WLC_GET_WAKEENTRY			271
#define WLC_SET_WAKEENTRY			272
#define WLC_NDCONFIG_ITEM			273	/*                               */
#define WLC_NVOTPW				274
#define WLC_OTPW				275
#define WLC_IOV_BLOCK_GET			276
#define WLC_IOV_MODULES_GET			277
#define WLC_SOFT_RESET				278
#define WLC_GET_ALLOW_MODE			279
#define WLC_SET_ALLOW_MODE			280
#define WLC_GET_DESIRED_BSSID			281
#define WLC_SET_DESIRED_BSSID			282
#define	WLC_DISASSOC_MYAP			283
#define WLC_GET_NBANDS				284	/*                            */
#define WLC_GET_BANDSTATES			285	/*                            */
#define WLC_GET_WLC_BSS_INFO			286	/*                            */
#define WLC_GET_ASSOC_INFO			287	/*                            */
#define WLC_GET_OID_PHY				288	/*                            */
#define WLC_SET_OID_PHY				289	/*                            */
#define WLC_SET_ASSOC_TIME			290	/*                            */
#define WLC_GET_DESIRED_SSID			291	/*                            */
#define WLC_GET_CHANSPEC			292	/*                            */
#define WLC_GET_ASSOC_STATE			293	/*                            */
#define WLC_SET_PHY_STATE			294	/*                            */
#define WLC_GET_SCAN_PENDING			295	/*                            */
#define WLC_GET_SCANREQ_PENDING			296	/*                            */
#define WLC_GET_PREV_ROAM_REASON		297	/*                            */
#define WLC_SET_PREV_ROAM_REASON		298	/*                            */
#define WLC_GET_BANDSTATES_PI			299	/*                            */
#define WLC_GET_PHY_STATE			300	/*                            */
#define WLC_GET_BSS_WPA_RSN			301	/*                            */
#define WLC_GET_BSS_WPA2_RSN			302	/*                            */
#define WLC_GET_BSS_BCN_TS			303	/*                            */
#define WLC_GET_INT_DISASSOC			304	/*                            */
#define WLC_SET_NUM_PEERS			305     /*                            */
#define WLC_GET_NUM_BSS				306	/*                            */
#define WLC_PHY_SAMPLE_COLLECT			307	/*                         */
/*                            */	/*                             */
#define WLC_GET_CMD				309
/*                         */	/*                            */
#define WLC_SET_INTERFERENCE_OVERRIDE_MODE	311	/*                         */
#define WLC_GET_INTERFERENCE_OVERRIDE_MODE	312	/*                         */
/*                                    */	/*                                        */
/*                                    */	/*                                        */
/*                                 */	/*                                        */
#define WLC_SET_NAT_CONFIG			316	/*                                   */
#define WLC_GET_NAT_STATE			317
#define WLC_GET_TXBF_RATESET			318
#define WLC_SET_TXBF_RATESET			319
#define WLC_SCAN_CQ				320
#define WLC_GET_RSSI_QDB			321 /*                         */
#define WLC_DUMP_RATESET			322
#define WLC_ECHO				323
#define WLC_LAST				324
#ifndef EPICTRL_COOKIE
#define EPICTRL_COOKIE		0xABADCEDE
#endif

/*                       */
#define CMN_IOCTL_OFF 0x180

/*
                     
  
                                     
                                              
                                               
                               
 */

/*                                                            */
#define WL_OID_BASE		0xFFE41420

/*                */
#define OID_WL_GETINSTANCE	(WL_OID_BASE + WLC_GET_INSTANCE)
#define OID_WL_GET_FORCELINK	(WL_OID_BASE + WLC_GET_FORCELINK)
#define OID_WL_SET_FORCELINK	(WL_OID_BASE + WLC_SET_FORCELINK)
#define	OID_WL_ENCRYPT_STRENGTH	(WL_OID_BASE + WLC_ENCRYPT_STRENGTH)
#define OID_WL_DECRYPT_STATUS	(WL_OID_BASE + WLC_DECRYPT_STATUS)
#define OID_LEGACY_LINK_BEHAVIOR (WL_OID_BASE + WLC_LEGACY_LINK_BEHAVIOR)
#define OID_WL_NDCONFIG_ITEM	(WL_OID_BASE + WLC_NDCONFIG_ITEM)

/*                        */
#define OID_STA_CHANSPEC	(WL_OID_BASE + WLC_GET_CHANSPEC)
#define OID_STA_NBANDS		(WL_OID_BASE + WLC_GET_NBANDS)
#define OID_STA_GET_PHY		(WL_OID_BASE + WLC_GET_OID_PHY)
#define OID_STA_SET_PHY		(WL_OID_BASE + WLC_SET_OID_PHY)
#define OID_STA_ASSOC_TIME	(WL_OID_BASE + WLC_SET_ASSOC_TIME)
#define OID_STA_DESIRED_SSID	(WL_OID_BASE + WLC_GET_DESIRED_SSID)
#define OID_STA_SET_PHY_STATE	(WL_OID_BASE + WLC_SET_PHY_STATE)
#define OID_STA_SCAN_PENDING	(WL_OID_BASE + WLC_GET_SCAN_PENDING)
#define OID_STA_SCANREQ_PENDING (WL_OID_BASE + WLC_GET_SCANREQ_PENDING)
#define OID_STA_GET_ROAM_REASON (WL_OID_BASE + WLC_GET_PREV_ROAM_REASON)
#define OID_STA_SET_ROAM_REASON (WL_OID_BASE + WLC_SET_PREV_ROAM_REASON)
#define OID_STA_GET_PHY_STATE	(WL_OID_BASE + WLC_GET_PHY_STATE)
#define OID_STA_INT_DISASSOC	(WL_OID_BASE + WLC_GET_INT_DISASSOC)
#define OID_STA_SET_NUM_PEERS	(WL_OID_BASE + WLC_SET_NUM_PEERS)
#define OID_STA_GET_NUM_BSS	(WL_OID_BASE + WLC_GET_NUM_BSS)

/*                           */
#define OID_NAT_SET_CONFIG	(WL_OID_BASE + WLC_SET_NAT_CONFIG)
#define OID_NAT_GET_STATE	(WL_OID_BASE + WLC_GET_NAT_STATE)

#define WL_DECRYPT_STATUS_SUCCESS	1
#define WL_DECRYPT_STATUS_FAILURE	2
#define WL_DECRYPT_STATUS_UNKNOWN	3

/*                                                              */
#define WLC_UPGRADE_SUCCESS			0
#define WLC_UPGRADE_PENDING			1

/*                                   */
#define WL_AUTH_OPEN_SYSTEM		0	/*                         */
#define WL_AUTH_SHARED_KEY		1	/*                           */
#define WL_AUTH_OPEN_SHARED		2	/*                                              */

/*                                                                       
                                                       
 */
#define WLC_TXPWR_MAX		(127)	/*                    */

/*                                      */
#define WL_DIAG_INTERRUPT			1	/*                             */
#define WL_DIAG_LOOPBACK			2	/*                        */
#define WL_DIAG_MEMORY				3	/*                 */
#define WL_DIAG_LED				4	/*          */
#define WL_DIAG_REG				5	/*                       */
#define WL_DIAG_SROM				6	/*                    */
#define WL_DIAG_DMA				7	/*          */
#define WL_DIAG_LOOPBACK_EXT			8	/*                                 */

#define WL_DIAGERR_SUCCESS			0
#define WL_DIAGERR_FAIL_TO_RUN			1	/*                              */
#define WL_DIAGERR_NOT_SUPPORTED		2	/*                                 */
#define WL_DIAGERR_INTERRUPT_FAIL		3	/*                                */
#define WL_DIAGERR_LOOPBACK_FAIL		4	/*                           */
#define WL_DIAGERR_SROM_FAIL			5	/*                  */
#define WL_DIAGERR_SROM_BADCRC			6	/*                 */
#define WL_DIAGERR_REG_FAIL			7	/*                              */
#define WL_DIAGERR_MEMORY_FAIL			8	/*                        */
#define WL_DIAGERR_NOMEM			9	/*                                   */
#define WL_DIAGERR_DMA_FAIL			10	/*                 */

#define WL_DIAGERR_MEMORY_TIMEOUT		11	/*                                       */
#define WL_DIAGERR_MEMORY_BADPATTERN		12	/*                                       */

/*            */
#define	WLC_BAND_AUTO		0	/*             */
#define	WLC_BAND_5G		1	/*       */
#define	WLC_BAND_2G		2	/*         */
#define	WLC_BAND_ALL		3	/*           */

/*                                         */
#define WL_CHAN_FREQ_RANGE_2G      0
#define WL_CHAN_FREQ_RANGE_5GL     1
#define WL_CHAN_FREQ_RANGE_5GM     2
#define WL_CHAN_FREQ_RANGE_5GH     3

#define WL_CHAN_FREQ_RANGE_5GLL_5BAND    4
#define WL_CHAN_FREQ_RANGE_5GLH_5BAND    5
#define WL_CHAN_FREQ_RANGE_5GML_5BAND    6
#define WL_CHAN_FREQ_RANGE_5GMH_5BAND    7
#define WL_CHAN_FREQ_RANGE_5GH_5BAND     8

#define WL_CHAN_FREQ_RANGE_5G_BAND0     1
#define WL_CHAN_FREQ_RANGE_5G_BAND1     2
#define WL_CHAN_FREQ_RANGE_5G_BAND2     3
#define WL_CHAN_FREQ_RANGE_5G_BAND3     4

#ifdef SROM12
#define WL_CHAN_FREQ_RANGE_5G_BAND4 5
#define WL_CHAN_FREQ_RANGE_2G_40 6
#define WL_CHAN_FREQ_RANGE_5G_BAND0_40 7
#define WL_CHAN_FREQ_RANGE_5G_BAND1_40 8
#define WL_CHAN_FREQ_RANGE_5G_BAND2_40 9
#define WL_CHAN_FREQ_RANGE_5G_BAND3_40 10
#define WL_CHAN_FREQ_RANGE_5G_BAND4_40 11
#define WL_CHAN_FREQ_RANGE_5G_BAND0_80 12
#define WL_CHAN_FREQ_RANGE_5G_BAND1_80 13
#define WL_CHAN_FREQ_RANGE_5G_BAND2_80 14
#define WL_CHAN_FREQ_RANGE_5G_BAND3_80 15
#define WL_CHAN_FREQ_RANGE_5G_BAND4_80 16

#define WL_CHAN_FREQ_RANGE_5G_4BAND	17
#define WL_CHAN_FREQ_RANGE_5G_5BAND	18
#define WL_CHAN_FREQ_RANGE_5G_5BAND_40	19
#define WL_CHAN_FREQ_RANGE_5G_5BAND_80	20
#else
#define WL_CHAN_FREQ_RANGE_5G_4BAND	5
#endif /*        */
/*                */
#define WLC_MACMODE_DISABLED	0	/*                   */
#define WLC_MACMODE_DENY	1	/*                                         */
#define WLC_MACMODE_ALLOW	2	/*                                         */

/*
                                                 
  
                                            
                     
                     
                                                           
                                     
                     
                      
                                                            
                                       
                               
                      
                                                                
                                     
                     
                    
                                                                                  
                               
                                 
                                          
                                                     
                     
                      
 */
#define GMODE_LEGACY_B		0
#define GMODE_AUTO		1
#define GMODE_ONLY		2
#define GMODE_B_DEFERRED	3
#define GMODE_PERFORMANCE	4
#define GMODE_LRS		5
#define GMODE_MAX		6

/*                             */
#define WLC_PLCP_AUTO	-1
#define WLC_PLCP_SHORT	0
#define WLC_PLCP_LONG	1

/*                                                            */
#define WLC_PROTECTION_AUTO		-1
#define WLC_PROTECTION_OFF		0
#define WLC_PROTECTION_ON		1
#define WLC_PROTECTION_MMHDR_ONLY	2
#define WLC_PROTECTION_CTS_ONLY		3

/*                                                          */
#define WLC_PROTECTION_CTL_OFF		0
#define WLC_PROTECTION_CTL_LOCAL	1
#define WLC_PROTECTION_CTL_OVERLAP	2

/*                         */
#define WLC_N_PROTECTION_OFF		0
#define WLC_N_PROTECTION_OPTIONAL	1
#define WLC_N_PROTECTION_20IN40		2
#define WLC_N_PROTECTION_MIXEDMODE	3

/*                            */
#define WLC_N_PREAMBLE_MIXEDMODE	0
#define WLC_N_PREAMBLE_GF		1
#define WLC_N_PREAMBLE_GF_BRCM          2

/*                                                          */
#define WLC_N_BW_20ALL			0
#define WLC_N_BW_40ALL			1
#define WLC_N_BW_20IN2G_40IN5G		2

#define WLC_BW_20MHZ_BIT		(1<<0)
#define WLC_BW_40MHZ_BIT		(1<<1)
#define WLC_BW_80MHZ_BIT		(1<<2)
#define WLC_BW_160MHZ_BIT		(1<<3)

/*                        */
#define WLC_BW_CAP_20MHZ		(WLC_BW_20MHZ_BIT)
#define WLC_BW_CAP_40MHZ		(WLC_BW_40MHZ_BIT|WLC_BW_20MHZ_BIT)
#define WLC_BW_CAP_80MHZ		(WLC_BW_80MHZ_BIT|WLC_BW_40MHZ_BIT|WLC_BW_20MHZ_BIT)
#define WLC_BW_CAP_160MHZ		(WLC_BW_160MHZ_BIT|WLC_BW_80MHZ_BIT| \
	WLC_BW_40MHZ_BIT|WLC_BW_20MHZ_BIT)
#define WLC_BW_CAP_UNRESTRICTED		0xFF

#define WL_BW_CAP_20MHZ(bw_cap)	(((bw_cap) & WLC_BW_20MHZ_BIT) ? TRUE : FALSE)
#define WL_BW_CAP_40MHZ(bw_cap)	(((bw_cap) & WLC_BW_40MHZ_BIT) ? TRUE : FALSE)
#define WL_BW_CAP_80MHZ(bw_cap)	(((bw_cap) & WLC_BW_80MHZ_BIT) ? TRUE : FALSE)
#define WL_BW_CAP_160MHZ(bw_cap)(((bw_cap) & WLC_BW_160MHZ_BIT) ? TRUE : FALSE)

/*                             */
#define WLC_N_TXRX_CHAIN0		0
#define WLC_N_TXRX_CHAIN1		1

/*                                         */
#define WLC_N_SGI_20			0x01
#define WLC_N_SGI_40			0x02
#define WLC_VHT_SGI_80			0x04

/*                                                                         */
#define WLC_SGI_ALL				0x02

#define LISTEN_INTERVAL			10
/*                                 */
#define	INTERFERE_OVRRIDE_OFF	-1	/*                           */
#define	INTERFERE_NONE	0	/*     */
#define	NON_WLAN	1	/*                                                 */
#define	WLAN_MANUAL	2	/*                        */
#define	WLAN_AUTO	3	/*                  */
#define	WLAN_AUTO_W_NOISE	4	/*                                                */
#define AUTO_ACTIVE	(1 << 7) /*                          */

/*                                     */
#define ACPHY_ACI_GLITCHBASED_DESENSE 1   /*       */
#define ACPHY_ACI_HWACI_PKTGAINLMT 2      /*       */
#define ACPHY_ACI_W2NB_PKTGAINLMT 4       /*       */
#define ACPHY_ACI_PREEMPTION 8            /*       */
#define ACPHY_HWACI_MITIGATION 16            /*       */
#define ACPHY_ACI_MAX_MODE 31

/*                */
#define AP_ENV_DETECT_NOT_USED		0 /*                                          */
#define AP_ENV_DENSE			1 /*                                           */
#define AP_ENV_SPARSE			2 /*                                    */
#define AP_ENV_INDETERMINATE		3 /*                                       */

#define TRIGGER_NOW				0
#define TRIGGER_CRS				0x01
#define TRIGGER_CRSDEASSERT			0x02
#define TRIGGER_GOODFCS				0x04
#define TRIGGER_BADFCS				0x08
#define TRIGGER_BADPLCP				0x10
#define TRIGGER_CRSGLITCH			0x20

#define	WL_SAMPLEDATA_HEADER_TYPE	1
#define WL_SAMPLEDATA_HEADER_SIZE	80	/*                                    */
#define	WL_SAMPLEDATA_TYPE		2
#define	WL_SAMPLEDATA_SEQ		0xff	/*            */
#define	WL_SAMPLEDATA_MORE_DATA		0x100	/*                */

/*              */
#define WL_OTA_ARG_PARSE_BLK_SIZE	1200
#define WL_OTA_TEST_MAX_NUM_RATE	30
#define WL_OTA_TEST_MAX_NUM_SEQ		100

#define WL_THRESHOLD_LO_BAND	70	/*                              */

/*                         */
#define WL_RADAR_DETECTOR_OFF		0	/*                    */
#define WL_RADAR_DETECTOR_ON		1	/*                   */
#define WL_RADAR_SIMULATED		2	/*                                
                       
       */
#define WL_RSSI_ANT_VERSION	1	/*                                  */
#define WL_ANT_RX_MAX		2	/*                        */
#define WL_ANT_HT_RX_MAX	3	/*                              */
#define WL_ANT_IDX_1		0	/*                 */
#define WL_ANT_IDX_2		1	/*                 */

#ifndef WL_RSSI_ANT_MAX
#define WL_RSSI_ANT_MAX		4	/*                          */
#elif WL_RSSI_ANT_MAX != 4
#error "WL_RSSI_ANT_MAX does not match"
#endif

/*                                  */

/*                                  
                              
                                       
 */

/*                  */
#define WL_DFS_CACSTATE_IDLE		0	/*                                          */
#define	WL_DFS_CACSTATE_PREISM_CAC	1	/*                 */
#define WL_DFS_CACSTATE_ISM		2	/*                 */
#define WL_DFS_CACSTATE_CSA		3	/*     */
#define WL_DFS_CACSTATE_POSTISM_CAC	4	/*         */
#define WL_DFS_CACSTATE_PREISM_OOC	5	/*            */
#define WL_DFS_CACSTATE_POSTISM_OOC	6	/*             */
#define WL_DFS_CACSTATES		7	/*                        */

/*                                                  */
#define WL_BW_20MHZ		0
#define WL_BW_40MHZ		1
#define WL_BW_80MHZ		2
#define WL_BW_160MHZ		3
#define WL_BW_8080MHZ		4

/*                       */
#define WL_TX_POWER_F_ENABLED	1
#define WL_TX_POWER_F_HW		2
#define WL_TX_POWER_F_MIMO		4
#define WL_TX_POWER_F_SISO		8
#define WL_TX_POWER_F_HT		0x10
#define WL_TX_POWER_F_VHT		0x20
#define WL_TX_POWER_F_OPENLOOP		0x40

/*                */
#define WL_ERROR_VAL		0x00000001
#define WL_TRACE_VAL		0x00000002
#define WL_PRHDRS_VAL		0x00000004
#define WL_PRPKT_VAL		0x00000008
#define WL_INFORM_VAL		0x00000010
#define WL_TMP_VAL		0x00000020
#define WL_OID_VAL		0x00000040
#define WL_RATE_VAL		0x00000080
#define WL_ASSOC_VAL		0x00000100
#define WL_PRUSR_VAL		0x00000200
#define WL_PS_VAL		0x00000400
#define WL_TXPWR_VAL		0x00000800	/*                             */
#define WL_MODE_SWITCH_VAL	0x00000800 /*                         */
#define WL_PORT_VAL		0x00001000
#define WL_DUAL_VAL		0x00002000
#define WL_WSEC_VAL		0x00004000
#define WL_WSEC_DUMP_VAL	0x00008000
#define WL_LOG_VAL		0x00010000
#define WL_NRSSI_VAL		0x00020000	/*                             */
#define WL_LOFT_VAL		0x00040000	/*                             */
#define WL_REGULATORY_VAL	0x00080000
#define WL_TAF_VAL		0x00100000
#define WL_RADAR_VAL		0x00200000	/*                             */
#define WL_MPC_VAL		0x00400000
#define WL_APSTA_VAL		0x00800000
#define WL_DFS_VAL		0x01000000
#define WL_BA_VAL		0x02000000	/*                             */
#define WL_ACI_VAL		0x04000000
#define WL_PRMAC_VAL		0x04000000
#define WL_MBSS_VAL		0x04000000
#define WL_CAC_VAL		0x08000000
#define WL_AMSDU_VAL		0x10000000
#define WL_AMPDU_VAL		0x20000000
#define WL_FFPLD_VAL		0x40000000

/*                                                                  
                            
 */
#define WL_DPT_VAL		0x00000001
#define WL_SCAN_VAL		0x00000002
#define WL_WOWL_VAL		0x00000004
#define WL_COEX_VAL		0x00000008
#define WL_RTDC_VAL		0x00000010
#define WL_PROTO_VAL		0x00000020
#define WL_BTA_VAL		0x00000040
#define WL_CHANINT_VAL		0x00000080
#define WL_WMF_VAL		0x00000100
#define WL_P2P_VAL		0x00000200
#define WL_ITFR_VAL		0x00000400
#define WL_MCHAN_VAL		0x00000800
#define WL_TDLS_VAL		0x00001000
#define WL_MCNX_VAL		0x00002000
#define WL_PROT_VAL		0x00004000
#define WL_PSTA_VAL		0x00008000
#define WL_TSO_VAL		0x00010000
#define WL_TRF_MGMT_VAL		0x00020000
#define WL_LPC_VAL	        0x00040000
#define WL_L2FILTER_VAL		0x00080000
#define WL_TXBF_VAL		0x00100000
#define WL_P2PO_VAL		0x00200000
#define WL_TBTT_VAL		0x00400000
#define WL_MQ_VAL		0x01000000

/*                                               */
#define WL_SRSCAN_VAL		0x02000000

#define WL_WNM_VAL		0x04000000
#define WL_PWRSEL_VAL		0x10000000
#define WL_NET_DETECT_VAL	0x20000000
#define WL_PCIE_VAL		0x40000000

/*                                                             
                                        
 */
#define WL_TIMESTAMP_VAL        0x80000000

/*                                                           */
#define	WL_LED_NUMGPIO		32	/*           */

/*                       */
#define	WL_LED_OFF		0		/*            */
#define	WL_LED_ON		1		/*           */
#define	WL_LED_ACTIVITY		2		/*          */
#define	WL_LED_RADIO		3		/*               */
#define	WL_LED_ARADIO		4		/*                      */
#define	WL_LED_BRADIO		5		/*                      */
#define	WL_LED_BGMODE		6		/*                           */
#define	WL_LED_WI1		7
#define	WL_LED_WI2		8
#define	WL_LED_WI3		9
#define	WL_LED_ASSOC		10		/*                            */
#define	WL_LED_INACTIVE		11		/*                                         */
#define	WL_LED_ASSOCACT		12		/*                                             */
#define WL_LED_WI4		13
#define WL_LED_WI5		14
#define	WL_LED_BLINKSLOW	15		/*            */
#define	WL_LED_BLINKMED		16		/*           */
#define	WL_LED_BLINKFAST	17		/*            */
#define	WL_LED_BLINKCUSTOM	18		/*              */
#define	WL_LED_BLINKPERIODIC	19		/*                                            */
#define WL_LED_ASSOC_WITH_SEC	20		/*                              */
						/*                     */
#define WL_LED_START_OFF	21		/*                                         */
#define WL_LED_WI6		22
#define WL_LED_WI7		23
#define WL_LED_WI8		24
#define	WL_LED_NUMBEHAVIOR	25

/*                                   */
#define	WL_LED_BEH_MASK		0x7f		/*               */
#define	WL_LED_AL_MASK		0x80		/*                          */

/*                                                                            */
#define BCMIO_ROUNDUP(x, y)	((((x) + ((y) - 1)) / (y)) * (y))
#define BCMIO_NBBY		8

/*                                                                 */
#define WL_EVENTING_MASK_LEN    ((WLC_E_LAST + 7) / 8)

/*                       */
#define WL_JOIN_PREF_RSSI	1	/*         */
#define WL_JOIN_PREF_WPA	2	/*                    */
#define WL_JOIN_PREF_BAND	3	/*                */
#define WL_JOIN_PREF_RSSI_DELTA	4	/*                                                     */
#define WL_JOIN_PREF_TRANS_PREF	5	/*                          */

/*                 */
#define WLJP_BAND_ASSOC_PREF	255	/*                                               */

/*                            */
#define WL_WPA_ACP_MCS_ANY	"\x00\x00\x00\x00"

/*                           */
#define WLC_MEASURE_TPC			1
#define WLC_MEASURE_CHANNEL_BASIC	2
#define WLC_MEASURE_CHANNEL_CCA		3
#define WLC_MEASURE_CHANNEL_RPI		4

/*                               */
#define SPECT_MNGMT_OFF			0		/*                           */
#define SPECT_MNGMT_LOOSE_11H		1		/*                                 */
#define SPECT_MNGMT_STRICT_11H		2		/*                                      */
#define SPECT_MNGMT_STRICT_11D		3		/*                        */
/*                                                                                       
                                                                
 */
#define SPECT_MNGMT_LOOSE_11H_D		4		/*                         */

#define WL_CHAN_VALID_HW	(1 << 0)	/*                       */
#define WL_CHAN_VALID_SW	(1 << 1)	/*                                    */
#define WL_CHAN_BAND_5G		(1 << 2)	/*                   */
#define WL_CHAN_RADAR		(1 << 3)	/*                          */
#define WL_CHAN_INACTIVE	(1 << 4)	/*                                   */
#define WL_CHAN_PASSIVE		(1 << 5)	/*                            */
#define WL_CHAN_RESTRICTED	(1 << 6)	/*                        */

/*                                   */
#define	WL_BTC_DISABLE		0	/*                        */
#define WL_BTC_FULLTDM      1	/*               */
#define WL_BTC_ENABLE       1	/*                                                 */
#define WL_BTC_PREMPT      2    /*                               */
#define WL_BTC_LITE        3	/*                                                */
#define WL_BTC_PARALLEL		4   /*                                                    */
#define WL_BTC_HYBRID		5   /*                                                         */
#define WL_BTC_DEFAULT		8	/*                                     */
#define WL_INF_BTC_DISABLE      0
#define WL_INF_BTC_ENABLE       1
#define WL_INF_BTC_AUTO         3

/*                                   */
#define	WL_BTC_DEFWIRE		0	/*                          */
#define WL_BTC_2WIRE		2	/*                */
#define WL_BTC_3WIRE		3	/*                */
#define WL_BTC_4WIRE		4	/*                */

/*                                                      */
#define WL_BTC_FLAG_PREMPT               (1 << 0)
#define WL_BTC_FLAG_BT_DEF               (1 << 1)
#define WL_BTC_FLAG_ACTIVE_PROT          (1 << 2)
#define WL_BTC_FLAG_SIM_RSP              (1 << 3)
#define WL_BTC_FLAG_PS_PROTECT           (1 << 4)
#define WL_BTC_FLAG_SIM_TX_LP	         (1 << 5)
#define WL_BTC_FLAG_ECI                  (1 << 6)
#define WL_BTC_FLAG_LIGHT                (1 << 7)
#define WL_BTC_FLAG_PARALLEL             (1 << 8)

/*                                                           */
#define WL_NUMCHANNELS		64

/*                                                                */
#ifdef WL11AC_80P80
#define WL_NUMCHANSPECS 206
#else
#define WL_NUMCHANSPECS 110
#endif


/*                                  */
#define WL_WDS_WPA_ROLE_AUTH	0	/*               */
#define WL_WDS_WPA_ROLE_SUP	1	/*            */
#define WL_WDS_WPA_ROLE_AUTO	255	/*                               */

/*                    */
#define WL_PKT_FILTER_BASE_PKT   0
#define WL_PKT_FILTER_BASE_END   1
#define WL_PKT_FILTER_BASE_D11_H 2 /*                */
#define WL_PKT_FILTER_BASE_D11_D 3 /*                */
#define WL_PKT_FILTER_BASE_ETH_H 4
#define WL_PKT_FILTER_BASE_ETH_D 5
#define WL_PKT_FILTER_BASE_ARP_H 6
#define WL_PKT_FILTER_BASE_ARP_D 7 /*                */
#define WL_PKT_FILTER_BASE_IP4_H 8
#define WL_PKT_FILTER_BASE_IP4_D 9
#define WL_PKT_FILTER_BASE_IP6_H 10
#define WL_PKT_FILTER_BASE_IP6_D 11
#define WL_PKT_FILTER_BASE_TCP_H 12
#define WL_PKT_FILTER_BASE_TCP_D 13 /*                */
#define WL_PKT_FILTER_BASE_UDP_H 14
#define WL_PKT_FILTER_BASE_UDP_D 15
#define WL_PKT_FILTER_BASE_IP6_P 16
#define WL_PKT_FILTER_BASE_COUNT 17 /*                */

/*                                                                    */
#define WL_PKT_FILTER_BASE_NAMES \
	{ "START", WL_PKT_FILTER_BASE_PKT },   \
	{ "END",   WL_PKT_FILTER_BASE_END },   \
	{ "ETH_H", WL_PKT_FILTER_BASE_ETH_H }, \
	{ "ETH_D", WL_PKT_FILTER_BASE_ETH_D }, \
	{ "D11_H", WL_PKT_FILTER_BASE_D11_H }, \
	{ "D11_D", WL_PKT_FILTER_BASE_D11_D }, \
	{ "ARP_H", WL_PKT_FILTER_BASE_ARP_H }, \
	{ "IP4_H", WL_PKT_FILTER_BASE_IP4_H }, \
	{ "IP4_D", WL_PKT_FILTER_BASE_IP4_D }, \
	{ "IP6_H", WL_PKT_FILTER_BASE_IP6_H }, \
	{ "IP6_D", WL_PKT_FILTER_BASE_IP6_D }, \
	{ "IP6_P", WL_PKT_FILTER_BASE_IP6_P }, \
	{ "TCP_H", WL_PKT_FILTER_BASE_TCP_H }, \
	{ "TCP_D", WL_PKT_FILTER_BASE_TCP_D }, \
	{ "UDP_H", WL_PKT_FILTER_BASE_UDP_H }, \
	{ "UDP_D", WL_PKT_FILTER_BASE_UDP_D }

/*                                  */
#define WL_PKT_FILTER_MFLAG_NEG 0x0001

/*
                          
 */

#define WL_PKTENG_PER_TX_START			0x01
#define WL_PKTENG_PER_TX_STOP			0x02
#define WL_PKTENG_PER_RX_START			0x04
#define WL_PKTENG_PER_RX_WITH_ACK_START		0x05
#define WL_PKTENG_PER_TX_WITH_ACK_START		0x06
#define WL_PKTENG_PER_RX_STOP			0x08
#define WL_PKTENG_PER_MASK			0xff

#define WL_PKTENG_SYNCHRONOUS			0x100	/*                  */

#define WL_PKTENG_MAXPKTSZ				16384	/*                            */

#define NUM_80211b_RATES	4
#define NUM_80211ag_RATES	8
#define NUM_80211n_RATES	32
#define NUM_80211_RATES		(NUM_80211b_RATES+NUM_80211ag_RATES+NUM_80211n_RATES)

/*
                                    
 */
#define WL_WOWL_MAGIC           (1 << 0)    /*                        */
#define WL_WOWL_NET             (1 << 1)    /*                      */
#define WL_WOWL_DIS             (1 << 2)    /*                                               */
#define WL_WOWL_RETR            (1 << 3)    /*                          */
#define WL_WOWL_BCN             (1 << 4)    /*                          */
#define WL_WOWL_TST             (1 << 5)    /*                   */
#define WL_WOWL_M1              (1 << 6)    /*                          */
#define WL_WOWL_EAPID           (1 << 7)    /*                                          */
#define WL_WOWL_PME_GPIO        (1 << 8)    /*                               */
#define WL_WOWL_NEEDTKIP1       (1 << 9)    /*                                                   */
#define WL_WOWL_GTK_FAILURE     (1 << 10)   /*                            */
#define WL_WOWL_EXTMAGPAT       (1 << 11)   /*                                */
#define WL_WOWL_ARPOFFLOAD      (1 << 12)   /*                                     */
#define WL_WOWL_WPA2            (1 << 13)   /*                                        */
#define WL_WOWL_KEYROT          (1 << 14)   /*                                    */
#define WL_WOWL_BCAST           (1 << 15)   /*                                                 */
#define WL_WOWL_SCANOL          (1 << 16)   /*                                            */
#define WL_WOWL_TCPKEEP_TIME    (1 << 17)   /*                                 */
#define WL_WOWL_MDNS_CONFLICT   (1 << 18)   /*                                    */
#define WL_WOWL_MDNS_SERVICE    (1 << 19)   /*                                */
#define WL_WOWL_TCPKEEP_DATA    (1 << 20)   /*                        */
#define WL_WOWL_FW_HALT         (1 << 21)   /*                            */
#define WL_WOWL_ENAB_HWRADIO    (1 << 22)   /*                                          */
#define WL_WOWL_MIC_FAIL        (1 << 23)   /*                                  */
#define WL_WOWL_UNASSOC         (1 << 24)   /*                                                  */
#define WL_WOWL_SECURE          (1 << 25)   /*                                            */
#define WL_WOWL_LINKDOWN        (1 << 31)   /*                                   */

#define WL_WOWL_TCPKEEP         (1 << 20)   /*                                 */
#define MAGIC_PKT_MINLEN 102    /*                                                        */

#define WOWL_PATTEN_TYPE_ARP	(1 << 0)	/*                     */
#define WOWL_PATTEN_TYPE_NA	(1 << 1)	/*                    */

#define MAGIC_PKT_MINLEN	102    /*                                                        */
#define MAGIC_PKT_NUM_MAC_ADDRS	16


/*                                                       */
#define WLC_OBSS_SCAN_PASSIVE_DWELL_DEFAULT		20	/*         */
#define WLC_OBSS_SCAN_PASSIVE_DWELL_MIN			5	/*         */
#define WLC_OBSS_SCAN_PASSIVE_DWELL_MAX			1000	/*         */
#define WLC_OBSS_SCAN_ACTIVE_DWELL_DEFAULT		10	/*         */
#define WLC_OBSS_SCAN_ACTIVE_DWELL_MIN			10	/*         */
#define WLC_OBSS_SCAN_ACTIVE_DWELL_MAX			1000	/*         */
#define WLC_OBSS_SCAN_WIDTHSCAN_INTERVAL_DEFAULT	300	/*          */
#define WLC_OBSS_SCAN_WIDTHSCAN_INTERVAL_MIN		10	/*          */
#define WLC_OBSS_SCAN_WIDTHSCAN_INTERVAL_MAX		900	/*          */
#define WLC_OBSS_SCAN_CHANWIDTH_TRANSITION_DLY_DEFAULT	5
#define WLC_OBSS_SCAN_CHANWIDTH_TRANSITION_DLY_MIN	5
#define WLC_OBSS_SCAN_CHANWIDTH_TRANSITION_DLY_MAX	100
#define WLC_OBSS_SCAN_PASSIVE_TOTAL_PER_CHANNEL_DEFAULT	200	/*         */
#define WLC_OBSS_SCAN_PASSIVE_TOTAL_PER_CHANNEL_MIN	200	/*         */
#define WLC_OBSS_SCAN_PASSIVE_TOTAL_PER_CHANNEL_MAX	10000	/*         */
#define WLC_OBSS_SCAN_ACTIVE_TOTAL_PER_CHANNEL_DEFAULT	20	/*         */
#define WLC_OBSS_SCAN_ACTIVE_TOTAL_PER_CHANNEL_MIN	20	/*         */
#define WLC_OBSS_SCAN_ACTIVE_TOTAL_PER_CHANNEL_MAX	10000	/*         */
#define WLC_OBSS_SCAN_ACTIVITY_THRESHOLD_DEFAULT	25	/*              */
#define WLC_OBSS_SCAN_ACTIVITY_THRESHOLD_MIN		0	/*              */
#define WLC_OBSS_SCAN_ACTIVITY_THRESHOLD_MAX		100	/*              */

#define WL_MIN_NUM_OBSS_SCAN_ARG 7	/*                                                    */

#define WL_COEX_INFO_MASK		0x07
#define WL_COEX_INFO_REQ		0x01
#define	WL_COEX_40MHZ_INTOLERANT	0x02
#define	WL_COEX_WIDTH20			0x04

#define	WLC_RSSI_INVALID	 0	/*                    */

#define MAX_RSSI_LEVELS 8

/*                  */
#define EXTLOG_CUR_VER		0x0100

#define MAX_ARGSTR_LEN		18 /*                                                    */

/*                      */
#define LOG_MODULE_COMMON	0x0001
#define LOG_MODULE_ASSOC	0x0002
#define LOG_MODULE_EVENT	0x0004
#define LOG_MODULE_MAX		3			/*                           */

/*            */
#define WL_LOG_LEVEL_DISABLE	0
#define WL_LOG_LEVEL_ERR	1
#define WL_LOG_LEVEL_WARN	2
#define WL_LOG_LEVEL_INFO	3
#define WL_LOG_LEVEL_MAX	WL_LOG_LEVEL_INFO	/*                          */

/*      */
#define LOG_FLAG_EVENT		1

/*              */
#define LOG_ARGTYPE_NULL	0
#define LOG_ARGTYPE_STR		1	/*    */
#define LOG_ARGTYPE_INT		2	/*    */
#define LOG_ARGTYPE_INT_STR	3	/*         */
#define LOG_ARGTYPE_STR_INT	4	/*         */

/*                          */
#define VNDR_IE_BEACON_FLAG	0x1
#define VNDR_IE_PRBRSP_FLAG	0x2
#define VNDR_IE_ASSOCRSP_FLAG	0x4
#define VNDR_IE_AUTHRSP_FLAG	0x8
#define VNDR_IE_PRBREQ_FLAG	0x10
#define VNDR_IE_ASSOCREQ_FLAG	0x20
#define VNDR_IE_IWAPID_FLAG	0x40 /*                                                 */
#define VNDR_IE_CUSTOM_FLAG	0x100 /*                    */

#if defined(WLP2P)
/*                                        */
#define VNDR_IE_GONREQ_FLAG     0x001000
#define VNDR_IE_GONRSP_FLAG     0x002000
#define VNDR_IE_GONCFM_FLAG     0x004000
#define VNDR_IE_INVREQ_FLAG     0x008000
#define VNDR_IE_INVRSP_FLAG     0x010000
#define VNDR_IE_DISREQ_FLAG     0x020000
#define VNDR_IE_DISRSP_FLAG     0x040000
#define VNDR_IE_PRDREQ_FLAG     0x080000
#define VNDR_IE_PRDRSP_FLAG     0x100000

#define VNDR_IE_P2PAF_SHIFT	12
#endif /*       */

/*                                                           */

/*             */
#define CHANIM_DISABLE	0	/*          */
#define CHANIM_DETECT	1	/*                */
#define CHANIM_EXT		2	/*                        */
#define CHANIM_ACT		3	/*                                           */
#define CHANIM_MODE_MAX 4

/*                             */
#define APCS_INIT		0
#define APCS_IOCTL		1
#define APCS_CHANIM		2
#define APCS_CSTIMER		3
#define APCS_BTA		4
#define APCS_TXDLY		5
#define APCS_NONACSD		6
#define APCS_DFS_REENTRY	7
#define APCS_TXFAIL		8
#define APCS_MAX		9

/*                              */
#define CHANIM_ACS_RECORD			10

/*        */
#define CCASTATS_TXDUR  0
#define CCASTATS_INBSS  1
#define CCASTATS_OBSS   2
#define CCASTATS_NOCTG  3
#define CCASTATS_NOPKT  4
#define CCASTATS_DOZE   5
#define CCASTATS_TXOP	6
#define CCASTATS_GDTXDUR        7
#define CCASTATS_BDTXDUR        8
#define CCASTATS_MAX    9

#define WL_CHANIM_COUNT_ALL	0xff
#define WL_CHANIM_COUNT_ONE	0x1

/*              */
#define	AP_TPC_OFF		0
#define	AP_TPC_BSS_PWR		1	/*                   */
#define AP_TPC_AP_PWR		2	/*                  */
#define	AP_TPC_AP_BSS_PWR	3	/*                               */
#define AP_TPC_MAX_LINK_MARGIN	127

/*              */
#define	AP_TPC_OFF		0
#define	AP_TPC_BSS_PWR		1	/*                   */
#define AP_TPC_AP_PWR		2	/*                  */
#define	AP_TPC_AP_BSS_PWR	3	/*                               */
#define AP_TPC_MAX_LINK_MARGIN	127

/*       */
#define WL_P2P_DISC_ST_SCAN	0
#define WL_P2P_DISC_ST_LISTEN	1
#define WL_P2P_DISC_ST_SEARCH	2

/*          */
#define WL_P2P_IF_CLIENT	0
#define WL_P2P_IF_GO		1
#define WL_P2P_IF_DYNBCN_GO	2
#define WL_P2P_IF_DEV		3

/*       */
#define WL_P2P_SCHED_RSVD	0
#define WL_P2P_SCHED_REPEAT	255	/*                                       */

#define WL_P2P_SCHED_FIXED_LEN		3

/*               */
#define WL_P2P_SCHED_TYPE_ABS		0	/*                   */
#define WL_P2P_SCHED_TYPE_REQ_ABS	1	/*                   */

/*                                                                    */
#define WL_P2P_SCHED_ACTION_NONE	0	/*           */
#define WL_P2P_SCHED_ACTION_DOZE	1	/*      */
/*                                             */
#define WL_P2P_SCHED_ACTION_GOOFF	2	/*                                     */
/*                                         */
#define WL_P2P_SCHED_ACTION_RESET	255	/*       */

/*                                         */
#define WL_P2P_SCHED_OPTION_NORMAL	0	/*                                      */
#define WL_P2P_SCHED_OPTION_BCNPCT	1	/*                               */
/*                                             */
#define WL_P2P_SCHED_OPTION_TSFOFS	2	/*                                          
                                                   
       */

/*               */
#define WL_P2P_FEAT_GO_CSA	(1 << 0)	/*                                        */
#define WL_P2P_FEAT_GO_NOLEGACY	(1 << 1)	/*                                           
                 
       */
#define WL_P2P_FEAT_RESTRICT_DEV_RESP (1 << 2)	/*                                            */

/*                           */
/*                                    
                                                                       
                           
 */
#define WL_11N_2x2			1
#define WL_11N_3x3			3
#define WL_11N_4x4			4

/*                                  */
#define WLFEATURE_DISABLE_11N		0x00000001
#define WLFEATURE_DISABLE_11N_STBC_TX	0x00000002
#define WLFEATURE_DISABLE_11N_STBC_RX	0x00000004
#define WLFEATURE_DISABLE_11N_SGI_TX	0x00000008
#define WLFEATURE_DISABLE_11N_SGI_RX	0x00000010
#define WLFEATURE_DISABLE_11N_AMPDU_TX	0x00000020
#define WLFEATURE_DISABLE_11N_AMPDU_RX	0x00000040
#define WLFEATURE_DISABLE_11N_GF	0x00000080

/*                 */
#define PSTA_MODE_DISABLED		0
#define PSTA_MODE_PROXY			1
#define PSTA_MODE_REPEATER		2

/*                    */
#define NAT_OP_ENABLE		1	/*                               */
#define NAT_OP_DISABLE		2	/*                                */
#define NAT_OP_DISABLE_ALL	3	/*                               */

/*           */
#define NAT_STATE_ENABLED	1	/*                */
#define NAT_STATE_DISABLED	2	/*                 */

#define CHANNEL_5G_LOW_START	36	/*                                             */
#define CHANNEL_5G_MID_START	52	/*                                             */
#define CHANNEL_5G_HIGH_START	100	/*                                                */
#define CHANNEL_5G_UPPER_START	149	/*                                                 */

/*               */
#define IPV4_ARP_FILTER		0x0001
#define IPV4_NETBT_FILTER	0x0002
#define IPV4_LLMNR_FILTER	0x0004
#define IPV4_SSDP_FILTER	0x0008
#define IPV4_WSD_FILTER		0x0010
#define IPV6_NETBT_FILTER	0x0200
#define IPV6_LLMNR_FILTER	0x0400
#define IPV6_SSDP_FILTER	0x0800
#define IPV6_WSD_FILTER		0x1000

/*                        */
#define NWOE_OL_ENABLE		0x00000001

/*
                                         
 */

/*                                         */
#define TRF_MGMT_MAX_PRIORITIES                 3

#define TRF_MGMT_FLAG_ADD_DSCP                  0x0001  /*                          */
#define TRF_MGMT_FLAG_DISABLE_SHAPING           0x0002  /*                     */
#define TRF_MGMT_FLAG_MANAGE_LOCAL_TRAFFIC      0x0008  /*                                      */
#define TRF_MGMT_FLAG_FILTER_ON_MACADDR         0x0010  /*                       */
#define TRF_MGMT_FLAG_NO_RX                     0x0020  /*                                   */

#define TRF_FILTER_MAC_ADDR              0x0001 /*                                             */
#define TRF_FILTER_IP_ADDR               0x0002 /*                                       */
#define TRF_FILTER_L4                    0x0004 /*                                     */
#define TRF_FILTER_DWM                   0x0008 /*                                  */
#define TRF_FILTER_FAVORED               0x0010 /*                        */

/*                          */
#define WL_WNM_BSSTRANS		0x00000001
#define WL_WNM_PROXYARP		0x00000002
#define WL_WNM_MAXIDLE		0x00000004
#define WL_WNM_TIMBC		0x00000008
#define WL_WNM_TFS		0x00000010
#define WL_WNM_SLEEP		0x00000020
#define WL_WNM_DMS		0x00000040
#define WL_WNM_FMS		0x00000080
#define WL_WNM_NOTIF		0x00000100
#define WL_WNM_MAX		0x00000200

#ifndef ETHER_MAX_DATA
#define ETHER_MAX_DATA	1500
#endif /*                */

/*                                   */
#define	DPT_DISCOVERY_MANUAL	0x01	/*                       */
#define	DPT_DISCOVERY_AUTO	0x02	/*                     */
#define	DPT_DISCOVERY_SCAN	0x04	/*                           */

/*                                 */
#define DPT_PATHSEL_AUTO	0	/*                              */
#define DPT_PATHSEL_DIRECT	1	/*                            */
#define DPT_PATHSEL_APPATH	2	/*                    */

/*                             */
#define DPT_DENY_LIST_ADD	1	/*                      */
#define DPT_DENY_LIST_REMOVE	2	/*                           */

/*                                    */
#define DPT_MANUAL_EP_CREATE	1	/*                            */
#define DPT_MANUAL_EP_MODIFY	2	/*                            */
#define DPT_MANUAL_EP_DELETE	3	/*                            */

/*                              */
#define	DPT_STATUS_ACTIVE	0x01	/*                                       */
#define	DPT_STATUS_AES		0x02	/*                                     */
#define	DPT_STATUS_FAILED	0x04	/*                 */

#ifdef WLTDLS
/*                                    */
#define TDLS_MANUAL_EP_CREATE	1	/*                            */
#define TDLS_MANUAL_EP_MODIFY	2	/*                            */
#define TDLS_MANUAL_EP_DELETE	3	/*                            */
#define TDLS_MANUAL_EP_PM		4	/*                              */
#define TDLS_MANUAL_EP_WAKE		5	/*                              */
#define TDLS_MANUAL_EP_DISCOVERY	6	/*                                      */
#define TDLS_MANUAL_EP_CHSW		7	/*                */
#define TDLS_MANUAL_EP_WFD_TPQ	8	/*                                     */

/*       */
#define TDLS_WFD_IE_TX			0
#define TDLS_WFD_IE_RX			1
#define TDLS_WFD_PROBE_IE_TX	2
#define TDLS_WFD_PROBE_IE_RX	3
#endif /*        */

/*                 */
#define TSPEC_PENDING		0	/*               */
#define TSPEC_ACCEPTED		1	/*                */
#define TSPEC_REJECTED		2	/*                */
#define TSPEC_UNKNOWN		3	/*               */
#define TSPEC_STATUS_MASK	7	/*                   */

#ifdef BCMCCX
/*                               */
#define WL_WLAN_ASSOC_REASON_NORMAL_NETWORK	0 /*                           */
#define WL_WLAN_ASSOC_REASON_ROAM_FROM_CELLULAR_NETWORK	1 /*                            */
#define WL_WLAN_ASSOC_REASON_ROAM_FROM_LAN	2 /*               */
#define WL_WLAN_ASSOC_REASON_MAX		2 /*                       */
#endif /*        */

/*                                                     */
#ifdef WLAFTERBURNER
#define WL_SWFL_ABBFL       0x0001 /*                                               */
#define WL_SWFL_ABENCORE    0x0002 /*                             */
#endif /*               */
#define WL_SWFL_NOHWRADIO	0x0004
#define WL_SWFL_FLOWCONTROL     0x0008 /*                                 */
#define WL_SWFL_WLBSSSORT	0x0010 /*                                  */

#define WL_LIFETIME_MAX 0xFFFF /*                 */

#define CSA_BROADCAST_ACTION_FRAME	0	/*                            */
#define CSA_UNICAST_ACTION_FRAME	  1 /*                          */

/*                                                      
  
                                                                          
                                                                    
                                      
  
                                                                          
                                  
 */
#define WLC_ROAM_TRIGGER_DEFAULT	0 /*                         */
#define WLC_ROAM_TRIGGER_BANDWIDTH	1 /*                                        */
#define WLC_ROAM_TRIGGER_DISTANCE	2 /*                                       */
#define WLC_ROAM_TRIGGER_AUTO		3 /*                         */
#define WLC_ROAM_TRIGGER_MAX_VALUE	3 /*                  */

#define WLC_ROAM_NEVER_ROAM_TRIGGER	(-100) /*                                        */

/*                                                       */
#define WPA_AUTH_PFN_ANY	0xffffffff	/*                          */

#define SORT_CRITERIA_BIT		0
#define AUTO_NET_SWITCH_BIT		1
#define ENABLE_BKGRD_SCAN_BIT		2
#define IMMEDIATE_SCAN_BIT		3
#define	AUTO_CONNECT_BIT		4
#define	ENABLE_BD_SCAN_BIT		5
#define ENABLE_ADAPTSCAN_BIT		6
#define IMMEDIATE_EVENT_BIT		8
#define SUPPRESS_SSID_BIT		9
#define ENABLE_NET_OFFLOAD_BIT		10
/*                                                                 */
#define REPORT_SEPERATELY_BIT		11
#define BESTN_BSSID_ONLY_BIT		12

#define SORT_CRITERIA_MASK		0x0001
#define AUTO_NET_SWITCH_MASK		0x0002
#define ENABLE_BKGRD_SCAN_MASK		0x0004
#define IMMEDIATE_SCAN_MASK		0x0008
#define	AUTO_CONNECT_MASK		0x0010

#define ENABLE_BD_SCAN_MASK		0x0020
#define ENABLE_ADAPTSCAN_MASK		0x00c0
#define IMMEDIATE_EVENT_MASK		0x0100
#define SUPPRESS_SSID_MASK		0x0200
#define ENABLE_NET_OFFLOAD_MASK		0x0400
/*                                                                 */
#define REPORT_SEPERATELY_MASK		0x0800
#define BESTN_BSSID_ONLY_MASK		0x1000

#define PFN_VERSION			2
#define PFN_SCANRESULT_VERSION		1
#define MAX_PFN_LIST_COUNT		16

#define PFN_COMPLETE			1
#define PFN_INCOMPLETE			0

#define DEFAULT_BESTN			2
#define DEFAULT_MSCAN			0
#define DEFAULT_REPEAT			10
#define DEFAULT_EXP				2

#define PFN_PARTIAL_SCAN_BIT		0
#define PFN_PARTIAL_SCAN_MASK		1

#define WL_PFN_SUPPRESSFOUND_MASK	0x08
#define WL_PFN_SUPPRESSLOST_MASK	0x10
#define WL_PFN_RSSI_MASK		0xff00
#define WL_PFN_RSSI_SHIFT		8

#define WL_PFN_REPORT_ALLNET    0
#define WL_PFN_REPORT_SSIDNET   1
#define WL_PFN_REPORT_BSSIDNET  2

#define WL_PFN_CFG_FLAGS_PROHIBITED	0x00000001	/*                                    */
#define WL_PFN_CFG_FLAGS_HISTORY_OFF	0x00000002	/*                         */

#define WL_PFN_HIDDEN_BIT		2
#define PNO_SCAN_MAX_FW			508*1000	/*                            */
#define PNO_SCAN_MAX_FW_SEC		PNO_SCAN_MAX_FW/1000 /*                           */
#define PNO_SCAN_MIN_FW_SEC		10			/*                           */
#define WL_PFN_HIDDEN_MASK		0x4

#ifndef BESTN_MAX
#define BESTN_MAX			8
#endif

#ifndef MSCAN_MAX
#define MSCAN_MAX			32
#endif

/*                                                  */
#define TOE_ERRTEST_TX_CSUM	0x00000001
#define TOE_ERRTEST_RX_CSUM	0x00000002
#define TOE_ERRTEST_RX_CSUM2	0x00000004

/*                                            */
#define ARP_OL_AGENT		0x00000001
#define ARP_OL_SNOOP		0x00000002
#define ARP_OL_HOST_AUTO_REPLY	0x00000004
#define ARP_OL_PEER_AUTO_REPLY	0x00000008

/*                             */
#define ARP_ERRTEST_REPLY_PEER	0x1
#define ARP_ERRTEST_REPLY_HOST	0x2

#define ARP_MULTIHOMING_MAX	8	/*                                 */
#define ND_MULTIHOMING_MAX 10	/*                                 */
#define ND_REQUEST_MAX		5	/*                           */


/*                      */
#define WAKE_EVENT_NLO_DISCOVERY_BIT		1
#define WAKE_EVENT_AP_ASSOCIATION_LOST_BIT	2
#define WAKE_EVENT_GTK_HANDSHAKE_ERROR_BIT 4
#define WAKE_EVENT_4WAY_HANDSHAKE_REQUEST_BIT 8


#define MAX_NUM_WOL_PATTERN	22 /*                          */


/*                              */
/*                   */
#define PKT_FILTER_MODE_FORWARD_ON_MATCH		1
/*                                          */
#define PKT_FILTER_MODE_DISABLE					2
/*                                                      */
#define PKT_FILTER_MODE_PKT_CACHE_ON_MATCH		4
/*                                                                       */
#define PKT_FILTER_MODE_PKT_FORWARD_OFF_DEFAULT 8

#ifdef DONGLEOVERLAYS
#define OVERLAY_IDX_MASK		0x000000ff
#define OVERLAY_IDX_SHIFT		0
#define OVERLAY_FLAGS_MASK		0xffffff00
#define OVERLAY_FLAGS_SHIFT		8
/*                                                                           */
#define OVERLAY_FLAG_POSTLOAD	0x100
/*                                                                             */
#define OVERLAY_FLAG_DEFER_DL	0x200
/*                                                     */
#define OVERLAY_FLAG_PRESLEEP	0x400
#define OVERLAY_DOWNLOAD_CHUNKSIZE	1024
#endif /*                */

/*                                     */
#define	SMFS_CODE_MALFORMED 0xFFFE
#define SMFS_CODE_IGNORED	0xFFFD

/*             */
#define BCM_ACTION_RFAWARE		0x77
#define BCM_ACTION_RFAWARE_DCS  0x01

/*                        */
#define BCM_DCS_IOVAR		0x1
#define BCM_DCS_UNKNOWN		0xFF


#ifdef PROP_TXSTATUS
/*                               */
/*
                       
                     
 */
#define WLFC_FLAGS_RSSI_SIGNALS			0x0001

/*                                                               
  
                         
                          
  
                               
                                
  
                            
                            
  
 */
#define WLFC_FLAGS_XONXOFF_SIGNALS		0x0002

/*                                                 
                                   
                         
                                
 */
#define WLFC_FLAGS_CREDIT_STATUS_SIGNALS	0x0004

#define WLFC_FLAGS_HOST_PROPTXSTATUS_ACTIVE	0x0008
#define WLFC_FLAGS_PSQ_GENERATIONFSM_ENABLE	0x0010
#define WLFC_FLAGS_PSQ_ZERO_BUFFER_ENABLE	0x0020
#define WLFC_FLAGS_HOST_RXRERODER_ACTIVE	0x0040
#define WLFC_FLAGS_PKT_STAMP_SIGNALS		0x0080

#endif /*               */

#define WL_TIMBC_STATUS_AP_UNKNOWN	255	/*                                 */

#define WL_DFRTS_LOGIC_OFF	0	/*                     */
#define WL_DFRTS_LOGIC_OR	1	/*                                      */
#define WL_DFRTS_LOGIC_AND	2	/*                                       */

/*                                    */
#define WL_RELMCAST_MAX_CLIENT		32
#define WL_RELMCAST_FLAG_INBLACKLIST	1
#define WL_RELMCAST_FLAG_ACTIVEACKER	2
#define WL_RELMCAST_FLAG_RELMCAST	4

/*                                                */
#define WL_PROXD_MODE_DISABLE	0
#define WL_PROXD_MODE_NEUTRAL	1
#define WL_PROXD_MODE_INITIATOR	2
#define WL_PROXD_MODE_TARGET	3
#define WL_PROXD_RANDOM_WAKEUP	0x8000


#ifdef NET_DETECT
#define NET_DETECT_MAX_WAKE_DATA_SIZE	2048
#define NET_DETECT_MAX_PROFILES		16
#define NET_DETECT_MAX_CHANNELS		50
#endif /*            */

/*                                                                */
#define WL_RADIO_SW_DISABLE		(1<<0)
#define WL_RADIO_HW_DISABLE		(1<<1)
#define WL_RADIO_MPC_DISABLE		(1<<2)
#define WL_RADIO_COUNTRY_DISABLE	(1<<3)	/*                                          */

#define	WL_SPURAVOID_OFF	0
#define	WL_SPURAVOID_ON1	1
#define	WL_SPURAVOID_ON2	2


#define WL_4335_SPURAVOID_ON1	1
#define WL_4335_SPURAVOID_ON2	2
#define WL_4335_SPURAVOID_ON3	3
#define WL_4335_SPURAVOID_ON4	4
#define WL_4335_SPURAVOID_ON5	5
#define WL_4335_SPURAVOID_ON6	6
#define WL_4335_SPURAVOID_ON7	7
#define WL_4335_SPURAVOID_ON8	8
#define WL_4335_SPURAVOID_ON9	9

/*                                                                    */
#define WL_TXPWR_OVERRIDE	(1U<<31)
#define WL_TXPWR_NEG   (1U<<30)


/*                                        */
#define	WLC_PHY_TYPE_A		0
#define	WLC_PHY_TYPE_B		1
#define	WLC_PHY_TYPE_G		2
#define	WLC_PHY_TYPE_N		4
#define	WLC_PHY_TYPE_LP		5
#define	WLC_PHY_TYPE_SSN	6
#define	WLC_PHY_TYPE_HT		7
#define	WLC_PHY_TYPE_LCN	8
#define	WLC_PHY_TYPE_LCN40	10
#define WLC_PHY_TYPE_AC		11
#define	WLC_PHY_TYPE_NULL	0xf

/*               */
#define PM_OFF	0
#define PM_MAX	1
#define PM_FAST 2
#define PM_FORCE_OFF 3		/*                                                */

#define WL_WME_CNT_VERSION	1	/*                                 */

/*                                     */
#define WLC_FBT_CAP_DRV_4WAY_AND_REASSOC  1 /*                                           */

/*                            */
#define WL_MONPROMISC_PROMISC 0x0001
#define WL_MONPROMISC_CTRL 0x0002
#define WL_MONPROMISC_FCS 0x0004

/*                              */
#define TOE_TX_CSUM_OL		0x00000001
#define TOE_RX_CSUM_OL		0x00000002

/*                               */
#define WL_P2P_SOCIAL_CHANNELS_MAX  WL_NUMCHANNELS
#define MAX_WFDS_SEEK_SVC 4	/*                                */
#define MAX_WFDS_ADVERT_SVC 4	/*                                     */
#define MAX_WFDS_SVC_NAME_LEN 200	/*                             */
#define MAX_WFDS_ADV_SVC_INFO_LEN 65000	/*                                 */
#define P2P_WFDS_HASH_LEN 6		/*                               */
#define MAX_WFDS_SEEK_SVC_INFO_LEN 255	/*                                      */
#define MAX_WFDS_SEEK_SVC_NAME_LEN 200	/*                             */

/*                    */
#define AP_ISOLATE_DISABLED		0x0
#define AP_ISOLATE_SENDUP_ALL		0x01
#define AP_ISOLATE_SENDUP_MCAST		0x02

#endif /*                */
