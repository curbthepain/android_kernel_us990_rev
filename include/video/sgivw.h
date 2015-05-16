/*
 *  linux/drivers/video/sgivw.h -- SGI DBE frame buffer device header
 *
 *      Copyright (C) 1999 Silicon Graphics, Inc.
 *      Jeffrey Newquist, newquist@engr.sgi.som
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the main directory of this archive for
 *  more details.
 */

#ifndef __SGIVWFB_H__
#define __SGIVWFB_H__

#define DBE_GETREG(reg, dest)		((dest) = DBE_REG_BASE->reg)
#define DBE_SETREG(reg, src)		DBE_REG_BASE->reg = (src)
#define DBE_IGETREG(reg, idx, dest)	((dest) = DBE_REG_BASE->reg[idx])
#define DBE_ISETREG(reg, idx, src)	(DBE_REG_BASE->reg[idx] = (src))

#define MASK(msb, lsb)          ( (((u32)1<<((msb)-(lsb)+1))-1) << (lsb) )
#define GET(v, msb, lsb)        ( ((u32)(v) & MASK(msb,lsb)) >> (lsb) )
#define SET(v, f, msb, lsb)     ( (v) = ((v)&~MASK(msb,lsb)) | (( (u32)(f)<<(lsb) ) & MASK(msb,lsb)) )

#define GET_DBE_FIELD(reg, field, v)        GET((v), DBE_##reg##_##field##_MSB, DBE_##reg##_##field##_LSB)
#define SET_DBE_FIELD(reg, field, v, f)     SET((v), (f), DBE_##reg##_##field##_MSB, DBE_##reg##_##field##_LSB)

/*                                                     */

#define DBE_REG_PHYS	0xd0000000
#define DBE_REG_SIZE        0x01000000

struct asregs {
  volatile u32 ctrlstat;     /*                          */
  volatile u32 dotclock;     /*                                */
  volatile u32 i2c;          /*                          */
  volatile u32 sysclk;       /*                                   */
  volatile u32 i2cfp;        /*                                 */
  volatile u32 id;           /*                                  */
  volatile u32 config;       /*                                 */
  volatile u32 bist;         /*                               */

  char _pad0[ 0x010000 - 0x000020 ];

  volatile u32 vt_xy;        /*                             */
  volatile u32 vt_xymax;     /*                             */
  volatile u32 vt_vsync;     /*                       */
  volatile u32 vt_hsync;     /*                       */
  volatile u32 vt_vblank;    /*                        */
  volatile u32 vt_hblank;    /*                        */
  volatile u32 vt_flags;     /*                                 */
  volatile u32 vt_f2rf_lock; /*                                  */
  volatile u32 vt_intr01;    /*                            */
  volatile u32 vt_intr23;    /*                            */
  volatile u32 fp_hdrv;      /*                                 */
  volatile u32 fp_vdrv;      /*                                 */
  volatile u32 fp_de;        /*                               */
  volatile u32 vt_hpixen;    /*                                   */
  volatile u32 vt_vpixen;    /*                                   */
  volatile u32 vt_hcmap;     /*                             */
  volatile u32 vt_vcmap;     /*                            */
  volatile u32 did_start_xy; /*                                 */
  volatile u32 crs_start_xy; /*                                 */
  volatile u32 vc_start_xy;  /*                                */

  char _pad1[ 0x020000 - 0x010050 ];

  volatile u32 ovr_width_tile; /*                               */
  volatile u32 ovr_inhwctrl;   /*                               */
  volatile u32 ovr_control;    /*                               */

  char _pad2[ 0x030000 - 0x02000C ];

  volatile u32 frm_size_tile;  /*                              */
  volatile u32 frm_size_pixel; /*                              */
  volatile u32 frm_inhwctrl;   /*                              */
  volatile u32 frm_control;	   /*                              */

  char _pad3[ 0x040000 - 0x030010 ];

  volatile u32 did_inhwctrl;   /*                      */
  volatile u32 did_control;    /*                     */

  char _pad4[ 0x048000 - 0x040008 ];

  volatile u32 mode_regs[32];  /*                               */

  char _pad5[ 0x050000 - 0x048080 ];

  volatile u32 cmap[6144];     /*                               */

  char _pad6[ 0x058000 - 0x056000 ];

  volatile u32 cm_fifo;        /*                                */

