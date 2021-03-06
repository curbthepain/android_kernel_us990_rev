/*
 * Copyright (c) 2006, 2007, 2008 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _IPATH_COMMON_H
#define _IPATH_COMMON_H

/*
                                                             
                                               
 */


/*                                                          */
#define IPATH_SRC_OUI_1 0x00
#define IPATH_SRC_OUI_2 0x11
#define IPATH_SRC_OUI_3 0x75

/*                                                                  
                                                                       
                                                    
 */
#define IPS_PROTO_VERSION 2

/*
                                                                          
                                                                
                                                                      
                
                                                                      
                         
                                                                    
                   
                                                                  
 */

/*
                                                                      
                                                            
 */
#define IPATH_KD_QP 0x656b79

/*
                                                         
 */
#define IPATH_IB_LINKDOWN		0
#define IPATH_IB_LINKARM		1
#define IPATH_IB_LINKACTIVE		2
#define IPATH_IB_LINKDOWN_ONLY		3
#define IPATH_IB_LINKDOWN_SLEEP		4
#define IPATH_IB_LINKDOWN_DISABLE	5
#define IPATH_IB_LINK_LOOPBACK	6 /*                       */
#define IPATH_IB_LINK_EXTERNAL	7 /*                                */
#define IPATH_IB_LINK_NO_HRTBT	8 /*                                      */
#define IPATH_IB_LINK_HRTBT	9 /*                                        */

/*
                                                         
                                                                  
                                                                     
                                                                           
                                                                  
 */
#define IPATH_IB_SDR 1
#define IPATH_IB_DDR 2

/*
                                                                     
                        
 */
struct infinipath_stats {
	/*                            */
	__u64 sps_ints;
	/*                                 */
	__u64 sps_errints;
	/*                                                             */
	__u64 sps_errs;
	/*                                                  */
	__u64 sps_pkterrs;
	/*                                                   */
	__u64 sps_crcerrs;
	/*                                                   */
	__u64 sps_hwerrs;
	/*                                                    */
	__u64 sps_iblink;
	__u64 sps_unused; /*                                       */
	/*                                           */
	__u64 sps_port0pkts;
	/*                                             */
	__u64 sps_ether_spkts;
	/*                                                 */
	__u64 sps_ether_rpkts;
	/*                                                 */
	__u64 sps_sma_spkts;
	/*                                                     */
	__u64 sps_sma_rpkts;
	/*                                                               */
	__u64 sps_hdrqfull;
	/*                                                              */
	__u64 sps_etidfull;
	/*
                                                                    
         
  */
	__u64 sps_nopiobufs;
	/*                                */
	__u64 sps_ports;
	/*                                                               */
	__u16 sps_pkeys[4];
	__u16 sps_unused16[4]; /*                                          */
	/*                                              */
	__u32 sps_nports;
	/*                                       */
	__u32 sps_nullintr;
	/*                                                */
	__u32 sps_maxpkts_call;
	/*                                                */
	__u32 sps_avgpkts_call;
	/*                              */
	__u64 sps_pagelocks;
	/*                                */
	__u64 sps_pageunlocks;
	/*
                                                                
                                          
  */
	__u64 sps_krdrops;
	__u64 sps_txeparity; /*                                    */
	/*                       */
	__u64 __sps_pad[45];
};

/*
                                                                  
                                
 */
#define IPATH_STATUS_INITTED       0x1	/*                           */
#define IPATH_STATUS_DISABLED      0x2	/*                   */
/*                                            */
#define IPATH_STATUS_ADMIN_DISABLED    0x4
/*                                 */
#define IPATH_STATUS_CHIP_PRESENT 0x20
/*                                               */
#define IPATH_STATUS_IB_READY     0x40
/*                                                  */
#define IPATH_STATUS_IB_CONF      0x80
/*                                        */
#define IPATH_STATUS_IB_NOCABLE  0x100
/*                                      */
#define IPATH_STATUS_HWERROR     0x200

/*
                                                                            
 */
