#ifndef __iop_sw_cpu_defs_asm_h
#define __iop_sw_cpu_defs_asm_h

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
#define reg_iop_sw_cpu_r_mpu_trace_offset 0

/*                                                */
#define reg_iop_sw_cpu_r_spu_trace_offset 4

/*                                                    */
#define reg_iop_sw_cpu_r_spu_fsm_trace_offset 8

/*                                                */
#define reg_iop_sw_cpu_rw_mc_ctrl___keep_owner___lsb 0
#define reg_iop_sw_cpu_rw_mc_ctrl___keep_owner___width 1
#define reg_iop_sw_cpu_rw_mc_ctrl___keep_owner___bit 0
#define reg_iop_sw_cpu_rw_mc_ctrl___cmd___lsb 1
#define reg_iop_sw_cpu_rw_mc_ctrl___cmd___width 2
#define reg_iop_sw_cpu_rw_mc_ctrl___size___lsb 3
#define reg_iop_sw_cpu_rw_mc_ctrl___size___width 3
#define reg_iop_sw_cpu_rw_mc_ctrl___wr_spu_mem___lsb 6
#define reg_iop_sw_cpu_rw_mc_ctrl___wr_spu_mem___width 1
#define reg_iop_sw_cpu_rw_mc_ctrl___wr_spu_mem___bit 6
#define reg_iop_sw_cpu_rw_mc_ctrl_offset 12

/*                                                */
#define reg_iop_sw_cpu_rw_mc_data___val___lsb 0
#define reg_iop_sw_cpu_rw_mc_data___val___width 32
#define reg_iop_sw_cpu_rw_mc_data_offset 16

/*                                                */
#define reg_iop_sw_cpu_rw_mc_addr_offset 20

/*                                                */
#define reg_iop_sw_cpu_rs_mc_data_offset 24

/*                                              */
#define reg_iop_sw_cpu_r_mc_data_offset 28

/*                                              */
#define reg_iop_sw_cpu_r_mc_stat___busy_cpu___lsb 0
#define reg_iop_sw_cpu_r_mc_stat___busy_cpu___width 1
#define reg_iop_sw_cpu_r_mc_stat___busy_cpu___bit 0
#define reg_iop_sw_cpu_r_mc_stat___busy_mpu___lsb 1
#define reg_iop_sw_cpu_r_mc_stat___busy_mpu___width 1
#define reg_iop_sw_cpu_r_mc_stat___busy_mpu___bit 1
#define reg_iop_sw_cpu_r_mc_stat___busy_spu___lsb 2
#define reg_iop_sw_cpu_r_mc_stat___busy_spu___width 1
#define reg_iop_sw_cpu_r_mc_stat___busy_spu___bit 2
#define reg_iop_sw_cpu_r_mc_stat___owned_by_cpu___lsb 3
#define reg_iop_sw_cpu_r_mc_stat___owned_by_cpu___width 1
#define reg_iop_sw_cpu_r_mc_stat___owned_by_cpu___bit 3
#define reg_iop_sw_cpu_r_mc_stat___owned_by_mpu___lsb 4
#define reg_iop_sw_cpu_r_mc_stat___owned_by_mpu___width 1
#define reg_iop_sw_cpu_r_mc_stat___owned_by_mpu___bit 4
#define reg_iop_sw_cpu_r_mc_stat___owned_by_spu___lsb 5
#define reg_iop_sw_cpu_r_mc_stat___owned_by_spu___width 1
#define reg_iop_sw_cpu_r_mc_stat___owned_by_spu___bit 5
#define reg_iop_sw_cpu_r_mc_stat_offset 32

/*                                                     */
#define reg_iop_sw_cpu_rw_bus_clr_mask___byte0___lsb 0
#define reg_iop_sw_cpu_rw_bus_clr_mask___byte0___width 8
#define reg_iop_sw_cpu_rw_bus_clr_mask___byte1___lsb 8
#define reg_iop_sw_cpu_rw_bus_clr_mask___byte1___width 8
#define reg_iop_sw_cpu_rw_bus_clr_mask___byte2___lsb 16
#define reg_iop_sw_cpu_rw_bus_clr_mask___byte2___width 8
#define reg_iop_sw_cpu_rw_bus_clr_mask___byte3___lsb 24
#define reg_iop_sw_cpu_rw_bus_clr_mask___byte3___width 8
#define reg_iop_sw_cpu_rw_bus_clr_mask_offset 36

/*                                                     */
#define reg_iop_sw_cpu_rw_bus_set_mask___byte0___lsb 0
#define reg_iop_sw_cpu_rw_bus_set_mask___byte0___width 8
#define reg_iop_sw_cpu_rw_bus_set_mask___byte1___lsb 8
#define reg_iop_sw_cpu_rw_bus_set_mask___byte1___width 8
#define reg_iop_sw_cpu_rw_bus_set_mask___byte2___lsb 16
#define reg_iop_sw_cpu_rw_bus_set_mask___byte2___width 8
#define reg_iop_sw_cpu_rw_bus_set_mask___byte3___lsb 24
#define reg_iop_sw_cpu_rw_bus_set_mask___byte3___width 8
#define reg_iop_sw_cpu_rw_bus_set_mask_offset 40

/*                                                        */
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte0___lsb 0
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte0___width 1
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte0___bit 0
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte1___lsb 1
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte1___width 1
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte1___bit 1
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte2___lsb 2
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte2___width 1
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte2___bit 2
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte3___lsb 3
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte3___width 1
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask___byte3___bit 3
#define reg_iop_sw_cpu_rw_bus_oe_clr_mask_offset 44