  char _pad7[ 0x060000 - 0x058004 ];

  volatile u32 gmap[256];      /*                               */

  char _pad8[ 0x068000 - 0x060400 ];

  volatile u32 gmap10[1024];   /*                               */

  char _pad9[ 0x070000 - 0x069000 ];

  volatile u32 crs_pos;        /*                           */
  volatile u32 crs_ctl;        /*                           */
  volatile u32 crs_cmap[3];    /*                              */

  char _pad10[ 0x078000 - 0x070014 ];

  volatile u32 crs_glyph[64];  /*                               */

  char _pad11[ 0x080000 - 0x078100 ];

  volatile u32 vc_0;           /*                               */
  volatile u32 vc_1;           /*                               */
  volatile u32 vc_2;           /*                               */
  volatile u32 vc_3;           /*                               */
  volatile u32 vc_4;           /*                               */
  volatile u32 vc_5;           /*                               */
  volatile u32 vc_6;           /*                               */
  volatile u32 vc_7;           /*                               */
  volatile u32 vc_8;           /*                               */
};

/*                      */

#define DBE_CTRLSTAT_CHIPID_MSB     3
#define DBE_CTRLSTAT_CHIPID_LSB     0
#define DBE_CTRLSTAT_SENSE_N_MSB    4
#define DBE_CTRLSTAT_SENSE_N_LSB    4
#define DBE_CTRLSTAT_PCLKSEL_MSB    29
#define DBE_CTRLSTAT_PCLKSEL_LSB    28

#define DBE_DOTCLK_M_MSB            7
#define DBE_DOTCLK_M_LSB            0
#define DBE_DOTCLK_N_MSB            13
#define DBE_DOTCLK_N_LSB            8
#define DBE_DOTCLK_P_MSB            15
#define DBE_DOTCLK_P_LSB            14
#define DBE_DOTCLK_RUN_MSB          20
#define DBE_DOTCLK_RUN_LSB          20

#define DBE_VT_XY_VT_FREEZE_MSB     31
#define DBE_VT_XY_VT_FREEZE_LSB     31

#define DBE_FP_VDRV_FP_VDRV_ON_MSB	23
#define DBE_FP_VDRV_FP_VDRV_ON_LSB	12
#define DBE_FP_VDRV_FP_VDRV_OFF_MSB	11
#define DBE_FP_VDRV_FP_VDRV_OFF_LSB	0

#define DBE_FP_HDRV_FP_HDRV_ON_MSB	23
#define DBE_FP_HDRV_FP_HDRV_ON_LSB	12
#define DBE_FP_HDRV_FP_HDRV_OFF_MSB	11
#define DBE_FP_HDRV_FP_HDRV_OFF_LSB	0

#define DBE_FP_DE_FP_DE_ON_MSB		23
#define DBE_FP_DE_FP_DE_ON_LSB		12
#define DBE_FP_DE_FP_DE_OFF_MSB		11
#define DBE_FP_DE_FP_DE_OFF_LSB		0

#define DBE_VT_VSYNC_VT_VSYNC_ON_MSB        23
#define DBE_VT_VSYNC_VT_VSYNC_ON_LSB        12
#define DBE_VT_VSYNC_VT_VSYNC_OFF_MSB       11
#define DBE_VT_VSYNC_VT_VSYNC_OFF_LSB       0

#define DBE_VT_HSYNC_VT_HSYNC_ON_MSB        23
#define DBE_VT_HSYNC_VT_HSYNC_ON_LSB        12
#define DBE_VT_HSYNC_VT_HSYNC_OFF_MSB       11
#define DBE_VT_HSYNC_VT_HSYNC_OFF_LSB       0

#define DBE_VT_VBLANK_VT_VBLANK_ON_MSB        23
#define DBE_VT_VBLANK_VT_VBLANK_ON_LSB        12
#define DBE_VT_VBLANK_VT_VBLANK_OFF_MSB       11
#define DBE_VT_VBLANK_VT_VBLANK_OFF_LSB       0

#define DBE_VT_HBLANK_VT_HBLANK_ON_MSB        23
#define DBE_VT_HBLANK_VT_HBLANK_ON_LSB        12
#define DBE_VT_HBLANK_VT_HBLANK_OFF_MSB       11
#define DBE_VT_HBLANK_VT_HBLANK_OFF_LSB       0