typedef enum _ipath_ureg {
	/*                                   */
	ur_rcvhdrtail = 0,
	/*                                                  */
	ur_rcvhdrhead = 1,
	/*                                         */
	ur_rcvegrindextail = 2,
	/*                                      */
	ur_rcvegrindexhead = 3,
	/*                                             */
	_IPATH_UregMax
} ipath_ureg;

/*                                  */
#define IPATH_RUNTIME_HT	0x1
#define IPATH_RUNTIME_PCIE	0x2
#define IPATH_RUNTIME_FORCE_WC_ORDER	0x4
#define IPATH_RUNTIME_RCVHDR_COPY	0x8
#define IPATH_RUNTIME_MASTER	0x10
#define IPATH_RUNTIME_NODMA_RTAIL 0x80
#define IPATH_RUNTIME_SDMA	      0x200
#define IPATH_RUNTIME_FORCE_PIOAVAIL 0x400
#define IPATH_RUNTIME_PIO_REGSWAPPED 0x800

/*
                                                                   
                                                                      
            
  
                                                            
                                                           
                                                                 
                           
 */
struct ipath_base_info {
	/*                                            */
	__u32 spi_hw_version;
	/*                                            */
	__u32 spi_sw_version;
	/*                                                  */
	__u16 spi_port;
	__u16 spi_subport;
	/*
                                                   
                                                           
  */
	__u32 spi_mtu;
	/*
                                                                     
                                                                    
                                                                 
  */
	__u32 spi_piosize;
	/*                                                 */
	__u32 spi_tidcnt;
	/*                                                      */
	__u32 spi_tidegrcnt;
	/*                                                       */
	__u32 spi_rcvhdrent_size;
	/*
                                                    
                                                       
  */
	__u32 spi_rcvhdr_cnt;

	/*                                                              */
	__u32 spi_runtime_flags;

	/*                                                   */
	__u64 spi_rcvhdr_base;

	/*               */

	/*                                            */
	__u64 spi_rcv_egrbufs;

	/*                                                    */

	/*
                                                       
                                                           
  */
	__u32 spi_rcv_egrbufsize;
	/*
                                                                   
                                                                  
                      
  */
	__u32 spi_qpair;

	/*
                                                                
                             
  */
	__u64 __spi_uregbase;
	/*
                                                                 
                                                                     
                                                                    
                       
  */
	__u32 spi_tid_maxsize;
	/*
                                                 
                                                     
  */
	__u32 spi_pioalign;
	/*
                                                                
                                                         
                   
  */
	__u32 spi_pioindex;
	 /*                                           */
	__u32 spi_piocnt;

	/*
                                                           
                                                                     
                                                                
  */
	__u64 spi_piobufbase;

	/*
                                                                   
                                     
  */
	__u64 spi_pioavailaddr;

	/*
                                                                   
                                                                  
                                                       
  */
	__u64 spi_status;

	/*                                                  */
	__u32 spi_nports;
	/*                                  */
	__u32 spi_unit;
	/*                                 */
	__u32 spi_rcv_egrperchunk;
	/*                                      */
	__u32 spi_rcv_egrchunksize;
	/*                                                */
	__u32 spi_rcv_egrbuftotlen;
	__u32 spi_filler_for_align;
	/*                                                               */
	__u64 spi_rcvhdr_tailaddr;

	/*                                                    */
	__u64 spi_subport_uregbase;
	__u64 spi_subport_rcvegrbuf;
	__u64 spi_subport_rcvhdr_base;

	/*                                                      */
	__u64 spi_port_uregbase;
	__u64 spi_port_rcvegrbuf;
	__u64 spi_port_rcvhdr_base;
	__u64 spi_port_rcvhdr_tailaddr;

} __attribute__ ((aligned(8)));


/*
                                                                     
                                                                     
                                                         
  
                                                 
                                                                        
                                                                  
                                                                       
                        
 */
#define IPATH_USER_SWMAJOR 1

/*
                                                  
                                                               
                                                                  
                                                                  
                                                                       
 */