/*                                                        */
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte0___lsb 0
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte0___width 1
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte0___bit 0
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte1___lsb 1
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte1___width 1
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte1___bit 1
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte2___lsb 2
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte2___width 1
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte2___bit 2
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte3___lsb 3
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte3___width 1
#define reg_iop_sw_cpu_rw_bus_oe_set_mask___byte3___bit 3
#define reg_iop_sw_cpu_rw_bus_oe_set_mask_offset 48

/*                                             */
#define reg_iop_sw_cpu_r_bus_in_offset 52

/*                                                     */
#define reg_iop_sw_cpu_rw_gio_clr_mask___val___lsb 0
#define reg_iop_sw_cpu_rw_gio_clr_mask___val___width 32
#define reg_iop_sw_cpu_rw_gio_clr_mask_offset 56

/*                                                     */
#define reg_iop_sw_cpu_rw_gio_set_mask___val___lsb 0
#define reg_iop_sw_cpu_rw_gio_set_mask___val___width 32
#define reg_iop_sw_cpu_rw_gio_set_mask_offset 60

/*                                                        */
#define reg_iop_sw_cpu_rw_gio_oe_clr_mask___val___lsb 0
#define reg_iop_sw_cpu_rw_gio_oe_clr_mask___val___width 32
#define reg_iop_sw_cpu_rw_gio_oe_clr_mask_offset 64

/*                                                        */
#define reg_iop_sw_cpu_rw_gio_oe_set_mask___val___lsb 0
#define reg_iop_sw_cpu_rw_gio_oe_set_mask___val___width 32
#define reg_iop_sw_cpu_rw_gio_oe_set_mask_offset 68

/*                                             */
#define reg_iop_sw_cpu_r_gio_in_offset 72

/*                                                   */
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_0___lsb 0
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_0___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_0___bit 0
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_1___lsb 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_1___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_1___bit 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_2___lsb 2
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_2___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_2___bit 2
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_3___lsb 3
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_3___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_3___bit 3
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_4___lsb 4
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_4___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_4___bit 4
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_5___lsb 5
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_5___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_5___bit 5
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_6___lsb 6
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_6___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_6___bit 6
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_7___lsb 7
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_7___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_7___bit 7
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_8___lsb 8
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_8___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_8___bit 8
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_9___lsb 9
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_9___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_9___bit 9
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_10___lsb 10
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_10___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_10___bit 10
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_11___lsb 11
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_11___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_11___bit 11
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_12___lsb 12
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_12___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_12___bit 12
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_13___lsb 13
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_13___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_13___bit 13
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_14___lsb 14
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_14___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_14___bit 14
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_15___lsb 15
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_15___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___mpu_15___bit 15
#define reg_iop_sw_cpu_rw_intr0_mask___spu_0___lsb 16
#define reg_iop_sw_cpu_rw_intr0_mask___spu_0___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_0___bit 16
#define reg_iop_sw_cpu_rw_intr0_mask___spu_1___lsb 17
#define reg_iop_sw_cpu_rw_intr0_mask___spu_1___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_1___bit 17
#define reg_iop_sw_cpu_rw_intr0_mask___spu_2___lsb 18
#define reg_iop_sw_cpu_rw_intr0_mask___spu_2___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_2___bit 18
#define reg_iop_sw_cpu_rw_intr0_mask___spu_3___lsb 19
#define reg_iop_sw_cpu_rw_intr0_mask___spu_3___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_3___bit 19
#define reg_iop_sw_cpu_rw_intr0_mask___spu_4___lsb 20
#define reg_iop_sw_cpu_rw_intr0_mask___spu_4___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_4___bit 20
#define reg_iop_sw_cpu_rw_intr0_mask___spu_5___lsb 21
#define reg_iop_sw_cpu_rw_intr0_mask___spu_5___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_5___bit 21
#define reg_iop_sw_cpu_rw_intr0_mask___spu_6___lsb 22
#define reg_iop_sw_cpu_rw_intr0_mask___spu_6___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_6___bit 22
#define reg_iop_sw_cpu_rw_intr0_mask___spu_7___lsb 23
#define reg_iop_sw_cpu_rw_intr0_mask___spu_7___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_7___bit 23
#define reg_iop_sw_cpu_rw_intr0_mask___spu_8___lsb 24
#define reg_iop_sw_cpu_rw_intr0_mask___spu_8___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_8___bit 24
#define reg_iop_sw_cpu_rw_intr0_mask___spu_9___lsb 25
#define reg_iop_sw_cpu_rw_intr0_mask___spu_9___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_9___bit 25
#define reg_iop_sw_cpu_rw_intr0_mask___spu_10___lsb 26
#define reg_iop_sw_cpu_rw_intr0_mask___spu_10___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_10___bit 26
#define reg_iop_sw_cpu_rw_intr0_mask___spu_11___lsb 27
#define reg_iop_sw_cpu_rw_intr0_mask___spu_11___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_11___bit 27
#define reg_iop_sw_cpu_rw_intr0_mask___spu_12___lsb 28
#define reg_iop_sw_cpu_rw_intr0_mask___spu_12___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_12___bit 28
#define reg_iop_sw_cpu_rw_intr0_mask___spu_13___lsb 29
#define reg_iop_sw_cpu_rw_intr0_mask___spu_13___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_13___bit 29
#define reg_iop_sw_cpu_rw_intr0_mask___spu_14___lsb 30
#define reg_iop_sw_cpu_rw_intr0_mask___spu_14___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_14___bit 30
#define reg_iop_sw_cpu_rw_intr0_mask___spu_15___lsb 31
#define reg_iop_sw_cpu_rw_intr0_mask___spu_15___width 1
#define reg_iop_sw_cpu_rw_intr0_mask___spu_15___bit 31
#define reg_iop_sw_cpu_rw_intr0_mask_offset 76