#define DBE_VT_FLAGS_VDRV_INVERT_MSB		0
#define DBE_VT_FLAGS_VDRV_INVERT_LSB		0
#define DBE_VT_FLAGS_HDRV_INVERT_MSB		2
#define DBE_VT_FLAGS_HDRV_INVERT_LSB		2

#define DBE_VT_VCMAP_VT_VCMAP_ON_MSB        23
#define DBE_VT_VCMAP_VT_VCMAP_ON_LSB        12
#define DBE_VT_VCMAP_VT_VCMAP_OFF_MSB       11
#define DBE_VT_VCMAP_VT_VCMAP_OFF_LSB       0

#define DBE_VT_HCMAP_VT_HCMAP_ON_MSB        23
#define DBE_VT_HCMAP_VT_HCMAP_ON_LSB        12
#define DBE_VT_HCMAP_VT_HCMAP_OFF_MSB       11
#define DBE_VT_HCMAP_VT_HCMAP_OFF_LSB       0

#define DBE_VT_XYMAX_VT_MAXX_MSB    11
#define DBE_VT_XYMAX_VT_MAXX_LSB    0
#define DBE_VT_XYMAX_VT_MAXY_MSB    23
#define DBE_VT_XYMAX_VT_MAXY_LSB    12

#define DBE_VT_HPIXEN_VT_HPIXEN_ON_MSB      23
#define DBE_VT_HPIXEN_VT_HPIXEN_ON_LSB      12
#define DBE_VT_HPIXEN_VT_HPIXEN_OFF_MSB     11
#define DBE_VT_HPIXEN_VT_HPIXEN_OFF_LSB     0

#define DBE_VT_VPIXEN_VT_VPIXEN_ON_MSB      23
#define DBE_VT_VPIXEN_VT_VPIXEN_ON_LSB      12
#define DBE_VT_VPIXEN_VT_VPIXEN_OFF_MSB     11
#define DBE_VT_VPIXEN_VT_VPIXEN_OFF_LSB     0

#define DBE_OVR_CONTROL_OVR_DMA_ENABLE_MSB  0
#define DBE_OVR_CONTROL_OVR_DMA_ENABLE_LSB  0

#define DBE_OVR_INHWCTRL_OVR_DMA_ENABLE_MSB 0
#define DBE_OVR_INHWCTRL_OVR_DMA_ENABLE_LSB 0

#define DBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_MSB       13
#define DBE_OVR_WIDTH_TILE_OVR_FIFO_RESET_LSB       13

#define DBE_FRM_CONTROL_FRM_DMA_ENABLE_MSB  0
#define DBE_FRM_CONTROL_FRM_DMA_ENABLE_LSB  0
#define DBE_FRM_CONTROL_FRM_TILE_PTR_MSB    31
#define DBE_FRM_CONTROL_FRM_TILE_PTR_LSB    9
#define DBE_FRM_CONTROL_FRM_LINEAR_MSB      1
#define DBE_FRM_CONTROL_FRM_LINEAR_LSB      1

#define DBE_FRM_INHWCTRL_FRM_DMA_ENABLE_MSB 0
#define DBE_FRM_INHWCTRL_FRM_DMA_ENABLE_LSB 0

#define DBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_MSB        12
#define DBE_FRM_SIZE_TILE_FRM_WIDTH_TILE_LSB        5
#define DBE_FRM_SIZE_TILE_FRM_RHS_MSB       4
#define DBE_FRM_SIZE_TILE_FRM_RHS_LSB       0
#define DBE_FRM_SIZE_TILE_FRM_DEPTH_MSB     14
#define DBE_FRM_SIZE_TILE_FRM_DEPTH_LSB     13
#define DBE_FRM_SIZE_TILE_FRM_FIFO_RESET_MSB        15
#define DBE_FRM_SIZE_TILE_FRM_FIFO_RESET_LSB        15

#define DBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_MSB        31
#define DBE_FRM_SIZE_PIXEL_FB_HEIGHT_PIX_LSB        16

#define DBE_DID_CONTROL_DID_DMA_ENABLE_MSB  0
#define DBE_DID_CONTROL_DID_DMA_ENABLE_LSB  0
#define DBE_DID_INHWCTRL_DID_DMA_ENABLE_MSB 0
#define DBE_DID_INHWCTRL_DID_DMA_ENABLE_LSB 0