#define IPATH_USER_SWMINOR 6

#define IPATH_USER_SWVERSION ((IPATH_USER_SWMAJOR<<16) | IPATH_USER_SWMINOR)

#define IPATH_KERN_TYPE 0

/*
                                                                      
                                                                         
                                                                     
                                                               
                                                                    
  
                                                                            
                                                                        
                                           
*/
#define IPATH_KERN_SWVERSION ((IPATH_KERN_TYPE<<31) | IPATH_USER_SWVERSION)

/*
                                                                        
                                                                    
                                                                  
                                                                          
 */
struct ipath_user_info {
	/*
                                                             
                                          
  */
	__u32 spu_userversion;

	/*                                                */
	__u32 spu_rcvhdrcnt;

	/*                                      */
	__u32 spu_base_info_size;

	/*
                                         
                                                                   
                                                                     
                                                   
  */
	__u32 spu_rcvhdrsize;

	/*
                                                               
                                                               
                                                               
                                  
  */
	__u16 spu_subport_cnt;
	__u16 spu_subport_id;

	__u32 spu_unused; /*                            */

	/*
                                           
  */
	__u64 spu_base_info;

} __attribute__ ((aligned(8)));

/*                */

#define IPATH_CMD_MIN		16

#define __IPATH_CMD_USER_INIT	16	/*                                          */
#define IPATH_CMD_PORT_INFO	17	/*                                */
#define IPATH_CMD_RECV_CTRL	18	/*                            */
#define IPATH_CMD_TID_UPDATE	19	/*                             */
#define IPATH_CMD_TID_FREE	20	/*                           */
#define IPATH_CMD_SET_PART_KEY	21	/*                   */
#define __IPATH_CMD_SLAVE_INFO	22	/*                                                    */
#define IPATH_CMD_ASSIGN_PORT	23	/*                       */
#define IPATH_CMD_USER_INIT 	24	/*                  */
#define IPATH_CMD_UNUSED_1	25
#define IPATH_CMD_UNUSED_2	26
#define IPATH_CMD_PIOAVAILUPD	27	/*                                 */
#define IPATH_CMD_POLL_TYPE	28	/*                                 */
#define IPATH_CMD_ARMLAUNCH_CTRL	29 /*                             */
/*              */
#define IPATH_CMD_SDMA_INFLIGHT 31	/*                               */
#define IPATH_CMD_SDMA_COMPLETE 32	/*                                 */

/*
             
 */
#define IPATH_POLL_TYPE_URGENT	 0x01
#define IPATH_POLL_TYPE_OVERFLOW 0x02

struct ipath_port_info {
	__u32 num_active;	/*                        */
	__u32 unit;		/*                                */
	__u16 port;		/*                                 */
	__u16 subport;		/*                                    */
	__u16 num_ports;	/*                                   */
	__u16 num_subports;	/*                                   */
};

struct ipath_tid_info {
	__u32 tidcnt;
	/*                                           */
	__u32 tid__unused;
	/*                                           */
	__u64 tidvaddr;
	/*                                                  */
	__u64 tidlist;

	/*
                                                        
                                                         
  */
	__u64 tidmap;
};

struct ipath_cmd {
	__u32 type;			/*              */
	union {
		struct ipath_tid_info tid_info;
		struct ipath_user_info user_info;

		/*
                                                      
                     
   */
		__u64 sdma_inflight;
		/*
                                                      
                       
   */
		__u64 sdma_complete;
		/*                                                  
                     */
		__u64 port_info;
		/*                                   */
		__u32 recv_ctrl;
		/*                                                      */
		__u32 armlaunch_ctrl;
		/*                      */
		__u16 part_key;
		/*                                                */
		__u64 slave_mask_addr;
		/*                         */
		__u16 poll_type;
	} cmd;
};

struct ipath_iovec {
	/*                                              */
	__u64 iov_base;

	/*
                                                
                                                                     
  */
	__u64 iov_len;
};