/*                                                  */
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_0___lsb 0
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_0___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_0___bit 0
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_1___lsb 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_1___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_1___bit 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_2___lsb 2
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_2___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_2___bit 2
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_3___lsb 3
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_3___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_3___bit 3
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_4___lsb 4
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_4___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_4___bit 4
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_5___lsb 5
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_5___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_5___bit 5
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_6___lsb 6
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_6___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_6___bit 6
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_7___lsb 7
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_7___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_7___bit 7
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_8___lsb 8
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_8___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_8___bit 8
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_9___lsb 9
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_9___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_9___bit 9
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_10___lsb 10
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_10___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_10___bit 10
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_11___lsb 11
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_11___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_11___bit 11
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_12___lsb 12
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_12___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_12___bit 12
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_13___lsb 13
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_13___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_13___bit 13
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_14___lsb 14
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_14___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_14___bit 14
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_15___lsb 15
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_15___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___mpu_15___bit 15
#define reg_iop_sw_cpu_rw_ack_intr0___spu_0___lsb 16
#define reg_iop_sw_cpu_rw_ack_intr0___spu_0___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_0___bit 16
#define reg_iop_sw_cpu_rw_ack_intr0___spu_1___lsb 17
#define reg_iop_sw_cpu_rw_ack_intr0___spu_1___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_1___bit 17
#define reg_iop_sw_cpu_rw_ack_intr0___spu_2___lsb 18
#define reg_iop_sw_cpu_rw_ack_intr0___spu_2___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_2___bit 18
#define reg_iop_sw_cpu_rw_ack_intr0___spu_3___lsb 19
#define reg_iop_sw_cpu_rw_ack_intr0___spu_3___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_3___bit 19
#define reg_iop_sw_cpu_rw_ack_intr0___spu_4___lsb 20
#define reg_iop_sw_cpu_rw_ack_intr0___spu_4___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_4___bit 20
#define reg_iop_sw_cpu_rw_ack_intr0___spu_5___lsb 21
#define reg_iop_sw_cpu_rw_ack_intr0___spu_5___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_5___bit 21
#define reg_iop_sw_cpu_rw_ack_intr0___spu_6___lsb 22
#define reg_iop_sw_cpu_rw_ack_intr0___spu_6___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_6___bit 22
#define reg_iop_sw_cpu_rw_ack_intr0___spu_7___lsb 23
#define reg_iop_sw_cpu_rw_ack_intr0___spu_7___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_7___bit 23
#define reg_iop_sw_cpu_rw_ack_intr0___spu_8___lsb 24
#define reg_iop_sw_cpu_rw_ack_intr0___spu_8___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_8___bit 24
#define reg_iop_sw_cpu_rw_ack_intr0___spu_9___lsb 25
#define reg_iop_sw_cpu_rw_ack_intr0___spu_9___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_9___bit 25
#define reg_iop_sw_cpu_rw_ack_intr0___spu_10___lsb 26
#define reg_iop_sw_cpu_rw_ack_intr0___spu_10___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_10___bit 26
#define reg_iop_sw_cpu_rw_ack_intr0___spu_11___lsb 27
#define reg_iop_sw_cpu_rw_ack_intr0___spu_11___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_11___bit 27
#define reg_iop_sw_cpu_rw_ack_intr0___spu_12___lsb 28
#define reg_iop_sw_cpu_rw_ack_intr0___spu_12___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_12___bit 28
#define reg_iop_sw_cpu_rw_ack_intr0___spu_13___lsb 29
#define reg_iop_sw_cpu_rw_ack_intr0___spu_13___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_13___bit 29
#define reg_iop_sw_cpu_rw_ack_intr0___spu_14___lsb 30
#define reg_iop_sw_cpu_rw_ack_intr0___spu_14___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_14___bit 30
#define reg_iop_sw_cpu_rw_ack_intr0___spu_15___lsb 31
#define reg_iop_sw_cpu_rw_ack_intr0___spu_15___width 1
#define reg_iop_sw_cpu_rw_ack_intr0___spu_15___bit 31
#define reg_iop_sw_cpu_rw_ack_intr0_offset 80