#define DBE_DID_START_XY_DID_STARTY_MSB     23
#define DBE_DID_START_XY_DID_STARTY_LSB     12
#define DBE_DID_START_XY_DID_STARTX_MSB     11
#define DBE_DID_START_XY_DID_STARTX_LSB     0

#define DBE_CRS_START_XY_CRS_STARTY_MSB     23
#define DBE_CRS_START_XY_CRS_STARTY_LSB     12
#define DBE_CRS_START_XY_CRS_STARTX_MSB     11
#define DBE_CRS_START_XY_CRS_STARTX_LSB     0

#define DBE_WID_TYP_MSB     4
#define DBE_WID_TYP_LSB     2
#define DBE_WID_BUF_MSB     1
#define DBE_WID_BUF_LSB     0

#define DBE_VC_START_XY_VC_STARTY_MSB       23
#define DBE_VC_START_XY_VC_STARTY_LSB       12
#define DBE_VC_START_XY_VC_STARTX_MSB       11
#define DBE_VC_START_XY_VC_STARTX_LSB       0

/*           */

#define DBE_FRM_DEPTH_8     0
#define DBE_FRM_DEPTH_16    1
#define DBE_FRM_DEPTH_32    2

#define DBE_CMODE_I8        0
#define DBE_CMODE_I12       1
#define DBE_CMODE_RG3B2     2
#define DBE_CMODE_RGB4      3
#define DBE_CMODE_ARGB5     4
#define DBE_CMODE_RGB8      5
#define DBE_CMODE_RGBA5     6
#define DBE_CMODE_RGB10     7

#define DBE_BMODE_BOTH      3

#define DBE_CRS_MAGIC       54

#define DBE_CLOCK_REF_KHZ	27000

/*                                        */

#define DBE_CONFIG_VDAC_ENABLE       0x00000001
#define DBE_CONFIG_VDAC_GSYNC        0x00000002
#define DBE_CONFIG_VDAC_PBLANK       0x00000004
#define DBE_CONFIG_FPENABLE          0x00000008
#define DBE_CONFIG_LENDIAN           0x00000020
#define DBE_CONFIG_TILEHIST          0x00000040
#define DBE_CONFIG_EXT_ADDR          0x00000080

#define DBE_CONFIG_FBDEV        ( DBE_CONFIG_VDAC_ENABLE | \
                                      DBE_CONFIG_VDAC_GSYNC  | \
                                      DBE_CONFIG_VDAC_PBLANK | \
                                      DBE_CONFIG_LENDIAN     | \
                                      DBE_CONFIG_EXT_ADDR )

/*
                                                    
 */

typedef enum {
  DBE_VT_640_480_60,

  DBE_VT_800_600_60,
  DBE_VT_800_600_75,
  DBE_VT_800_600_120,

  DBE_VT_1024_768_50,
  DBE_VT_1024_768_60,
  DBE_VT_1024_768_75,
  DBE_VT_1024_768_85,
  DBE_VT_1024_768_120,

  DBE_VT_1280_1024_50,
  DBE_VT_1280_1024_60,
  DBE_VT_1280_1024_75,
  DBE_VT_1280_1024_85,

  DBE_VT_1600_1024_53,
  DBE_VT_1600_1024_60,

  DBE_VT_1600_1200_50,
  DBE_VT_1600_1200_60,
  DBE_VT_1600_1200_75,

  DBE_VT_1920_1080_50,
  DBE_VT_1920_1080_60,
  DBE_VT_1920_1080_72,

  DBE_VT_1920_1200_50,
  DBE_VT_1920_1200_60,
  DBE_VT_1920_1200_66,

  DBE_VT_UNKNOWN
} dbe_timing_t;



/*
                                    
 */

struct dbe_timing_info
{
  dbe_timing_t type;
  int flags;
  short width;		    /*                     */
  short height;
  int fields_sec;	    /*                                */
  int cfreq;		    /*                                            */
  short htotal;		    /*                         */
  short hblank_start;	    /*                        */
  short hblank_end;	    /*                       */
  short hsync_start;	    /*                       */
  short hsync_end;	    /*                      */
  short vtotal;		    /*                       */
  short vblank_start;	    /*                       */
  short vblank_end;	    /*                     */
  short vsync_start;	    /*                      */
  short vsync_end;	    /*                    */
  short pll_m;		    /*                  */
  short pll_n;		    /*                  */
  short pll_p;		    /*                  */
};