/*
                                                                        
                                                                       
                                                                   
                                                                           
                                               
 */
struct __ipath_sendpkt {
	__u32 sps_flags;	/*                        */
	__u32 sps_cnt;		/*                                     */
	/*                                             */
	struct ipath_iovec sps_iov[4];
};

/*
                                                                  
                                        
                                                             
 */
struct ipath_diag_pkt {
	__u32 unit;
	__u64 data;
	__u32 len;
};

/*                                                               
                                                                   
                                                                  
                                                                 
                                                    
 */
struct ipath_diag_xpkt {
	__u64 data;
	__u64 pbc_wd;
	__u32 unit;
	__u32 len;
};

/*
                                            
                                                              
 */
#define IPATH_FLASH_VERSION 2
struct ipath_flash {
	/*                                            */
	__u8 if_fversion;
	/*                                     */
	__u8 if_csum;
	/*
                                                          
                                       
  */
	__u8 if_length;
	/*                            */
	__u8 if_guid[8];
	/*                                               */
	__u8 if_numguid;
	/*                                                           */
	char if_serial[12];
	/*                                 */
	char if_mfgdate[8];
	/*                                              */
	char if_testdate[8];
	/*                              */
	__u8 if_errcntp[4];
	/*                                            */
	__u8 if_powerhour[2];
	/*                               */
	char if_comment[32];
	/*                                                              */
	char if_sprefix[4];
	/*                                            */
	__u8 if_future[46];
};

/*
                                                                           
                                                             
 */
struct infinipath_counters {
	__u64 LBIntCnt;
	__u64 LBFlowStallCnt;
	__u64 TxSDmaDescCnt;	/*               */
	__u64 TxUnsupVLErrCnt;
	__u64 TxDataPktCnt;
	__u64 TxFlowPktCnt;
	__u64 TxDwordCnt;
	__u64 TxLenErrCnt;
	__u64 TxMaxMinLenErrCnt;
	__u64 TxUnderrunCnt;
	__u64 TxFlowStallCnt;
	__u64 TxDroppedPktCnt;
	__u64 RxDroppedPktCnt;
	__u64 RxDataPktCnt;
	__u64 RxFlowPktCnt;
	__u64 RxDwordCnt;
	__u64 RxLenErrCnt;
	__u64 RxMaxMinLenErrCnt;
	__u64 RxICRCErrCnt;
	__u64 RxVCRCErrCnt;
	__u64 RxFlowCtrlErrCnt;
	__u64 RxBadFormatCnt;
	__u64 RxLinkProblemCnt;
	__u64 RxEBPCnt;
	__u64 RxLPCRCErrCnt;
	__u64 RxBufOvflCnt;
	__u64 RxTIDFullErrCnt;
	__u64 RxTIDValidErrCnt;
	__u64 RxPKeyMismatchCnt;
	__u64 RxP0HdrEgrOvflCnt;
	__u64 RxP1HdrEgrOvflCnt;
	__u64 RxP2HdrEgrOvflCnt;
	__u64 RxP3HdrEgrOvflCnt;
	__u64 RxP4HdrEgrOvflCnt;
	__u64 RxP5HdrEgrOvflCnt;
	__u64 RxP6HdrEgrOvflCnt;
	__u64 RxP7HdrEgrOvflCnt;
	__u64 RxP8HdrEgrOvflCnt;
	__u64 RxP9HdrEgrOvflCnt;	/*               */
	__u64 RxP10HdrEgrOvflCnt;	/*               */
	__u64 RxP11HdrEgrOvflCnt;	/*                 */
	__u64 RxP12HdrEgrOvflCnt;	/*                 */
	__u64 RxP13HdrEgrOvflCnt;	/*                 */
	__u64 RxP14HdrEgrOvflCnt;	/*                 */
	__u64 RxP15HdrEgrOvflCnt;	/*                 */
	__u64 RxP16HdrEgrOvflCnt;	/*                 */
	__u64 IBStatusChangeCnt;
	__u64 IBLinkErrRecoveryCnt;
	__u64 IBLinkDownedCnt;
	__u64 IBSymbolErrCnt;
	/*                                   */
	__u64 RxVL15DroppedPktCnt;
	__u64 RxOtherLocalPhyErrCnt;
	__u64 PcieRetryBufDiagQwordCnt;
	__u64 ExcessBufferOvflCnt;
	__u64 LocalLinkIntegrityErrCnt;
	__u64 RxVlErrCnt;
	__u64 RxDlidFltrCnt;
};

