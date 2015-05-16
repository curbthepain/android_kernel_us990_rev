#ifndef __iop_sw_spu_defs_asm_h
#define __iop_sw_spu_defs_asm_h

/*
                                  
                                 
   
                                                                                        
                                 
  
                              
 */

#ifndef REG_FIELD
#define REG_FIELD( scope, reg, field, value ) \
  REG_FIELD_X_( value, reg_##scope##_##reg##___##field##___lsb )
#define REG_FIELD_X_( value, shift ) ((value) << shift)
#endif

#ifndef REG_STATE
#define REG_STATE( scope, reg, field, symbolic_value ) \
  REG_STATE_X_( regk_##scope##_##symbolic_value, reg_##scope##_##reg##___##field##___lsb )
#define REG_STATE_X_( k, shift ) (k << shift)
#endif

#ifndef REG_MASK
#define REG_MASK( scope, reg, field ) \
  REG_MASK_X_( reg_##scope##_##reg##___##field##___width, reg_##scope##_##reg##___##field##___lsb )
#define REG_MASK_X_( width, lsb ) (((1 << width)-1) << lsb)
#endif

#ifndef REG_LSB
#define REG_LSB( scope, reg, field ) reg_##scope##_##reg##___##field##___lsb
#endif

#ifndef REG_BIT
#define REG_BIT( scope, reg, field ) reg_##scope##_##reg##___##field##___bit
#endif

#ifndef REG_ADDR
#define REG_ADDR( scope, inst, reg ) REG_ADDR_X_(inst, reg_##scope##_##reg##_offset)
#define REG_ADDR_X_( inst, offs ) ((inst) + offs)
#endif

#ifndef REG_ADDR_VECT
#define REG_ADDR_VECT( scope, inst, reg, index ) \
         REG_ADDR_VECT_X_(inst, reg_##scope##_##reg##_offset, index, \
			 STRIDE_##scope##_##reg )
#define REG_ADDR_VECT_X_( inst, offs, index, stride ) \
                          ((inst) + offs + (index) * stride)
#endif

/*                                                */
#define reg_iop_sw_spu_r_mpu_trace_offset 0

/*                                                */
#define reg_iop_sw_spu_rw_mc_ctrl___keep_owner___lsb 0
#define reg_iop_sw_spu_rw_mc_ctrl___keep_owner___width 1
#define reg_iop_sw_spu_rw_mc_ctrl___keep_owner___bit 0
#define reg_iop_sw_spu_rw_mc_ctrl___cmd___lsb 1
#define reg_iop_sw_spu_rw_mc_ctrl___cmd___width 2
#define reg_iop_sw_spu_rw_mc_ctrl___size___lsb 3
#define reg_iop_sw_spu_rw_mc_ctrl___size___width 3
#define reg_iop_sw_spu_rw_mc_ctrl___wr_spu_mem___lsb 6
#define reg_iop_sw_spu_rw_mc_ctrl___wr_spu_mem___width 1
#define reg_iop_sw_spu_rw_mc_ctrl___wr_spu_mem___bit 6
#define reg_iop_sw_spu_rw_mc_ctrl_offset 4

/*                                                */
#define reg_iop_sw_spu_rw_mc_data___val___lsb 0
#define reg_iop_sw_spu_rw_mc_data___val___width 32
#define reg_iop_sw_spu_rw_mc_data_offset 8

/*                                                */
#define reg_iop_sw_spu_rw_mc_addr_offset 12

/*                                                */
#define reg_iop_sw_spu_rs_mc_data_offset 16

/*                                              */
#define reg_iop_sw_spu_r_mc_data_offset 20

/*                                              */
#define reg_iop_sw_spu_r_mc_stat___busy_cpu___lsb 0
#define reg_iop_sw_spu_r_mc_stat___busy_cpu___width 1
#define reg_iop_sw_spu_r_mc_stat___busy_cpu___bit 0
#define reg_iop_sw_spu_r_mc_stat___busy_mpu___lsb 1
#define reg_iop_sw_spu_r_mc_stat___busy_mpu___width 1
#define reg_iop_sw_spu_r_mc_stat___busy_mpu___bit 1
#define reg_iop_sw_spu_r_mc_stat___busy_spu___lsb 2
#define reg_iop_sw_spu_r_mc_stat___busy_spu___width 1
#define reg_iop_sw_spu_r_mc_stat___busy_spu___bit 2
#define reg_iop_sw_spu_r_mc_stat___owned_by_cpu___lsb 3
#define reg_iop_sw_spu_r_mc_stat___owned_by_cpu___width 1
#define reg_iop_sw_spu_r_mc_stat___owned_by_cpu___bit 3
#define reg_iop_sw_spu_r_mc_stat___owned_by_mpu___lsb 4
#define reg_iop_sw_spu_r_mc_stat___owned_by_mpu___width 1
#define reg_iop_sw_spu_r_mc_stat___owned_by_mpu___bit 4
#define reg_iop_sw_spu_r_mc_stat___owned_by_spu___lsb 5
#define reg_iop_sw_spu_r_mc_stat___owned_by_spu___width 1
#define reg_iop_sw_spu_r_mc_stat___owned_by_spu___bit 5
#define reg_iop_sw_spu_r_mc_stat_offset 24

/*                                                     */
#define reg_iop_sw_spu_rw_bus_clr_mask___byte0___lsb 0
#define reg_iop_sw_spu_rw_bus_clr_mask___byte0___width 8
#define reg_iop_sw_spu_rw_bus_clr_mask___byte1___lsb 8
#define reg_iop_sw_spu_rw_bus_clr_mask___byte1___width 8
#define reg_iop_sw_spu_rw_bus_clr_mask___byte2___lsb 16
#define reg_iop_sw_spu_rw_bus_clr_mask___byte2___width 8
#define reg_iop_sw_spu_rw_bus_clr_mask___byte3___lsb 24
#define reg_iop_sw_spu_rw_bus_clr_mask___byte3___width 8
#define reg_iop_sw_spu_rw_bus_clr_mask_offset 28

/*                                                     */
#define reg_iop_sw_spu_rw_bus_set_mask___byte0___lsb 0
#define reg_iop_sw_spu_rw_bus_set_mask___byte0___width 8
#define reg_iop_sw_spu_rw_bus_set_mask___byte1___lsb 8
#define reg_iop_sw_spu_rw_bus_set_mask___byte1___width 8
#define reg_iop_sw_spu_rw_bus_set_mask___byte2___lsb 16
#define reg_iop_sw_spu_rw_bus_set_mask___byte2___width 8
#define reg_iop_sw_spu_rw_bus_set_mask___byte3___lsb 24
#define reg_iop_sw_spu_rw_bus_set_mask___byte3___width 8
#define reg_iop_sw_spu_rw_bus_set_mask_offset 32

/*                                                        */
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte0___lsb 0
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte0___width 1
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte0___bit 0
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte1___lsb 1
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte1___width 1
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte1___bit 1
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte2___lsb 2
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte2___width 1
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte2___bit 2
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte3___lsb 3
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte3___width 1
#define reg_iop_sw_spu_rw_bus_oe_clr_mask___byte3___bit 3
#define reg_iop_sw_spu_rw_bus_oe_clr_mask_offset 36

/*                                                        */
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte0___lsb 0
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte0___width 1
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte0___bit 0
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte1___lsb 1
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte1___width 1
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte1___bit 1
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte2___lsb 2
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte2___width 1
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte2___bit 2
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte3___lsb 3
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte3___width 1
#define reg_iop_sw_spu_rw_bus_oe_set_mask___byte3___bit 3
#define reg_iop_sw_spu_rw_bus_oe_set_mask_offset 40

/*                                             */
#define reg_iop_sw_spu_r_bus_in_offset 44

/*                                                     */
#define reg_iop_sw_spu_rw_gio_clr_mask___val___lsb 0
#define reg_iop_sw_spu_rw_gio_clr_mask___val___width 32
#define reg_iop_sw_spu_rw_gio_clr_mask_offset 48

/*                                                     */
#define reg_iop_sw_spu_rw_gio_set_mask___val___lsb 0
#define reg_iop_sw_spu_rw_gio_set_mask___val___width 32
#define reg_iop_sw_spu_rw_gio_set_mask_offset 52

/*                                                        */
#define reg_iop_sw_spu_rw_gio_oe_clr_mask___val___lsb 0
#define reg_iop_sw_spu_rw_gio_oe_clr_mask___val___width 32
#define reg_iop_sw_spu_rw_gio_oe_clr_mask_offset 56

/*                                                        */
#define reg_iop_sw_spu_rw_gio_oe_set_mask___val___lsb 0
#define reg_iop_sw_spu_rw_gio_oe_set_mask___val___width 32
#define reg_iop_sw_spu_rw_gio_oe_set_mask_offset 60

/*                                             */
#define reg_iop_sw_spu_r_gio_in_offset 64

/*                                                        */
#define reg_iop_sw_spu_rw_bus_clr_mask_lo___byte0___lsb 0
#define reg_iop_sw_spu_rw_bus_clr_mask_lo___byte0___width 8
#define reg_iop_sw_spu_rw_bus_clr_mask_lo___byte1___lsb 8
#define reg_iop_sw_spu_rw_bus_clr_mask_lo___byte1___width 8
#define reg_iop_sw_spu_rw_bus_clr_mask_lo_offset 68

/*                                                        */
#define reg_iop_sw_spu_rw_bus_clr_mask_hi___byte2___lsb 0
#define reg_iop_sw_spu_rw_bus_clr_mask_hi___byte2___width 8
#define reg_iop_sw_spu_rw_bus_clr_mask_hi___byte3___lsb 8
#define reg_iop_sw_spu_rw_bus_clr_mask_hi___byte3___width 8
#define reg_iop_sw_spu_rw_bus_clr_mask_hi_offset 72

/*                                                        */
#define reg_iop_sw_spu_rw_bus_set_mask_lo___byte0___lsb 0
#define reg_iop_sw_spu_rw_bus_set_mask_lo___byte0___width 8
#define reg_iop_sw_spu_rw_bus_set_mask_lo___byte1___lsb 8
#define reg_iop_sw_spu_rw_bus_set_mask_lo___byte1___width 8
#define reg_iop_sw_spu_rw_bus_set_mask_lo_offset 76

/*                                                        */
#define reg_iop_sw_spu_rw_bus_set_mask_hi___byte2___lsb 0
#define reg_iop_sw_spu_rw_bus_set_mask_hi___byte2___width 8
#define reg_iop_sw_spu_rw_bus_set_mask_hi___byte3___lsb 8
#define reg_iop_sw_spu_rw_bus_set_mask_hi___byte3___width 8
#define reg_iop_sw_spu_rw_bus_set_mask_hi_offset 80

/*                                                        */
#define reg_iop_sw_spu_rw_gio_clr_mask_lo___val___lsb 0
#define reg_iop_sw_spu_rw_gio_clr_mask_lo___val___width 16
#define reg_iop_sw_spu_rw_gio_clr_mask_lo_offset 84

/*                                                        */
#define reg_iop_sw_spu_rw_gio_clr_mask_hi___val___lsb 0
#define reg_iop_sw_spu_rw_gio_clr_mask_hi___val___width 16
#define reg_iop_sw_spu_rw_gio_clr_mask_hi_offset 88

/*                                                        */
#define reg_iop_sw_spu_rw_gio_set_mask_lo___val___lsb 0
#define reg_iop_sw_spu_rw_gio_set_mask_lo___val___width 16
#define reg_iop_sw_spu_rw_gio_set_mask_lo_offset 92

/*                                                        */
#define reg_iop_sw_spu_rw_gio_set_mask_hi___val___lsb 0
#define reg_iop_sw_spu_rw_gio_set_mask_hi___val___width 16
#define reg_iop_sw_spu_rw_gio_set_mask_hi_offset 96

/*                                                           */
#define reg_iop_sw_spu_rw_gio_oe_clr_mask_lo___val___lsb 0
#define reg_iop_sw_spu_rw_gio_oe_clr_mask_lo___val___width 16
#define reg_iop_sw_spu_rw_gio_oe_clr_mask_lo_offset 100

/*                                                           */
#define reg_iop_sw_spu_rw_gio_oe_clr_mask_hi___val___lsb 0
#define reg_iop_sw_spu_rw_gio_oe_clr_mask_hi___val___width 16
#define reg_iop_sw_spu_rw_gio_oe_clr_mask_hi_offset 104

/*                                                           */
#define reg_iop_sw_spu_rw_gio_oe_set_mask_lo___val___lsb 0
#define reg_iop_sw_spu_rw_gio_oe_set_mask_lo___val___width 16
#define reg_iop_sw_spu_rw_gio_oe_set_mask_lo_offset 108

/*                                                           */
#define reg_iop_sw_spu_rw_gio_oe_set_mask_hi___val___lsb 0
#define reg_iop_sw_spu_rw_gio_oe_set_mask_hi___val___width 16
#define reg_iop_sw_spu_rw_gio_oe_set_mask_hi_offset 112

/*                                                 */
#define reg_iop_sw_spu_rw_cpu_intr___intr0___lsb 0
#define reg_iop_sw_spu_rw_cpu_intr___intr0___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr0___bit 0
#define reg_iop_sw_spu_rw_cpu_intr___intr1___lsb 1
#define reg_iop_sw_spu_rw_cpu_intr___intr1___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr1___bit 1
#define reg_iop_sw_spu_rw_cpu_intr___intr2___lsb 2
#define reg_iop_sw_spu_rw_cpu_intr___intr2___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr2___bit 2
#define reg_iop_sw_spu_rw_cpu_intr___intr3___lsb 3
#define reg_iop_sw_spu_rw_cpu_intr___intr3___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr3___bit 3
#define reg_iop_sw_spu_rw_cpu_intr___intr4___lsb 4
#define reg_iop_sw_spu_rw_cpu_intr___intr4___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr4___bit 4
#define reg_iop_sw_spu_rw_cpu_intr___intr5___lsb 5
#define reg_iop_sw_spu_rw_cpu_intr___intr5___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr5___bit 5
#define reg_iop_sw_spu_rw_cpu_intr___intr6___lsb 6
#define reg_iop_sw_spu_rw_cpu_intr___intr6___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr6___bit 6
#define reg_iop_sw_spu_rw_cpu_intr___intr7___lsb 7
#define reg_iop_sw_spu_rw_cpu_intr___intr7___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr7___bit 7
#define reg_iop_sw_spu_rw_cpu_intr___intr8___lsb 8
#define reg_iop_sw_spu_rw_cpu_intr___intr8___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr8___bit 8
#define reg_iop_sw_spu_rw_cpu_intr___intr9___lsb 9
#define reg_iop_sw_spu_rw_cpu_intr___intr9___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr9___bit 9
#define reg_iop_sw_spu_rw_cpu_intr___intr10___lsb 10
#define reg_iop_sw_spu_rw_cpu_intr___intr10___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr10___bit 10
#define reg_iop_sw_spu_rw_cpu_intr___intr11___lsb 11
#define reg_iop_sw_spu_rw_cpu_intr___intr11___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr11___bit 11
#define reg_iop_sw_spu_rw_cpu_intr___intr12___lsb 12
#define reg_iop_sw_spu_rw_cpu_intr___intr12___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr12___bit 12
#define reg_iop_sw_spu_rw_cpu_intr___intr13___lsb 13
#define reg_iop_sw_spu_rw_cpu_intr___intr13___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr13___bit 13
#define reg_iop_sw_spu_rw_cpu_intr___intr14___lsb 14
#define reg_iop_sw_spu_rw_cpu_intr___intr14___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr14___bit 14
#define reg_iop_sw_spu_rw_cpu_intr___intr15___lsb 15
#define reg_iop_sw_spu_rw_cpu_intr___intr15___width 1
#define reg_iop_sw_spu_rw_cpu_intr___intr15___bit 15
#define reg_iop_sw_spu_rw_cpu_intr_offset 116

/*                                               */
#define reg_iop_sw_spu_r_cpu_intr___intr0___lsb 0
#define reg_iop_sw_spu_r_cpu_intr___intr0___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr0___bit 0
#define reg_iop_sw_spu_r_cpu_intr___intr1___lsb 1
#define reg_iop_sw_spu_r_cpu_intr___intr1___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr1___bit 1
#define reg_iop_sw_spu_r_cpu_intr___intr2___lsb 2
#define reg_iop_sw_spu_r_cpu_intr___intr2___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr2___bit 2
#define reg_iop_sw_spu_r_cpu_intr___intr3___lsb 3
#define reg_iop_sw_spu_r_cpu_intr___intr3___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr3___bit 3
#define reg_iop_sw_spu_r_cpu_intr___intr4___lsb 4
#define reg_iop_sw_spu_r_cpu_intr___intr4___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr4___bit 4
#define reg_iop_sw_spu_r_cpu_intr___intr5___lsb 5
#define reg_iop_sw_spu_r_cpu_intr___intr5___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr5___bit 5
#define reg_iop_sw_spu_r_cpu_intr___intr6___lsb 6
#define reg_iop_sw_spu_r_cpu_intr___intr6___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr6___bit 6
#define reg_iop_sw_spu_r_cpu_intr___intr7___lsb 7
#define reg_iop_sw_spu_r_cpu_intr___intr7___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr7___bit 7
#define reg_iop_sw_spu_r_cpu_intr___intr8___lsb 8
#define reg_iop_sw_spu_r_cpu_intr___intr8___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr8___bit 8
#define reg_iop_sw_spu_r_cpu_intr___intr9___lsb 9
#define reg_iop_sw_spu_r_cpu_intr___intr9___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr9___bit 9
#define reg_iop_sw_spu_r_cpu_intr___intr10___lsb 10
#define reg_iop_sw_spu_r_cpu_intr___intr10___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr10___bit 10
#define reg_iop_sw_spu_r_cpu_intr___intr11___lsb 11
#define reg_iop_sw_spu_r_cpu_intr___intr11___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr11___bit 11
#define reg_iop_sw_spu_r_cpu_intr___intr12___lsb 12
#define reg_iop_sw_spu_r_cpu_intr___intr12___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr12___bit 12
#define reg_iop_sw_spu_r_cpu_intr___intr13___lsb 13
#define reg_iop_sw_spu_r_cpu_intr___intr13___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr13___bit 13
#define reg_iop_sw_spu_r_cpu_intr___intr14___lsb 14
#define reg_iop_sw_spu_r_cpu_intr___intr14___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr14___bit 14
#define reg_iop_sw_spu_r_cpu_intr___intr15___lsb 15
#define reg_iop_sw_spu_r_cpu_intr___intr15___width 1
#define reg_iop_sw_spu_r_cpu_intr___intr15___bit 15
#define reg_iop_sw_spu_r_cpu_intr_offset 120

/*                                              */
#define reg_iop_sw_spu_r_hw_intr___trigger_grp0___lsb 0
#define reg_iop_sw_spu_r_hw_intr___trigger_grp0___width 1
#define reg_iop_sw_spu_r_hw_intr___trigger_grp0___bit 0
#define reg_iop_sw_spu_r_hw_intr___trigger_grp1___lsb 1
#define reg_iop_sw_spu_r_hw_intr___trigger_grp1___width 1
#define reg_iop_sw_spu_r_hw_intr___trigger_grp1___bit 1
#define reg_iop_sw_spu_r_hw_intr___trigger_grp2___lsb 2
#define reg_iop_sw_spu_r_hw_intr___trigger_grp2___width 1
#define reg_iop_sw_spu_r_hw_intr___trigger_grp2___bit 2
#define reg_iop_sw_spu_r_hw_intr___trigger_grp3___lsb 3
#define reg_iop_sw_spu_r_hw_intr___trigger_grp3___width 1
#define reg_iop_sw_spu_r_hw_intr___trigger_grp3___bit 3
#define reg_iop_sw_spu_r_hw_intr___trigger_grp4___lsb 4
#define reg_iop_sw_spu_r_hw_intr___trigger_grp4___width 1
#define reg_iop_sw_spu_r_hw_intr___trigger_grp4___bit 4
#define reg_iop_sw_spu_r_hw_intr___trigger_grp5___lsb 5
#define reg_iop_sw_spu_r_hw_intr___trigger_grp5___width 1
#define reg_iop_sw_spu_r_hw_intr___trigger_grp5___bit 5
#define reg_iop_sw_spu_r_hw_intr___trigger_grp6___lsb 6
#define reg_iop_sw_spu_r_hw_intr___trigger_grp6___width 1
#define reg_iop_sw_spu_r_hw_intr___trigger_grp6___bit 6
#define reg_iop_sw_spu_r_hw_intr___trigger_grp7___lsb 7
#define reg_iop_sw_spu_r_hw_intr___trigger_grp7___width 1
#define reg_iop_sw_spu_r_hw_intr___trigger_grp7___bit 7
#define reg_iop_sw_spu_r_hw_intr___timer_grp0___lsb 8
#define reg_iop_sw_spu_r_hw_intr___timer_grp0___width 1
#define reg_iop_sw_spu_r_hw_intr___timer_grp0___bit 8
#define reg_iop_sw_spu_r_hw_intr___timer_grp1___lsb 9
#define reg_iop_sw_spu_r_hw_intr___timer_grp1___width 1
#define reg_iop_sw_spu_r_hw_intr___timer_grp1___bit 9
#define reg_iop_sw_spu_r_hw_intr___fifo_out___lsb 10
#define reg_iop_sw_spu_r_hw_intr___fifo_out___width 1
#define reg_iop_sw_spu_r_hw_intr___fifo_out___bit 10
#define reg_iop_sw_spu_r_hw_intr___fifo_out_extra___lsb 11
#define reg_iop_sw_spu_r_hw_intr___fifo_out_extra___width 1
#define reg_iop_sw_spu_r_hw_intr___fifo_out_extra___bit 11
#define reg_iop_sw_spu_r_hw_intr___fifo_in___lsb 12
#define reg_iop_sw_spu_r_hw_intr___fifo_in___width 1
#define reg_iop_sw_spu_r_hw_intr___fifo_in___bit 12
#define reg_iop_sw_spu_r_hw_intr___fifo_in_extra___lsb 13
#define reg_iop_sw_spu_r_hw_intr___fifo_in_extra___width 1
#define reg_iop_sw_spu_r_hw_intr___fifo_in_extra___bit 13
#define reg_iop_sw_spu_r_hw_intr___dmc_out___lsb 14
#define reg_iop_sw_spu_r_hw_intr___dmc_out___width 1
#define reg_iop_sw_spu_r_hw_intr___dmc_out___bit 14
#define reg_iop_sw_spu_r_hw_intr___dmc_in___lsb 15
#define reg_iop_sw_spu_r_hw_intr___dmc_in___width 1
#define reg_iop_sw_spu_r_hw_intr___dmc_in___bit 15
#define reg_iop_sw_spu_r_hw_intr_offset 124

/*                                                 */
#define reg_iop_sw_spu_rw_mpu_intr___intr0___lsb 0
#define reg_iop_sw_spu_rw_mpu_intr___intr0___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr0___bit 0
#define reg_iop_sw_spu_rw_mpu_intr___intr1___lsb 1
#define reg_iop_sw_spu_rw_mpu_intr___intr1___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr1___bit 1
#define reg_iop_sw_spu_rw_mpu_intr___intr2___lsb 2
#define reg_iop_sw_spu_rw_mpu_intr___intr2___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr2___bit 2
#define reg_iop_sw_spu_rw_mpu_intr___intr3___lsb 3
#define reg_iop_sw_spu_rw_mpu_intr___intr3___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr3___bit 3
#define reg_iop_sw_spu_rw_mpu_intr___intr4___lsb 4
#define reg_iop_sw_spu_rw_mpu_intr___intr4___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr4___bit 4
#define reg_iop_sw_spu_rw_mpu_intr___intr5___lsb 5
#define reg_iop_sw_spu_rw_mpu_intr___intr5___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr5___bit 5
#define reg_iop_sw_spu_rw_mpu_intr___intr6___lsb 6
#define reg_iop_sw_spu_rw_mpu_intr___intr6___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr6___bit 6
#define reg_iop_sw_spu_rw_mpu_intr___intr7___lsb 7
#define reg_iop_sw_spu_rw_mpu_intr___intr7___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr7___bit 7
#define reg_iop_sw_spu_rw_mpu_intr___intr8___lsb 8
#define reg_iop_sw_spu_rw_mpu_intr___intr8___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr8___bit 8
#define reg_iop_sw_spu_rw_mpu_intr___intr9___lsb 9
#define reg_iop_sw_spu_rw_mpu_intr___intr9___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr9___bit 9
#define reg_iop_sw_spu_rw_mpu_intr___intr10___lsb 10
#define reg_iop_sw_spu_rw_mpu_intr___intr10___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr10___bit 10
#define reg_iop_sw_spu_rw_mpu_intr___intr11___lsb 11
#define reg_iop_sw_spu_rw_mpu_intr___intr11___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr11___bit 11
#define reg_iop_sw_spu_rw_mpu_intr___intr12___lsb 12
#define reg_iop_sw_spu_rw_mpu_intr___intr12___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr12___bit 12
#define reg_iop_sw_spu_rw_mpu_intr___intr13___lsb 13
#define reg_iop_sw_spu_rw_mpu_intr___intr13___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr13___bit 13
#define reg_iop_sw_spu_rw_mpu_intr___intr14___lsb 14
#define reg_iop_sw_spu_rw_mpu_intr___intr14___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr14___bit 14
#define reg_iop_sw_spu_rw_mpu_intr___intr15___lsb 15
#define reg_iop_sw_spu_rw_mpu_intr___intr15___width 1
#define reg_iop_sw_spu_rw_mpu_intr___intr15___bit 15
#define reg_iop_sw_spu_rw_mpu_intr_offset 128

/*                                               */
#define reg_iop_sw_spu_r_mpu_intr___intr0___lsb 0
#define reg_iop_sw_spu_r_mpu_intr___intr0___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr0___bit 0
#define reg_iop_sw_spu_r_mpu_intr___intr1___lsb 1
#define reg_iop_sw_spu_r_mpu_intr___intr1___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr1___bit 1
#define reg_iop_sw_spu_r_mpu_intr___intr2___lsb 2
#define reg_iop_sw_spu_r_mpu_intr___intr2___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr2___bit 2
#define reg_iop_sw_spu_r_mpu_intr___intr3___lsb 3
#define reg_iop_sw_spu_r_mpu_intr___intr3___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr3___bit 3
#define reg_iop_sw_spu_r_mpu_intr___intr4___lsb 4
#define reg_iop_sw_spu_r_mpu_intr___intr4___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr4___bit 4
#define reg_iop_sw_spu_r_mpu_intr___intr5___lsb 5
#define reg_iop_sw_spu_r_mpu_intr___intr5___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr5___bit 5
#define reg_iop_sw_spu_r_mpu_intr___intr6___lsb 6
#define reg_iop_sw_spu_r_mpu_intr___intr6___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr6___bit 6
#define reg_iop_sw_spu_r_mpu_intr___intr7___lsb 7
#define reg_iop_sw_spu_r_mpu_intr___intr7___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr7___bit 7
#define reg_iop_sw_spu_r_mpu_intr___intr8___lsb 8
#define reg_iop_sw_spu_r_mpu_intr___intr8___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr8___bit 8
#define reg_iop_sw_spu_r_mpu_intr___intr9___lsb 9
#define reg_iop_sw_spu_r_mpu_intr___intr9___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr9___bit 9
#define reg_iop_sw_spu_r_mpu_intr___intr10___lsb 10
#define reg_iop_sw_spu_r_mpu_intr___intr10___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr10___bit 10
#define reg_iop_sw_spu_r_mpu_intr___intr11___lsb 11
#define reg_iop_sw_spu_r_mpu_intr___intr11___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr11___bit 11
#define reg_iop_sw_spu_r_mpu_intr___intr12___lsb 12
#define reg_iop_sw_spu_r_mpu_intr___intr12___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr12___bit 12
#define reg_iop_sw_spu_r_mpu_intr___intr13___lsb 13
#define reg_iop_sw_spu_r_mpu_intr___intr13___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr13___bit 13
#define reg_iop_sw_spu_r_mpu_intr___intr14___lsb 14
#define reg_iop_sw_spu_r_mpu_intr___intr14___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr14___bit 14
#define reg_iop_sw_spu_r_mpu_intr___intr15___lsb 15
#define reg_iop_sw_spu_r_mpu_intr___intr15___width 1
#define reg_iop_sw_spu_r_mpu_intr___intr15___bit 15
#define reg_iop_sw_spu_r_mpu_intr_offset 132


/*           */
#define regk_iop_sw_spu_copy                      0x00000000
#define regk_iop_sw_spu_no                        0x00000000
#define regk_iop_sw_spu_nop                       0x00000000
#define regk_iop_sw_spu_rd                        0x00000002
#define regk_iop_sw_spu_reg_copy                  0x00000001
#define regk_iop_sw_spu_rw_bus_clr_mask_default   0x00000000
#define regk_iop_sw_spu_rw_bus_oe_clr_mask_default  0x00000000
#define regk_iop_sw_spu_rw_bus_oe_set_mask_default  0x00000000
#define regk_iop_sw_spu_rw_bus_set_mask_default   0x00000000
#define regk_iop_sw_spu_rw_gio_clr_mask_default   0x00000000
#define regk_iop_sw_spu_rw_gio_oe_clr_mask_default  0x00000000
#define regk_iop_sw_spu_rw_gio_oe_set_mask_default  0x00000000
#define regk_iop_sw_spu_rw_gio_set_mask_default   0x00000000
#define regk_iop_sw_spu_set                       0x00000001
#define regk_iop_sw_spu_wr                        0x00000003
#define regk_iop_sw_spu_yes                       0x00000001
#endif /*                         */