/*                                  */

#define DBE_VOF_UNKNOWNMON    1
#define DBE_VOF_STEREO        2
#define DBE_VOF_DO_GENSYNC    4          /*                      */
#define DBE_VOF_SYNC_ON_GREEN 8          /*               */
#define DBE_VOF_FLATPANEL     0x1000     /*                  */
#define DBE_VOF_MAGICKEY      0x2000     /*              */

/*
                    
 */

#ifdef INCLUDE_TIMING_TABLE_DATA
struct dbe_timing_info dbeVTimings[] = {
  {
    DBE_VT_640_480_60,
    /*                                             */
    0,	        640,			480,		59940,			25175,
    /*                                                          */
    800,	640,		        800,		656,		752,
    /*                                                          */
    525,	480,		        525,		490,		    492,
    /*                       */
    15,	    2,				3
  },

  {
    DBE_VT_800_600_60,
    /*                                             */
    0,	    800,			600,		60317,			40000,
    /*                                                          */
    1056,	800,		    1056,		840,		    968,
    /*                                                          */
    628,	600,		    628,		601,		    605,
    /*                       */
    3,	    1,				1
  },

  {
    DBE_VT_800_600_75,
    /*                                                   */
    0,	    800,		    600,		75000,		    49500,
    /*                                                          */
    1056,	800,		    1056,		816,		    896,
    /*                                                          */
    625,	600,		    625,		601,		    604,
    /*                          */
    11,	    3,		        1
  },

  {
    DBE_VT_800_600_120,
    /*                                                    */
    DBE_VOF_STEREO,	    800,		600,			119800,		    82978,
    /*                                                          */
    1040,	800,		    1040,		856,		    976,
    /*                                                          */
    666,	600,		    666,		637,		    643,
    /*                          */
    31,	    5,		        1
  },

  {
    DBE_VT_1024_768_50,
    /*                                                   */
    0,	    1024,		    768,		50000,		    54163,
    /*                                                          */
    1344,	1024,		    1344,		1048,		    1184,
    /*                                                          */
    806,	768,		    806,		771,		    777,
    /*                          */
    4,	    1,		        1
  },

  {
    DBE_VT_1024_768_60,
    /*                                             */
    0,	    1024,			768,		60004,			65000,
    /*                                                          */
    1344,	1024,		    1344,		1048,		    1184,
    /*                                                          */
    806,	768,		    806,		771,		    777,
    /*                       */
    12,	    5,				0
  },

  {
    DBE_VT_1024_768_75,
    /*                                             */
    0,	    1024,			768,		75029,			78750,
    /*                                                          */
    1312,	1024,		    1312,		1040,		    1136,
    /*                                                          */
    800,	768,		    800,		769,		    772,
    /*                       */
    29,	    5,				1
  },

  {
    DBE_VT_1024_768_85,
    /*                                             */
    0,	    1024,			768,		84997,			94500,
    /*                                                          */
    1376,	1024,		    1376,		1072,		    1168,
    /*                                                          */
    808,	768,		    808,		769,		    772,
    /*                       */
    7,	    2,				0
  },

  {
    DBE_VT_1024_768_120,
    /*                                                 */
    DBE_VOF_STEREO,	    1024,		768,			119800,			133195,
    /*                                                          */
    1376,	1024,		    1376,		1072,		    1168,
    /*                                                          */
    808,	768,		    808,		769,		    772,
    /*                       */
    5,	    1,				0
  },

  {
    DBE_VT_1280_1024_50,
    /*                                             */
    0,	    1280,			1024,		50000,			89460,
    /*                                                          */
    1680,	1280,		    1680,		1360,		    1480,
    /*                                                          */
    1065,	1024,		    1065,		1027,		    1030,
    /*                       */
    10,	    3,				0
  },

  {
    DBE_VT_1280_1024_60,
    /*                                             */
    0,	    1280,			1024,		60020,			108000,
    /*                                                          */
    1688,	1280,		    1688,		1328,		    1440,
    /*                                                          */
    1066,	1024,		    1066,		1025,		    1028,
    /*                       */
    4,	    1,			    0
  },