/*
                                                                    
                                                                        
                                                                  
                    
 */

/*                  */
#define INFINIPATH_RHF_LENGTH_MASK 0x7FF
#define INFINIPATH_RHF_LENGTH_SHIFT 0
#define INFINIPATH_RHF_RCVTYPE_MASK 0x7
#define INFINIPATH_RHF_RCVTYPE_SHIFT 11
#define INFINIPATH_RHF_EGRINDEX_MASK 0xFFF
#define INFINIPATH_RHF_EGRINDEX_SHIFT 16
#define INFINIPATH_RHF_SEQ_MASK 0xF
#define INFINIPATH_RHF_SEQ_SHIFT 0
#define INFINIPATH_RHF_HDRQ_OFFSET_MASK 0x7FF
#define INFINIPATH_RHF_HDRQ_OFFSET_SHIFT 4
#define INFINIPATH_RHF_H_ICRCERR   0x80000000
#define INFINIPATH_RHF_H_VCRCERR   0x40000000
#define INFINIPATH_RHF_H_PARITYERR 0x20000000
#define INFINIPATH_RHF_H_LENERR    0x10000000
#define INFINIPATH_RHF_H_MTUERR    0x08000000
#define INFINIPATH_RHF_H_IHDRERR   0x04000000
#define INFINIPATH_RHF_H_TIDERR    0x02000000
#define INFINIPATH_RHF_H_MKERR     0x01000000
#define INFINIPATH_RHF_H_IBERR     0x00800000
#define INFINIPATH_RHF_H_ERR_MASK  0xFF800000
#define INFINIPATH_RHF_L_USE_EGR   0x80000000
#define INFINIPATH_RHF_L_SWA       0x00008000
#define INFINIPATH_RHF_L_SWB       0x00004000

/*                          */
#define INFINIPATH_I_VERS_MASK 0xF
#define INFINIPATH_I_VERS_SHIFT 28
#define INFINIPATH_I_PORT_MASK 0xF
#define INFINIPATH_I_PORT_SHIFT 24
#define INFINIPATH_I_TID_MASK 0x7FF
#define INFINIPATH_I_TID_SHIFT 13
#define INFINIPATH_I_OFFSET_MASK 0x1FFF
#define INFINIPATH_I_OFFSET_SHIFT 0

/*                 */
#define INFINIPATH_KPF_INTR 0x1
#define INFINIPATH_KPF_SUBPORT_MASK 0x3
#define INFINIPATH_KPF_SUBPORT_SHIFT 1

#define INFINIPATH_MAX_SUBPORT	4

/*                            */
#define INFINIPATH_SP_TEST    0x40
#define INFINIPATH_SP_TESTEBP 0x20
#define INFINIPATH_SP_TRIGGER_SHIFT  15

/*                   */
#define INFINIPATH_SENDPIOAVAIL_BUSY_SHIFT 1
#define INFINIPATH_SENDPIOAVAIL_CHECK_SHIFT 0

/*                          */
struct ipath_header {
	/*
                                                               
                                                              
                              
  */
	__le32 ver_port_tid_offset;
	__le16 chksum;
	__le16 pkt_flags;
};

/*                                       
                                                                     
                          
 */
struct ipath_message_header {
	__be16 lrh[4];
	__be32 bth[3];
	/*                                                */
	struct ipath_header iph;
	__u8 sub_opcode;
};