/*                                            */
#define reg_iop_sw_cpu_r_intr0___mpu_0___lsb 0
#define reg_iop_sw_cpu_r_intr0___mpu_0___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_0___bit 0
#define reg_iop_sw_cpu_r_intr0___mpu_1___lsb 1
#define reg_iop_sw_cpu_r_intr0___mpu_1___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_1___bit 1
#define reg_iop_sw_cpu_r_intr0___mpu_2___lsb 2
#define reg_iop_sw_cpu_r_intr0___mpu_2___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_2___bit 2
#define reg_iop_sw_cpu_r_intr0___mpu_3___lsb 3
#define reg_iop_sw_cpu_r_intr0___mpu_3___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_3___bit 3
#define reg_iop_sw_cpu_r_intr0___mpu_4___lsb 4
#define reg_iop_sw_cpu_r_intr0___mpu_4___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_4___bit 4
#define reg_iop_sw_cpu_r_intr0___mpu_5___lsb 5
#define reg_iop_sw_cpu_r_intr0___mpu_5___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_5___bit 5
#define reg_iop_sw_cpu_r_intr0___mpu_6___lsb 6
#define reg_iop_sw_cpu_r_intr0___mpu_6___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_6___bit 6
#define reg_iop_sw_cpu_r_intr0___mpu_7___lsb 7
#define reg_iop_sw_cpu_r_intr0___mpu_7___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_7___bit 7
#define reg_iop_sw_cpu_r_intr0___mpu_8___lsb 8
#define reg_iop_sw_cpu_r_intr0___mpu_8___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_8___bit 8
#define reg_iop_sw_cpu_r_intr0___mpu_9___lsb 9
#define reg_iop_sw_cpu_r_intr0___mpu_9___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_9___bit 9
#define reg_iop_sw_cpu_r_intr0___mpu_10___lsb 10
#define reg_iop_sw_cpu_r_intr0___mpu_10___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_10___bit 10
#define reg_iop_sw_cpu_r_intr0___mpu_11___lsb 11
#define reg_iop_sw_cpu_r_intr0___mpu_11___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_11___bit 11
#define reg_iop_sw_cpu_r_intr0___mpu_12___lsb 12
#define reg_iop_sw_cpu_r_intr0___mpu_12___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_12___bit 12
#define reg_iop_sw_cpu_r_intr0___mpu_13___lsb 13
#define reg_iop_sw_cpu_r_intr0___mpu_13___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_13___bit 13
#define reg_iop_sw_cpu_r_intr0___mpu_14___lsb 14
#define reg_iop_sw_cpu_r_intr0___mpu_14___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_14___bit 14
#define reg_iop_sw_cpu_r_intr0___mpu_15___lsb 15
#define reg_iop_sw_cpu_r_intr0___mpu_15___width 1
#define reg_iop_sw_cpu_r_intr0___mpu_15___bit 15
#define reg_iop_sw_cpu_r_intr0___spu_0___lsb 16
#define reg_iop_sw_cpu_r_intr0___spu_0___width 1
#define reg_iop_sw_cpu_r_intr0___spu_0___bit 16
#define reg_iop_sw_cpu_r_intr0___spu_1___lsb 17
#define reg_iop_sw_cpu_r_intr0___spu_1___width 1
#define reg_iop_sw_cpu_r_intr0___spu_1___bit 17
#define reg_iop_sw_cpu_r_intr0___spu_2___lsb 18
#define reg_iop_sw_cpu_r_intr0___spu_2___width 1
#define reg_iop_sw_cpu_r_intr0___spu_2___bit 18
#define reg_iop_sw_cpu_r_intr0___spu_3___lsb 19
#define reg_iop_sw_cpu_r_intr0___spu_3___width 1
#define reg_iop_sw_cpu_r_intr0___spu_3___bit 19
#define reg_iop_sw_cpu_r_intr0___spu_4___lsb 20
#define reg_iop_sw_cpu_r_intr0___spu_4___width 1
#define reg_iop_sw_cpu_r_intr0___spu_4___bit 20
#define reg_iop_sw_cpu_r_intr0___spu_5___lsb 21
#define reg_iop_sw_cpu_r_intr0___spu_5___width 1
#define reg_iop_sw_cpu_r_intr0___spu_5___bit 21
#define reg_iop_sw_cpu_r_intr0___spu_6___lsb 22
#define reg_iop_sw_cpu_r_intr0___spu_6___width 1
#define reg_iop_sw_cpu_r_intr0___spu_6___bit 22
#define reg_iop_sw_cpu_r_intr0___spu_7___lsb 23
#define reg_iop_sw_cpu_r_intr0___spu_7___width 1
#define reg_iop_sw_cpu_r_intr0___spu_7___bit 23
#define reg_iop_sw_cpu_r_intr0___spu_8___lsb 24
#define reg_iop_sw_cpu_r_intr0___spu_8___width 1
#define reg_iop_sw_cpu_r_intr0___spu_8___bit 24
#define reg_iop_sw_cpu_r_intr0___spu_9___lsb 25
#define reg_iop_sw_cpu_r_intr0___spu_9___width 1
#define reg_iop_sw_cpu_r_intr0___spu_9___bit 25
#define reg_iop_sw_cpu_r_intr0___spu_10___lsb 26
#define reg_iop_sw_cpu_r_intr0___spu_10___width 1
#define reg_iop_sw_cpu_r_intr0___spu_10___bit 26
#define reg_iop_sw_cpu_r_intr0___spu_11___lsb 27
#define reg_iop_sw_cpu_r_intr0___spu_11___width 1
#define reg_iop_sw_cpu_r_intr0___spu_11___bit 27
#define reg_iop_sw_cpu_r_intr0___spu_12___lsb 28
#define reg_iop_sw_cpu_r_intr0___spu_12___width 1
#define reg_iop_sw_cpu_r_intr0___spu_12___bit 28
#define reg_iop_sw_cpu_r_intr0___spu_13___lsb 29
#define reg_iop_sw_cpu_r_intr0___spu_13___width 1
#define reg_iop_sw_cpu_r_intr0___spu_13___bit 29
#define reg_iop_sw_cpu_r_intr0___spu_14___lsb 30
#define reg_iop_sw_cpu_r_intr0___spu_14___width 1
#define reg_iop_sw_cpu_r_intr0___spu_14___bit 30
#define reg_iop_sw_cpu_r_intr0___spu_15___lsb 31
#define reg_iop_sw_cpu_r_intr0___spu_15___width 1
#define reg_iop_sw_cpu_r_intr0___spu_15___bit 31
#define reg_iop_sw_cpu_r_intr0_offset 84