  {
    DBE_VT_1280_1024_75,
    /*                                             */
    0,	    1280,			1024,		75025,			135000,
    /*                                                          */
    1688,	1280,		    1688,		1296,		    1440,
    /*                                                          */
    1066,	1024,		    1066,		1025,		    1028,
    /*                       */
    5,	    1,				0
  },

  {
    DBE_VT_1280_1024_85,
    /*                                                   */
    0,	    1280,		    1024,		85024,		    157500,
    /*                                                          */
    1728,	1280,		    1728,		1344,		    1504,
    /*                                                          */
    1072,	1024,		    1072,		1025,		    1028,
    /*                          */
    29,	    5,		        0
  },

  {
    DBE_VT_1600_1024_53,
    /*                                                */
    DBE_VOF_FLATPANEL | DBE_VOF_MAGICKEY,
    1600,			1024,		53000,			107447,
    /*                                                                   */
    1900,   1600,           1900,           1630,           1730,
    /*                                                                   */
    1067,   1024,           1067,           1027,           1030,
    /*                               */
    4,      1,              0
  },

  {
    DBE_VT_1600_1024_60,
    /*                                                            */
    DBE_VOF_FLATPANEL,   1600,           1024,			60000,          106913,
    /*                                                                   */
    1670,   1600,           1670,           1630,           1650,
    /*                                                                   */
    1067,   1024,           1067,           1027,           1030,
    /*                               */
    4,      1,              0
  },

  {
    DBE_VT_1600_1200_50,
    /*                                                               */
    0,      1600,           1200,           50000,          130500,
    /*                                                                   */
    2088,   1600,           2088,           1644,           1764,
    /*                                                                   */
    1250,   1200,           1250,           1205,           1211,
    /*                               */
    24,     5,              0
  },

  {
    DBE_VT_1600_1200_60,
    /*                                                               */
    0,      1600,           1200,           59940,          162000,
    /*                                                                   */
    2160,   1600,           2160,           1644,           1856,
    /*                                                                   */
    1250,   1200,           1250,           1201,           1204,
    /*                               */
    6,		1,              0
  },

  {
    DBE_VT_1600_1200_75,
    /*                                                               */
    0,      1600,           1200,           75000,          202500,
    /*                                                                   */
    2160,   1600,           2160,           1644,           1856,
    /*                                                                   */
    1250,   1200,           1250,           1201,           1204,
    /*                               */
    15,		2,              0
  },

  {
    DBE_VT_1920_1080_50,
    /*                                                               */
    0,      1920,           1080,           50000,          133200,
    /*                                                                   */
    2368,   1920,           2368,           1952,           2096,
    /*                                                                   */
    1125,   1080,           1125,           1083,           1086,
    /*                               */
    5,      1,              0
  },

  {
    DBE_VT_1920_1080_60,
    /*                                                               */
    0,      1920,           1080,           59940,          159840,
    /*                                                                   */
    2368,   1920,           2368,           1952,           2096,
    /*                                                                   */
    1125,   1080,           1125,           1083,           1086,
    /*                               */
    6,      1,              0
  },

  {
    DBE_VT_1920_1080_72,
    /*                                                               */
    0,      1920,           1080,           72000,          216023,
    /*                                                                   */
    2560,   1920,           2560,           1968,           2184,
    /*                                                                   */
    1172,   1080,           1172,           1083,           1086,
    /*                               */
    8,      1,              0
  },

  {
    DBE_VT_1920_1200_50,
    /*                                                               */
    0,      1920,           1200,           50000,          161500,
    /*                                                                   */
    2584,   1920,           2584,           1984,           2240,
    /*                                                                   */
    1250,   1200,           1250,           1203,           1206,
    /*                               */
    6,      1,              0
  },

  {
    DBE_VT_1920_1200_60,
    /*                                                               */
    0,      1920,           1200,           59940,          193800,
    /*                                                                   */
    2584,   1920,           2584,           1984,           2240,
    /*                                                                   */
    1250,   1200,           1250,           1203,           1206,
    /*                               */
    29,     4,              0
  },

  {
    DBE_VT_1920_1200_66,
    /*                                                               */
    0,      1920,           1200,           66000,          213180,
    /*                                                                   */
    2584,   1920,           2584,           1984,           2240,
    /*                                                                   */
    1250,   1200,           1250,           1203,           1206,
    /*                               */
    8,      1,              0
  }
};

#endif //                          

#endif //                