/*                                   */
struct ether_header {
	__be16 lrh[4];
	__be32 bth[3];
	struct ipath_header iph;
	__u8 sub_opcode;
	__u8 cmd;
	__be16 lid;
	__u16 mac[3];
	__u8 frag_num;
	__u8 seq_num;
	__le32 len;
	/*                                                    */
	__le32 csum;
	__le16 csum_offset;
	__le16 flags;
	__u16 first_2_bytes;
	__u8 unused[2];		/*                  */
};


/*                        */
#define IPATH_LRH_GRH 0x0003	/*                                      */
#define IPATH_LRH_BTH 0x0002	/*                                      */

/*       */
#define SIZE_OF_CRC 1

#define IPATH_DEFAULT_P_KEY 0xFFFF
#define IPATH_PERMISSIVE_LID 0xFFFF
#define IPATH_AETH_CREDIT_SHIFT 24
#define IPATH_AETH_CREDIT_MASK 0x1F
#define IPATH_AETH_CREDIT_INVAL 0x1F
#define IPATH_PSN_MASK 0xFFFFFF
#define IPATH_MSN_MASK 0xFFFFFF
#define IPATH_QPN_MASK 0xFFFFFF
#define IPATH_MULTICAST_LID_BASE 0xC000
#define IPATH_EAGER_TID_ID INFINIPATH_I_TID_MASK
#define IPATH_MULTICAST_QPN 0xFFFFFF

/*                                                      */
#define RCVHQ_RCV_TYPE_EXPECTED  0
#define RCVHQ_RCV_TYPE_EAGER     1
#define RCVHQ_RCV_TYPE_NON_KD    2
#define RCVHQ_RCV_TYPE_ERROR     3


/*                      */
#define IPATH_ITH4X_OPCODE_ENCAP 0x81
#define IPATH_ITH4X_OPCODE_LID_ARP 0x82

#define IPATH_HEADER_QUEUE_WORDS 9

/*                                                                     
 */
static inline __u32 ipath_hdrget_err_flags(const __le32 * rbuf)
{
	return __le32_to_cpu(rbuf[1]) & INFINIPATH_RHF_H_ERR_MASK;
}

static inline __u32 ipath_hdrget_rcv_type(const __le32 * rbuf)
{
	return (__le32_to_cpu(rbuf[0]) >> INFINIPATH_RHF_RCVTYPE_SHIFT)
	    & INFINIPATH_RHF_RCVTYPE_MASK;
}

static inline __u32 ipath_hdrget_length_in_bytes(const __le32 * rbuf)
{
	return ((__le32_to_cpu(rbuf[0]) >> INFINIPATH_RHF_LENGTH_SHIFT)
		& INFINIPATH_RHF_LENGTH_MASK) << 2;
}

static inline __u32 ipath_hdrget_index(const __le32 * rbuf)
{
	return (__le32_to_cpu(rbuf[0]) >> INFINIPATH_RHF_EGRINDEX_SHIFT)
	    & INFINIPATH_RHF_EGRINDEX_MASK;
}

static inline __u32 ipath_hdrget_seq(const __le32 *rbuf)
{
	return (__le32_to_cpu(rbuf[1]) >> INFINIPATH_RHF_SEQ_SHIFT)
		& INFINIPATH_RHF_SEQ_MASK;
}

static inline __u32 ipath_hdrget_offset(const __le32 *rbuf)
{
	return (__le32_to_cpu(rbuf[1]) >> INFINIPATH_RHF_HDRQ_OFFSET_SHIFT)
		& INFINIPATH_RHF_HDRQ_OFFSET_MASK;
}

static inline __u32 ipath_hdrget_use_egr_buf(const __le32 *rbuf)
{
	return __le32_to_cpu(rbuf[0]) & INFINIPATH_RHF_L_USE_EGR;
}

static inline __u32 ipath_hdrget_ipath_ver(__le32 hdrword)
{
	return (__le32_to_cpu(hdrword) >> INFINIPATH_I_VERS_SHIFT)
	    & INFINIPATH_I_VERS_MASK;
}

#endif				/*                 */