/*                                                   */
#define reg_iop_sw_cpu_r_masked_intr0___mpu_0___lsb 0
#define reg_iop_sw_cpu_r_masked_intr0___mpu_0___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_0___bit 0
#define reg_iop_sw_cpu_r_masked_intr0___mpu_1___lsb 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_1___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_1___bit 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_2___lsb 2
#define reg_iop_sw_cpu_r_masked_intr0___mpu_2___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_2___bit 2
#define reg_iop_sw_cpu_r_masked_intr0___mpu_3___lsb 3
#define reg_iop_sw_cpu_r_masked_intr0___mpu_3___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_3___bit 3
#define reg_iop_sw_cpu_r_masked_intr0___mpu_4___lsb 4
#define reg_iop_sw_cpu_r_masked_intr0___mpu_4___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_4___bit 4
#define reg_iop_sw_cpu_r_masked_intr0___mpu_5___lsb 5
#define reg_iop_sw_cpu_r_masked_intr0___mpu_5___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_5___bit 5
#define reg_iop_sw_cpu_r_masked_intr0___mpu_6___lsb 6
#define reg_iop_sw_cpu_r_masked_intr0___mpu_6___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_6___bit 6
#define reg_iop_sw_cpu_r_masked_intr0___mpu_7___lsb 7
#define reg_iop_sw_cpu_r_masked_intr0___mpu_7___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_7___bit 7
#define reg_iop_sw_cpu_r_masked_intr0___mpu_8___lsb 8
#define reg_iop_sw_cpu_r_masked_intr0___mpu_8___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_8___bit 8
#define reg_iop_sw_cpu_r_masked_intr0___mpu_9___lsb 9
#define reg_iop_sw_cpu_r_masked_intr0___mpu_9___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_9___bit 9
#define reg_iop_sw_cpu_r_masked_intr0___mpu_10___lsb 10
#define reg_iop_sw_cpu_r_masked_intr0___mpu_10___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_10___bit 10
#define reg_iop_sw_cpu_r_masked_intr0___mpu_11___lsb 11
#define reg_iop_sw_cpu_r_masked_intr0___mpu_11___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_11___bit 11
#define reg_iop_sw_cpu_r_masked_intr0___mpu_12___lsb 12
#define reg_iop_sw_cpu_r_masked_intr0___mpu_12___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_12___bit 12
#define reg_iop_sw_cpu_r_masked_intr0___mpu_13___lsb 13
#define reg_iop_sw_cpu_r_masked_intr0___mpu_13___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_13___bit 13
#define reg_iop_sw_cpu_r_masked_intr0___mpu_14___lsb 14
#define reg_iop_sw_cpu_r_masked_intr0___mpu_14___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_14___bit 14
#define reg_iop_sw_cpu_r_masked_intr0___mpu_15___lsb 15
#define reg_iop_sw_cpu_r_masked_intr0___mpu_15___width 1
#define reg_iop_sw_cpu_r_masked_intr0___mpu_15___bit 15
#define reg_iop_sw_cpu_r_masked_intr0___spu_0___lsb 16
#define reg_iop_sw_cpu_r_masked_intr0___spu_0___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_0___bit 16
#define reg_iop_sw_cpu_r_masked_intr0___spu_1___lsb 17
#define reg_iop_sw_cpu_r_masked_intr0___spu_1___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_1___bit 17
#define reg_iop_sw_cpu_r_masked_intr0___spu_2___lsb 18
#define reg_iop_sw_cpu_r_masked_intr0___spu_2___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_2___bit 18
#define reg_iop_sw_cpu_r_masked_intr0___spu_3___lsb 19
#define reg_iop_sw_cpu_r_masked_intr0___spu_3___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_3___bit 19
#define reg_iop_sw_cpu_r_masked_intr0___spu_4___lsb 20
#define reg_iop_sw_cpu_r_masked_intr0___spu_4___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_4___bit 20
#define reg_iop_sw_cpu_r_masked_intr0___spu_5___lsb 21
#define reg_iop_sw_cpu_r_masked_intr0___spu_5___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_5___bit 21
#define reg_iop_sw_cpu_r_masked_intr0___spu_6___lsb 22
#define reg_iop_sw_cpu_r_masked_intr0___spu_6___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_6___bit 22
#define reg_iop_sw_cpu_r_masked_intr0___spu_7___lsb 23
#define reg_iop_sw_cpu_r_masked_intr0___spu_7___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_7___bit 23
#define reg_iop_sw_cpu_r_masked_intr0___spu_8___lsb 24
#define reg_iop_sw_cpu_r_masked_intr0___spu_8___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_8___bit 24
#define reg_iop_sw_cpu_r_masked_intr0___spu_9___lsb 25
#define reg_iop_sw_cpu_r_masked_intr0___spu_9___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_9___bit 25
#define reg_iop_sw_cpu_r_masked_intr0___spu_10___lsb 26
#define reg_iop_sw_cpu_r_masked_intr0___spu_10___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_10___bit 26
#define reg_iop_sw_cpu_r_masked_intr0___spu_11___lsb 27
#define reg_iop_sw_cpu_r_masked_intr0___spu_11___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_11___bit 27
#define reg_iop_sw_cpu_r_masked_intr0___spu_12___lsb 28
#define reg_iop_sw_cpu_r_masked_intr0___spu_12___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_12___bit 28
#define reg_iop_sw_cpu_r_masked_intr0___spu_13___lsb 29
#define reg_iop_sw_cpu_r_masked_intr0___spu_13___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_13___bit 29
#define reg_iop_sw_cpu_r_masked_intr0___spu_14___lsb 30
#define reg_iop_sw_cpu_r_masked_intr0___spu_14___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_14___bit 30
#define reg_iop_sw_cpu_r_masked_intr0___spu_15___lsb 31
#define reg_iop_sw_cpu_r_masked_intr0___spu_15___width 1
#define reg_iop_sw_cpu_r_masked_intr0___spu_15___bit 31
#define reg_iop_sw_cpu_r_masked_intr0_offset 88

/*                                                   */
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_16___lsb 0
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_16___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_16___bit 0
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_17___lsb 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_17___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_17___bit 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_18___lsb 2
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_18___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_18___bit 2
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_19___lsb 3
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_19___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_19___bit 3
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_20___lsb 4
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_20___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_20___bit 4
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_21___lsb 5
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_21___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_21___bit 5
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_22___lsb 6
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_22___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_22___bit 6
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_23___lsb 7
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_23___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_23___bit 7
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_24___lsb 8
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_24___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_24___bit 8
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_25___lsb 9
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_25___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_25___bit 9
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_26___lsb 10
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_26___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_26___bit 10
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_27___lsb 11
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_27___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_27___bit 11
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_28___lsb 12
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_28___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_28___bit 12
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_29___lsb 13
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_29___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_29___bit 13
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_30___lsb 14
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_30___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_30___bit 14
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_31___lsb 15
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_31___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___mpu_31___bit 15
#define reg_iop_sw_cpu_rw_intr1_mask___dmc_in___lsb 16
#define reg_iop_sw_cpu_rw_intr1_mask___dmc_in___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___dmc_in___bit 16
#define reg_iop_sw_cpu_rw_intr1_mask___dmc_out___lsb 17
#define reg_iop_sw_cpu_rw_intr1_mask___dmc_out___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___dmc_out___bit 17
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_in___lsb 18
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_in___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_in___bit 18
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_out___lsb 19
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_out___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_out___bit 19
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_in_extra___lsb 20
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_in_extra___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_in_extra___bit 20
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_out_extra___lsb 21
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_out_extra___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___fifo_out_extra___bit 21
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp0___lsb 22
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp0___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp0___bit 22
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp1___lsb 23
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp1___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp1___bit 23
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp2___lsb 24
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp2___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp2___bit 24
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp3___lsb 25
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp3___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp3___bit 25
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp4___lsb 26
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp4___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp4___bit 26
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp5___lsb 27
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp5___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp5___bit 27
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp6___lsb 28
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp6___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp6___bit 28
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp7___lsb 29
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp7___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___trigger_grp7___bit 29
#define reg_iop_sw_cpu_rw_intr1_mask___timer_grp0___lsb 30
#define reg_iop_sw_cpu_rw_intr1_mask___timer_grp0___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___timer_grp0___bit 30
#define reg_iop_sw_cpu_rw_intr1_mask___timer_grp1___lsb 31
#define reg_iop_sw_cpu_rw_intr1_mask___timer_grp1___width 1
#define reg_iop_sw_cpu_rw_intr1_mask___timer_grp1___bit 31
#define reg_iop_sw_cpu_rw_intr1_mask_offset 92

/*                                                  */
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_16___lsb 0
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_16___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_16___bit 0
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_17___lsb 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_17___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_17___bit 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_18___lsb 2
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_18___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_18___bit 2
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_19___lsb 3
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_19___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_19___bit 3
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_20___lsb 4
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_20___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_20___bit 4
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_21___lsb 5
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_21___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_21___bit 5
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_22___lsb 6
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_22___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_22___bit 6
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_23___lsb 7
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_23___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_23___bit 7
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_24___lsb 8
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_24___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_24___bit 8
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_25___lsb 9
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_25___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_25___bit 9
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_26___lsb 10
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_26___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_26___bit 10
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_27___lsb 11
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_27___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_27___bit 11
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_28___lsb 12
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_28___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_28___bit 12
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_29___lsb 13
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_29___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_29___bit 13
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_30___lsb 14
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_30___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_30___bit 14
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_31___lsb 15
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_31___width 1
#define reg_iop_sw_cpu_rw_ack_intr1___mpu_31___bit 15
#define reg_iop_sw_cpu_rw_ack_intr1_offset 96

/*                                            */
#define reg_iop_sw_cpu_r_intr1___mpu_16___lsb 0
#define reg_iop_sw_cpu_r_intr1___mpu_16___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_16___bit 0
#define reg_iop_sw_cpu_r_intr1___mpu_17___lsb 1
#define reg_iop_sw_cpu_r_intr1___mpu_17___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_17___bit 1
#define reg_iop_sw_cpu_r_intr1___mpu_18___lsb 2
#define reg_iop_sw_cpu_r_intr1___mpu_18___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_18___bit 2
#define reg_iop_sw_cpu_r_intr1___mpu_19___lsb 3
#define reg_iop_sw_cpu_r_intr1___mpu_19___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_19___bit 3
#define reg_iop_sw_cpu_r_intr1___mpu_20___lsb 4
#define reg_iop_sw_cpu_r_intr1___mpu_20___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_20___bit 4
#define reg_iop_sw_cpu_r_intr1___mpu_21___lsb 5
#define reg_iop_sw_cpu_r_intr1___mpu_21___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_21___bit 5
#define reg_iop_sw_cpu_r_intr1___mpu_22___lsb 6
#define reg_iop_sw_cpu_r_intr1___mpu_22___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_22___bit 6
#define reg_iop_sw_cpu_r_intr1___mpu_23___lsb 7
#define reg_iop_sw_cpu_r_intr1___mpu_23___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_23___bit 7
#define reg_iop_sw_cpu_r_intr1___mpu_24___lsb 8
#define reg_iop_sw_cpu_r_intr1___mpu_24___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_24___bit 8
#define reg_iop_sw_cpu_r_intr1___mpu_25___lsb 9
#define reg_iop_sw_cpu_r_intr1___mpu_25___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_25___bit 9
#define reg_iop_sw_cpu_r_intr1___mpu_26___lsb 10
#define reg_iop_sw_cpu_r_intr1___mpu_26___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_26___bit 10
#define reg_iop_sw_cpu_r_intr1___mpu_27___lsb 11
#define reg_iop_sw_cpu_r_intr1___mpu_27___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_27___bit 11
#define reg_iop_sw_cpu_r_intr1___mpu_28___lsb 12
#define reg_iop_sw_cpu_r_intr1___mpu_28___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_28___bit 12
#define reg_iop_sw_cpu_r_intr1___mpu_29___lsb 13
#define reg_iop_sw_cpu_r_intr1___mpu_29___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_29___bit 13
#define reg_iop_sw_cpu_r_intr1___mpu_30___lsb 14
#define reg_iop_sw_cpu_r_intr1___mpu_30___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_30___bit 14
#define reg_iop_sw_cpu_r_intr1___mpu_31___lsb 15
#define reg_iop_sw_cpu_r_intr1___mpu_31___width 1
#define reg_iop_sw_cpu_r_intr1___mpu_31___bit 15
#define reg_iop_sw_cpu_r_intr1___dmc_in___lsb 16
#define reg_iop_sw_cpu_r_intr1___dmc_in___width 1
#define reg_iop_sw_cpu_r_intr1___dmc_in___bit 16
#define reg_iop_sw_cpu_r_intr1___dmc_out___lsb 17
#define reg_iop_sw_cpu_r_intr1___dmc_out___width 1
#define reg_iop_sw_cpu_r_intr1___dmc_out___bit 17
#define reg_iop_sw_cpu_r_intr1___fifo_in___lsb 18
#define reg_iop_sw_cpu_r_intr1___fifo_in___width 1
#define reg_iop_sw_cpu_r_intr1___fifo_in___bit 18
#define reg_iop_sw_cpu_r_intr1___fifo_out___lsb 19
#define reg_iop_sw_cpu_r_intr1___fifo_out___width 1
#define reg_iop_sw_cpu_r_intr1___fifo_out___bit 19
#define reg_iop_sw_cpu_r_intr1___fifo_in_extra___lsb 20
#define reg_iop_sw_cpu_r_intr1___fifo_in_extra___width 1
#define reg_iop_sw_cpu_r_intr1___fifo_in_extra___bit 20
#define reg_iop_sw_cpu_r_intr1___fifo_out_extra___lsb 21
#define reg_iop_sw_cpu_r_intr1___fifo_out_extra___width 1
#define reg_iop_sw_cpu_r_intr1___fifo_out_extra___bit 21
#define reg_iop_sw_cpu_r_intr1___trigger_grp0___lsb 22
#define reg_iop_sw_cpu_r_intr1___trigger_grp0___width 1
#define reg_iop_sw_cpu_r_intr1___trigger_grp0___bit 22
#define reg_iop_sw_cpu_r_intr1___trigger_grp1___lsb 23
#define reg_iop_sw_cpu_r_intr1___trigger_grp1___width 1
#define reg_iop_sw_cpu_r_intr1___trigger_grp1___bit 23
#define reg_iop_sw_cpu_r_intr1___trigger_grp2___lsb 24
#define reg_iop_sw_cpu_r_intr1___trigger_grp2___width 1
#define reg_iop_sw_cpu_r_intr1___trigger_grp2___bit 24
#define reg_iop_sw_cpu_r_intr1___trigger_grp3___lsb 25
#define reg_iop_sw_cpu_r_intr1___trigger_grp3___width 1
#define reg_iop_sw_cpu_r_intr1___trigger_grp3___bit 25
#define reg_iop_sw_cpu_r_intr1___trigger_grp4___lsb 26
#define reg_iop_sw_cpu_r_intr1___trigger_grp4___width 1
#define reg_iop_sw_cpu_r_intr1___trigger_grp4___bit 26
#define reg_iop_sw_cpu_r_intr1___trigger_grp5___lsb 27
#define reg_iop_sw_cpu_r_intr1___trigger_grp5___width 1
#define reg_iop_sw_cpu_r_intr1___trigger_grp5___bit 27
#define reg_iop_sw_cpu_r_intr1___trigger_grp6___lsb 28
#define reg_iop_sw_cpu_r_intr1___trigger_grp6___width 1
#define reg_iop_sw_cpu_r_intr1___trigger_grp6___bit 28
#define reg_iop_sw_cpu_r_intr1___trigger_grp7___lsb 29
#define reg_iop_sw_cpu_r_intr1___trigger_grp7___width 1
#define reg_iop_sw_cpu_r_intr1___trigger_grp7___bit 29
#define reg_iop_sw_cpu_r_intr1___timer_grp0___lsb 30
#define reg_iop_sw_cpu_r_intr1___timer_grp0___width 1
#define reg_iop_sw_cpu_r_intr1___timer_grp0___bit 30
#define reg_iop_sw_cpu_r_intr1___timer_grp1___lsb 31
#define reg_iop_sw_cpu_r_intr1___timer_grp1___width 1
#define reg_iop_sw_cpu_r_intr1___timer_grp1___bit 31
#define reg_iop_sw_cpu_r_intr1_offset 100

/*                                                   */
#define reg_iop_sw_cpu_r_masked_intr1___mpu_16___lsb 0
#define reg_iop_sw_cpu_r_masked_intr1___mpu_16___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_16___bit 0
#define reg_iop_sw_cpu_r_masked_intr1___mpu_17___lsb 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_17___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_17___bit 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_18___lsb 2
#define reg_iop_sw_cpu_r_masked_intr1___mpu_18___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_18___bit 2
#define reg_iop_sw_cpu_r_masked_intr1___mpu_19___lsb 3
#define reg_iop_sw_cpu_r_masked_intr1___mpu_19___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_19___bit 3
#define reg_iop_sw_cpu_r_masked_intr1___mpu_20___lsb 4
#define reg_iop_sw_cpu_r_masked_intr1___mpu_20___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_20___bit 4
#define reg_iop_sw_cpu_r_masked_intr1___mpu_21___lsb 5
#define reg_iop_sw_cpu_r_masked_intr1___mpu_21___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_21___bit 5
#define reg_iop_sw_cpu_r_masked_intr1___mpu_22___lsb 6
#define reg_iop_sw_cpu_r_masked_intr1___mpu_22___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_22___bit 6
#define reg_iop_sw_cpu_r_masked_intr1___mpu_23___lsb 7
#define reg_iop_sw_cpu_r_masked_intr1___mpu_23___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_23___bit 7
#define reg_iop_sw_cpu_r_masked_intr1___mpu_24___lsb 8
#define reg_iop_sw_cpu_r_masked_intr1___mpu_24___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_24___bit 8
#define reg_iop_sw_cpu_r_masked_intr1___mpu_25___lsb 9
#define reg_iop_sw_cpu_r_masked_intr1___mpu_25___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_25___bit 9
#define reg_iop_sw_cpu_r_masked_intr1___mpu_26___lsb 10
#define reg_iop_sw_cpu_r_masked_intr1___mpu_26___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_26___bit 10
#define reg_iop_sw_cpu_r_masked_intr1___mpu_27___lsb 11
#define reg_iop_sw_cpu_r_masked_intr1___mpu_27___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_27___bit 11
#define reg_iop_sw_cpu_r_masked_intr1___mpu_28___lsb 12
#define reg_iop_sw_cpu_r_masked_intr1___mpu_28___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_28___bit 12
#define reg_iop_sw_cpu_r_masked_intr1___mpu_29___lsb 13
#define reg_iop_sw_cpu_r_masked_intr1___mpu_29___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_29___bit 13
#define reg_iop_sw_cpu_r_masked_intr1___mpu_30___lsb 14
#define reg_iop_sw_cpu_r_masked_intr1___mpu_30___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_30___bit 14
#define reg_iop_sw_cpu_r_masked_intr1___mpu_31___lsb 15
#define reg_iop_sw_cpu_r_masked_intr1___mpu_31___width 1
#define reg_iop_sw_cpu_r_masked_intr1___mpu_31___bit 15
#define reg_iop_sw_cpu_r_masked_intr1___dmc_in___lsb 16
#define reg_iop_sw_cpu_r_masked_intr1___dmc_in___width 1
#define reg_iop_sw_cpu_r_masked_intr1___dmc_in___bit 16
#define reg_iop_sw_cpu_r_masked_intr1___dmc_out___lsb 17
#define reg_iop_sw_cpu_r_masked_intr1___dmc_out___width 1
#define reg_iop_sw_cpu_r_masked_intr1___dmc_out___bit 17
#define reg_iop_sw_cpu_r_masked_intr1___fifo_in___lsb 18
#define reg_iop_sw_cpu_r_masked_intr1___fifo_in___width 1
#define reg_iop_sw_cpu_r_masked_intr1___fifo_in___bit 18
#define reg_iop_sw_cpu_r_masked_intr1___fifo_out___lsb 19
#define reg_iop_sw_cpu_r_masked_intr1___fifo_out___width 1
#define reg_iop_sw_cpu_r_masked_intr1___fifo_out___bit 19
#define reg_iop_sw_cpu_r_masked_intr1___fifo_in_extra___lsb 20
#define reg_iop_sw_cpu_r_masked_intr1___fifo_in_extra___width 1
#define reg_iop_sw_cpu_r_masked_intr1___fifo_in_extra___bit 20
#define reg_iop_sw_cpu_r_masked_intr1___fifo_out_extra___lsb 21
#define reg_iop_sw_cpu_r_masked_intr1___fifo_out_extra___width 1
#define reg_iop_sw_cpu_r_masked_intr1___fifo_out_extra___bit 21
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp0___lsb 22
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp0___width 1
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp0___bit 22
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp1___lsb 23
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp1___width 1
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp1___bit 23
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp2___lsb 24
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp2___width 1
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp2___bit 24
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp3___lsb 25
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp3___width 1
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp3___bit 25
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp4___lsb 26
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp4___width 1
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp4___bit 26
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp5___lsb 27
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp5___width 1
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp5___bit 27
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp6___lsb 28
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp6___width 1
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp6___bit 28
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp7___lsb 29
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp7___width 1
#define reg_iop_sw_cpu_r_masked_intr1___trigger_grp7___bit 29
#define reg_iop_sw_cpu_r_masked_intr1___timer_grp0___lsb 30
#define reg_iop_sw_cpu_r_masked_intr1___timer_grp0___width 1
#define reg_iop_sw_cpu_r_masked_intr1___timer_grp0___bit 30
#define reg_iop_sw_cpu_r_masked_intr1___timer_grp1___lsb 31
#define reg_iop_sw_cpu_r_masked_intr1___timer_grp1___width 1
#define reg_iop_sw_cpu_r_masked_intr1___timer_grp1___bit 31
#define reg_iop_sw_cpu_r_masked_intr1_offset 104


/*           */
#define regk_iop_sw_cpu_copy                      0x00000000
#define regk_iop_sw_cpu_no                        0x00000000
#define regk_iop_sw_cpu_rd                        0x00000002
#define regk_iop_sw_cpu_reg_copy                  0x00000001
#define regk_iop_sw_cpu_rw_bus_clr_mask_default   0x00000000
#define regk_iop_sw_cpu_rw_bus_oe_clr_mask_default  0x00000000
#define regk_iop_sw_cpu_rw_bus_oe_set_mask_default  0x00000000
#define regk_iop_sw_cpu_rw_bus_set_mask_default   0x00000000
#define regk_iop_sw_cpu_rw_gio_clr_mask_default   0x00000000
#define regk_iop_sw_cpu_rw_gio_oe_clr_mask_default  0x00000000
#define regk_iop_sw_cpu_rw_gio_oe_set_mask_default  0x00000000
#define regk_iop_sw_cpu_rw_gio_set_mask_default   0x00000000
#define regk_iop_sw_cpu_rw_intr0_mask_default     0x00000000
#define regk_iop_sw_cpu_rw_intr1_mask_default     0x00000000
#define regk_iop_sw_cpu_wr                        0x00000003
#define regk_iop_sw_cpu_yes                       0x00000001
#endif /*                         */
