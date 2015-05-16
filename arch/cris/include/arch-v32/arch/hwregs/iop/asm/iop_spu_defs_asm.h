#ifndef __iop_spu_defs_asm_h
#define __iop_spu_defs_asm_h

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

#define STRIDE_iop_spu_rw_r 4
/*                                       */
#define reg_iop_spu_rw_r_offset 0

/*                                            */
#define reg_iop_spu_rw_seq_pc___addr___lsb 0
#define reg_iop_spu_rw_seq_pc___addr___width 12
#define reg_iop_spu_rw_seq_pc_offset 64

/*                                            */
#define reg_iop_spu_rw_fsm_pc___addr___lsb 0
#define reg_iop_spu_rw_fsm_pc___addr___width 12
#define reg_iop_spu_rw_fsm_pc_offset 68

/*                                          */
#define reg_iop_spu_rw_ctrl___fsm___lsb 0
#define reg_iop_spu_rw_ctrl___fsm___width 1
#define reg_iop_spu_rw_ctrl___fsm___bit 0
#define reg_iop_spu_rw_ctrl___en___lsb 1
#define reg_iop_spu_rw_ctrl___en___width 1
#define reg_iop_spu_rw_ctrl___en___bit 1
#define reg_iop_spu_rw_ctrl_offset 72

/*                                                   */
#define reg_iop_spu_rw_fsm_inputs3_0___val0___lsb 0
#define reg_iop_spu_rw_fsm_inputs3_0___val0___width 5
#define reg_iop_spu_rw_fsm_inputs3_0___src0___lsb 5
#define reg_iop_spu_rw_fsm_inputs3_0___src0___width 3
#define reg_iop_spu_rw_fsm_inputs3_0___val1___lsb 8
#define reg_iop_spu_rw_fsm_inputs3_0___val1___width 5
#define reg_iop_spu_rw_fsm_inputs3_0___src1___lsb 13
#define reg_iop_spu_rw_fsm_inputs3_0___src1___width 3
#define reg_iop_spu_rw_fsm_inputs3_0___val2___lsb 16
#define reg_iop_spu_rw_fsm_inputs3_0___val2___width 5
#define reg_iop_spu_rw_fsm_inputs3_0___src2___lsb 21
#define reg_iop_spu_rw_fsm_inputs3_0___src2___width 3
#define reg_iop_spu_rw_fsm_inputs3_0___val3___lsb 24
#define reg_iop_spu_rw_fsm_inputs3_0___val3___width 5
#define reg_iop_spu_rw_fsm_inputs3_0___src3___lsb 29
#define reg_iop_spu_rw_fsm_inputs3_0___src3___width 3
#define reg_iop_spu_rw_fsm_inputs3_0_offset 76

/*                                                   */
#define reg_iop_spu_rw_fsm_inputs7_4___val4___lsb 0
#define reg_iop_spu_rw_fsm_inputs7_4___val4___width 5
#define reg_iop_spu_rw_fsm_inputs7_4___src4___lsb 5
#define reg_iop_spu_rw_fsm_inputs7_4___src4___width 3
#define reg_iop_spu_rw_fsm_inputs7_4___val5___lsb 8
#define reg_iop_spu_rw_fsm_inputs7_4___val5___width 5
#define reg_iop_spu_rw_fsm_inputs7_4___src5___lsb 13
#define reg_iop_spu_rw_fsm_inputs7_4___src5___width 3
#define reg_iop_spu_rw_fsm_inputs7_4___val6___lsb 16
#define reg_iop_spu_rw_fsm_inputs7_4___val6___width 5
#define reg_iop_spu_rw_fsm_inputs7_4___src6___lsb 21
#define reg_iop_spu_rw_fsm_inputs7_4___src6___width 3
#define reg_iop_spu_rw_fsm_inputs7_4___val7___lsb 24
#define reg_iop_spu_rw_fsm_inputs7_4___val7___width 5
#define reg_iop_spu_rw_fsm_inputs7_4___src7___lsb 29
#define reg_iop_spu_rw_fsm_inputs7_4___src7___width 3
#define reg_iop_spu_rw_fsm_inputs7_4_offset 80

/*                                             */
#define reg_iop_spu_rw_gio_out_offset 84

/*                                              */
#define reg_iop_spu_rw_bus0_out_offset 88

/*                                              */
#define reg_iop_spu_rw_bus1_out_offset 92

/*                                          */
#define reg_iop_spu_r_gio_in_offset 96

/*                                           */
#define reg_iop_spu_r_bus0_in_offset 100

/*                                           */
#define reg_iop_spu_r_bus1_in_offset 104

/*                                                 */
#define reg_iop_spu_rw_gio_out_set_offset 108

/*                                                 */
#define reg_iop_spu_rw_gio_out_clr_offset 112

/*                                             */
#define reg_iop_spu_rs_wr_stat___r0___lsb 0
#define reg_iop_spu_rs_wr_stat___r0___width 1
#define reg_iop_spu_rs_wr_stat___r0___bit 0
#define reg_iop_spu_rs_wr_stat___r1___lsb 1
#define reg_iop_spu_rs_wr_stat___r1___width 1
#define reg_iop_spu_rs_wr_stat___r1___bit 1
#define reg_iop_spu_rs_wr_stat___r2___lsb 2
#define reg_iop_spu_rs_wr_stat___r2___width 1
#define reg_iop_spu_rs_wr_stat___r2___bit 2
#define reg_iop_spu_rs_wr_stat___r3___lsb 3
#define reg_iop_spu_rs_wr_stat___r3___width 1
#define reg_iop_spu_rs_wr_stat___r3___bit 3
#define reg_iop_spu_rs_wr_stat___r4___lsb 4
#define reg_iop_spu_rs_wr_stat___r4___width 1
#define reg_iop_spu_rs_wr_stat___r4___bit 4
#define reg_iop_spu_rs_wr_stat___r5___lsb 5
#define reg_iop_spu_rs_wr_stat___r5___width 1
#define reg_iop_spu_rs_wr_stat___r5___bit 5
#define reg_iop_spu_rs_wr_stat___r6___lsb 6
#define reg_iop_spu_rs_wr_stat___r6___width 1
#define reg_iop_spu_rs_wr_stat___r6___bit 6
#define reg_iop_spu_rs_wr_stat___r7___lsb 7
#define reg_iop_spu_rs_wr_stat___r7___width 1
#define reg_iop_spu_rs_wr_stat___r7___bit 7
#define reg_iop_spu_rs_wr_stat___r8___lsb 8
#define reg_iop_spu_rs_wr_stat___r8___width 1
#define reg_iop_spu_rs_wr_stat___r8___bit 8
#define reg_iop_spu_rs_wr_stat___r9___lsb 9
#define reg_iop_spu_rs_wr_stat___r9___width 1
#define reg_iop_spu_rs_wr_stat___r9___bit 9
#define reg_iop_spu_rs_wr_stat___r10___lsb 10
#define reg_iop_spu_rs_wr_stat___r10___width 1
#define reg_iop_spu_rs_wr_stat___r10___bit 10
#define reg_iop_spu_rs_wr_stat___r11___lsb 11
#define reg_iop_spu_rs_wr_stat___r11___width 1
#define reg_iop_spu_rs_wr_stat___r11___bit 11
#define reg_iop_spu_rs_wr_stat___r12___lsb 12
#define reg_iop_spu_rs_wr_stat___r12___width 1
#define reg_iop_spu_rs_wr_stat___r12___bit 12
#define reg_iop_spu_rs_wr_stat___r13___lsb 13
#define reg_iop_spu_rs_wr_stat___r13___width 1
#define reg_iop_spu_rs_wr_stat___r13___bit 13
#define reg_iop_spu_rs_wr_stat___r14___lsb 14
#define reg_iop_spu_rs_wr_stat___r14___width 1
#define reg_iop_spu_rs_wr_stat___r14___bit 14
#define reg_iop_spu_rs_wr_stat___r15___lsb 15
#define reg_iop_spu_rs_wr_stat___r15___width 1
#define reg_iop_spu_rs_wr_stat___r15___bit 15
#define reg_iop_spu_rs_wr_stat_offset 116

/*                                           */
#define reg_iop_spu_r_wr_stat___r0___lsb 0
#define reg_iop_spu_r_wr_stat___r0___width 1
#define reg_iop_spu_r_wr_stat___r0___bit 0
#define reg_iop_spu_r_wr_stat___r1___lsb 1
#define reg_iop_spu_r_wr_stat___r1___width 1
#define reg_iop_spu_r_wr_stat___r1___bit 1
#define reg_iop_spu_r_wr_stat___r2___lsb 2
#define reg_iop_spu_r_wr_stat___r2___width 1
#define reg_iop_spu_r_wr_stat___r2___bit 2
#define reg_iop_spu_r_wr_stat___r3___lsb 3
#define reg_iop_spu_r_wr_stat___r3___width 1
#define reg_iop_spu_r_wr_stat___r3___bit 3
#define reg_iop_spu_r_wr_stat___r4___lsb 4
#define reg_iop_spu_r_wr_stat___r4___width 1
#define reg_iop_spu_r_wr_stat___r4___bit 4
#define reg_iop_spu_r_wr_stat___r5___lsb 5
#define reg_iop_spu_r_wr_stat___r5___width 1
#define reg_iop_spu_r_wr_stat___r5___bit 5
#define reg_iop_spu_r_wr_stat___r6___lsb 6
#define reg_iop_spu_r_wr_stat___r6___width 1
#define reg_iop_spu_r_wr_stat___r6___bit 6
#define reg_iop_spu_r_wr_stat___r7___lsb 7
#define reg_iop_spu_r_wr_stat___r7___width 1
#define reg_iop_spu_r_wr_stat___r7___bit 7
#define reg_iop_spu_r_wr_stat___r8___lsb 8
#define reg_iop_spu_r_wr_stat___r8___width 1
#define reg_iop_spu_r_wr_stat___r8___bit 8
#define reg_iop_spu_r_wr_stat___r9___lsb 9
#define reg_iop_spu_r_wr_stat___r9___width 1
#define reg_iop_spu_r_wr_stat___r9___bit 9
#define reg_iop_spu_r_wr_stat___r10___lsb 10
#define reg_iop_spu_r_wr_stat___r10___width 1
#define reg_iop_spu_r_wr_stat___r10___bit 10
#define reg_iop_spu_r_wr_stat___r11___lsb 11
#define reg_iop_spu_r_wr_stat___r11___width 1
#define reg_iop_spu_r_wr_stat___r11___bit 11
#define reg_iop_spu_r_wr_stat___r12___lsb 12
#define reg_iop_spu_r_wr_stat___r12___width 1
#define reg_iop_spu_r_wr_stat___r12___bit 12
#define reg_iop_spu_r_wr_stat___r13___lsb 13
#define reg_iop_spu_r_wr_stat___r13___width 1
#define reg_iop_spu_r_wr_stat___r13___bit 13
#define reg_iop_spu_r_wr_stat___r14___lsb 14
#define reg_iop_spu_r_wr_stat___r14___width 1
#define reg_iop_spu_r_wr_stat___r14___bit 14
#define reg_iop_spu_r_wr_stat___r15___lsb 15
#define reg_iop_spu_r_wr_stat___r15___width 1
#define reg_iop_spu_r_wr_stat___r15___bit 15
#define reg_iop_spu_r_wr_stat_offset 120

/*                                                          */
#define reg_iop_spu_r_reg_indexed_by_bus0_in_offset 124

/*                                           */
#define reg_iop_spu_r_stat_in___timer_grp_lo___lsb 0
#define reg_iop_spu_r_stat_in___timer_grp_lo___width 4
#define reg_iop_spu_r_stat_in___fifo_out_last___lsb 4
#define reg_iop_spu_r_stat_in___fifo_out_last___width 1
#define reg_iop_spu_r_stat_in___fifo_out_last___bit 4
#define reg_iop_spu_r_stat_in___fifo_out_rdy___lsb 5
#define reg_iop_spu_r_stat_in___fifo_out_rdy___width 1
#define reg_iop_spu_r_stat_in___fifo_out_rdy___bit 5
#define reg_iop_spu_r_stat_in___fifo_out_all___lsb 6
#define reg_iop_spu_r_stat_in___fifo_out_all___width 1
#define reg_iop_spu_r_stat_in___fifo_out_all___bit 6
#define reg_iop_spu_r_stat_in___fifo_in_rdy___lsb 7
#define reg_iop_spu_r_stat_in___fifo_in_rdy___width 1
#define reg_iop_spu_r_stat_in___fifo_in_rdy___bit 7
#define reg_iop_spu_r_stat_in___dmc_out_all___lsb 8
#define reg_iop_spu_r_stat_in___dmc_out_all___width 1
#define reg_iop_spu_r_stat_in___dmc_out_all___bit 8
#define reg_iop_spu_r_stat_in___dmc_out_dth___lsb 9
#define reg_iop_spu_r_stat_in___dmc_out_dth___width 1
#define reg_iop_spu_r_stat_in___dmc_out_dth___bit 9
#define reg_iop_spu_r_stat_in___dmc_out_eop___lsb 10
#define reg_iop_spu_r_stat_in___dmc_out_eop___width 1
#define reg_iop_spu_r_stat_in___dmc_out_eop___bit 10
#define reg_iop_spu_r_stat_in___dmc_out_dv___lsb 11
#define reg_iop_spu_r_stat_in___dmc_out_dv___width 1
#define reg_iop_spu_r_stat_in___dmc_out_dv___bit 11
#define reg_iop_spu_r_stat_in___dmc_out_last___lsb 12
#define reg_iop_spu_r_stat_in___dmc_out_last___width 1
#define reg_iop_spu_r_stat_in___dmc_out_last___bit 12
#define reg_iop_spu_r_stat_in___dmc_out_cmd_rq___lsb 13
#define reg_iop_spu_r_stat_in___dmc_out_cmd_rq___width 1
#define reg_iop_spu_r_stat_in___dmc_out_cmd_rq___bit 13
#define reg_iop_spu_r_stat_in___dmc_out_cmd_rdy___lsb 14
#define reg_iop_spu_r_stat_in___dmc_out_cmd_rdy___width 1
#define reg_iop_spu_r_stat_in___dmc_out_cmd_rdy___bit 14
#define reg_iop_spu_r_stat_in___pcrc_correct___lsb 15
#define reg_iop_spu_r_stat_in___pcrc_correct___width 1
#define reg_iop_spu_r_stat_in___pcrc_correct___bit 15
#define reg_iop_spu_r_stat_in___timer_grp_hi___lsb 16
#define reg_iop_spu_r_stat_in___timer_grp_hi___width 4
#define reg_iop_spu_r_stat_in___dmc_in_sth___lsb 20
#define reg_iop_spu_r_stat_in___dmc_in_sth___width 1
#define reg_iop_spu_r_stat_in___dmc_in_sth___bit 20
#define reg_iop_spu_r_stat_in___dmc_in_full___lsb 21
#define reg_iop_spu_r_stat_in___dmc_in_full___width 1
#define reg_iop_spu_r_stat_in___dmc_in_full___bit 21
#define reg_iop_spu_r_stat_in___dmc_in_cmd_rdy___lsb 22
#define reg_iop_spu_r_stat_in___dmc_in_cmd_rdy___width 1
#define reg_iop_spu_r_stat_in___dmc_in_cmd_rdy___bit 22
#define reg_iop_spu_r_stat_in___spu_gio_out___lsb 23
#define reg_iop_spu_r_stat_in___spu_gio_out___width 4
#define reg_iop_spu_r_stat_in___sync_clk12___lsb 27
#define reg_iop_spu_r_stat_in___sync_clk12___width 1
#define reg_iop_spu_r_stat_in___sync_clk12___bit 27
#define reg_iop_spu_r_stat_in___scrc_out_data___lsb 28
#define reg_iop_spu_r_stat_in___scrc_out_data___width 1
#define reg_iop_spu_r_stat_in___scrc_out_data___bit 28
#define reg_iop_spu_r_stat_in___scrc_in_err___lsb 29
#define reg_iop_spu_r_stat_in___scrc_in_err___width 1
#define reg_iop_spu_r_stat_in___scrc_in_err___bit 29
#define reg_iop_spu_r_stat_in___mc_busy___lsb 30
#define reg_iop_spu_r_stat_in___mc_busy___width 1
#define reg_iop_spu_r_stat_in___mc_busy___bit 30
#define reg_iop_spu_r_stat_in___mc_owned___lsb 31
#define reg_iop_spu_r_stat_in___mc_owned___width 1
#define reg_iop_spu_r_stat_in___mc_owned___bit 31
#define reg_iop_spu_r_stat_in_offset 128

/*                                              */
#define reg_iop_spu_r_trigger_in_offset 132

/*                                                */
#define reg_iop_spu_r_special_stat___c_flag___lsb 0
#define reg_iop_spu_r_special_stat___c_flag___width 1
#define reg_iop_spu_r_special_stat___c_flag___bit 0
#define reg_iop_spu_r_special_stat___v_flag___lsb 1
#define reg_iop_spu_r_special_stat___v_flag___width 1
#define reg_iop_spu_r_special_stat___v_flag___bit 1
#define reg_iop_spu_r_special_stat___z_flag___lsb 2
#define reg_iop_spu_r_special_stat___z_flag___width 1
#define reg_iop_spu_r_special_stat___z_flag___bit 2
#define reg_iop_spu_r_special_stat___n_flag___lsb 3
#define reg_iop_spu_r_special_stat___n_flag___width 1
#define reg_iop_spu_r_special_stat___n_flag___bit 3
#define reg_iop_spu_r_special_stat___xor_bus0_r2_0___lsb 4
#define reg_iop_spu_r_special_stat___xor_bus0_r2_0___width 1
#define reg_iop_spu_r_special_stat___xor_bus0_r2_0___bit 4
#define reg_iop_spu_r_special_stat___xor_bus1_r3_0___lsb 5
#define reg_iop_spu_r_special_stat___xor_bus1_r3_0___width 1
#define reg_iop_spu_r_special_stat___xor_bus1_r3_0___bit 5
#define reg_iop_spu_r_special_stat___xor_bus0m_r2_0___lsb 6
#define reg_iop_spu_r_special_stat___xor_bus0m_r2_0___width 1
#define reg_iop_spu_r_special_stat___xor_bus0m_r2_0___bit 6
#define reg_iop_spu_r_special_stat___xor_bus1m_r3_0___lsb 7
#define reg_iop_spu_r_special_stat___xor_bus1m_r3_0___width 1
#define reg_iop_spu_r_special_stat___xor_bus1m_r3_0___bit 7
#define reg_iop_spu_r_special_stat___fsm_in0___lsb 8
#define reg_iop_spu_r_special_stat___fsm_in0___width 1
#define reg_iop_spu_r_special_stat___fsm_in0___bit 8
#define reg_iop_spu_r_special_stat___fsm_in1___lsb 9
#define reg_iop_spu_r_special_stat___fsm_in1___width 1
#define reg_iop_spu_r_special_stat___fsm_in1___bit 9
#define reg_iop_spu_r_special_stat___fsm_in2___lsb 10
#define reg_iop_spu_r_special_stat___fsm_in2___width 1
#define reg_iop_spu_r_special_stat___fsm_in2___bit 10
#define reg_iop_spu_r_special_stat___fsm_in3___lsb 11
#define reg_iop_spu_r_special_stat___fsm_in3___width 1
#define reg_iop_spu_r_special_stat___fsm_in3___bit 11
#define reg_iop_spu_r_special_stat___fsm_in4___lsb 12
#define reg_iop_spu_r_special_stat___fsm_in4___width 1
#define reg_iop_spu_r_special_stat___fsm_in4___bit 12
#define reg_iop_spu_r_special_stat___fsm_in5___lsb 13
#define reg_iop_spu_r_special_stat___fsm_in5___width 1
#define reg_iop_spu_r_special_stat___fsm_in5___bit 13
#define reg_iop_spu_r_special_stat___fsm_in6___lsb 14
#define reg_iop_spu_r_special_stat___fsm_in6___width 1
#define reg_iop_spu_r_special_stat___fsm_in6___bit 14
#define reg_iop_spu_r_special_stat___fsm_in7___lsb 15
#define reg_iop_spu_r_special_stat___fsm_in7___width 1
#define reg_iop_spu_r_special_stat___fsm_in7___bit 15
#define reg_iop_spu_r_special_stat___event0___lsb 16
#define reg_iop_spu_r_special_stat___event0___width 1
#define reg_iop_spu_r_special_stat___event0___bit 16
#define reg_iop_spu_r_special_stat___event1___lsb 17
#define reg_iop_spu_r_special_stat___event1___width 1
#define reg_iop_spu_r_special_stat___event1___bit 17
#define reg_iop_spu_r_special_stat___event2___lsb 18
#define reg_iop_spu_r_special_stat___event2___width 1
#define reg_iop_spu_r_special_stat___event2___bit 18
#define reg_iop_spu_r_special_stat___event3___lsb 19
#define reg_iop_spu_r_special_stat___event3___width 1
#define reg_iop_spu_r_special_stat___event3___bit 19
#define reg_iop_spu_r_special_stat_offset 136

/*                                                */
#define reg_iop_spu_rw_reg_access___addr___lsb 0
#define reg_iop_spu_rw_reg_access___addr___width 13
#define reg_iop_spu_rw_reg_access___imm_hi___lsb 16
#define reg_iop_spu_rw_reg_access___imm_hi___width 16
#define reg_iop_spu_rw_reg_access_offset 140

#define STRIDE_iop_spu_rw_event_cfg 4
/*                                               */
#define reg_iop_spu_rw_event_cfg___addr___lsb 0
#define reg_iop_spu_rw_event_cfg___addr___width 12
#define reg_iop_spu_rw_event_cfg___src___lsb 12
#define reg_iop_spu_rw_event_cfg___src___width 2
#define reg_iop_spu_rw_event_cfg___eq_en___lsb 14
#define reg_iop_spu_rw_event_cfg___eq_en___width 1
#define reg_iop_spu_rw_event_cfg___eq_en___bit 14
#define reg_iop_spu_rw_event_cfg___eq_inv___lsb 15
#define reg_iop_spu_rw_event_cfg___eq_inv___width 1
#define reg_iop_spu_rw_event_cfg___eq_inv___bit 15
#define reg_iop_spu_rw_event_cfg___gt_en___lsb 16
#define reg_iop_spu_rw_event_cfg___gt_en___width 1
#define reg_iop_spu_rw_event_cfg___gt_en___bit 16
#define reg_iop_spu_rw_event_cfg___gt_inv___lsb 17
#define reg_iop_spu_rw_event_cfg___gt_inv___width 1
#define reg_iop_spu_rw_event_cfg___gt_inv___bit 17
#define reg_iop_spu_rw_event_cfg_offset 144

#define STRIDE_iop_spu_rw_event_mask 4
/*                                                */
#define reg_iop_spu_rw_event_mask_offset 160

#define STRIDE_iop_spu_rw_event_val 4
/*                                               */
#define reg_iop_spu_rw_event_val_offset 176

/*                                               */
#define reg_iop_spu_rw_event_ret___addr___lsb 0
#define reg_iop_spu_rw_event_ret___addr___width 12
#define reg_iop_spu_rw_event_ret_offset 192

/*                                         */
#define reg_iop_spu_r_trace___fsm___lsb 0
#define reg_iop_spu_r_trace___fsm___width 1
#define reg_iop_spu_r_trace___fsm___bit 0
#define reg_iop_spu_r_trace___en___lsb 1
#define reg_iop_spu_r_trace___en___width 1
#define reg_iop_spu_r_trace___en___bit 1
#define reg_iop_spu_r_trace___c_flag___lsb 2
#define reg_iop_spu_r_trace___c_flag___width 1
#define reg_iop_spu_r_trace___c_flag___bit 2
#define reg_iop_spu_r_trace___v_flag___lsb 3
#define reg_iop_spu_r_trace___v_flag___width 1
#define reg_iop_spu_r_trace___v_flag___bit 3
#define reg_iop_spu_r_trace___z_flag___lsb 4
#define reg_iop_spu_r_trace___z_flag___width 1
#define reg_iop_spu_r_trace___z_flag___bit 4
#define reg_iop_spu_r_trace___n_flag___lsb 5
#define reg_iop_spu_r_trace___n_flag___width 1
#define reg_iop_spu_r_trace___n_flag___bit 5
#define reg_iop_spu_r_trace___seq_addr___lsb 6
#define reg_iop_spu_r_trace___seq_addr___width 12
#define reg_iop_spu_r_trace___fsm_addr___lsb 20
#define reg_iop_spu_r_trace___fsm_addr___width 12
#define reg_iop_spu_r_trace_offset 196

/*                                             */
#define reg_iop_spu_r_fsm_trace___fsm___lsb 0
#define reg_iop_spu_r_fsm_trace___fsm___width 1
#define reg_iop_spu_r_fsm_trace___fsm___bit 0
#define reg_iop_spu_r_fsm_trace___en___lsb 1
#define reg_iop_spu_r_fsm_trace___en___width 1
#define reg_iop_spu_r_fsm_trace___en___bit 1
#define reg_iop_spu_r_fsm_trace___tmr_done___lsb 2
#define reg_iop_spu_r_fsm_trace___tmr_done___width 1
#define reg_iop_spu_r_fsm_trace___tmr_done___bit 2
#define reg_iop_spu_r_fsm_trace___inp0___lsb 3
#define reg_iop_spu_r_fsm_trace___inp0___width 1
#define reg_iop_spu_r_fsm_trace___inp0___bit 3
#define reg_iop_spu_r_fsm_trace___inp1___lsb 4
#define reg_iop_spu_r_fsm_trace___inp1___width 1
#define reg_iop_spu_r_fsm_trace___inp1___bit 4
#define reg_iop_spu_r_fsm_trace___inp2___lsb 5
#define reg_iop_spu_r_fsm_trace___inp2___width 1
#define reg_iop_spu_r_fsm_trace___inp2___bit 5
#define reg_iop_spu_r_fsm_trace___inp3___lsb 6
#define reg_iop_spu_r_fsm_trace___inp3___width 1
#define reg_iop_spu_r_fsm_trace___inp3___bit 6
#define reg_iop_spu_r_fsm_trace___event0___lsb 7
#define reg_iop_spu_r_fsm_trace___event0___width 1
#define reg_iop_spu_r_fsm_trace___event0___bit 7
#define reg_iop_spu_r_fsm_trace___event1___lsb 8
#define reg_iop_spu_r_fsm_trace___event1___width 1
#define reg_iop_spu_r_fsm_trace___event1___bit 8
#define reg_iop_spu_r_fsm_trace___event2___lsb 9
#define reg_iop_spu_r_fsm_trace___event2___width 1
#define reg_iop_spu_r_fsm_trace___event2___bit 9
#define reg_iop_spu_r_fsm_trace___event3___lsb 10
#define reg_iop_spu_r_fsm_trace___event3___width 1
#define reg_iop_spu_r_fsm_trace___event3___bit 10
#define reg_iop_spu_r_fsm_trace___gio_out___lsb 11
#define reg_iop_spu_r_fsm_trace___gio_out___width 8
#define reg_iop_spu_r_fsm_trace___fsm_addr___lsb 20
#define reg_iop_spu_r_fsm_trace___fsm_addr___width 12
#define reg_iop_spu_r_fsm_trace_offset 200

#define STRIDE_iop_spu_rw_brp 4
/*                                         */
#define reg_iop_spu_rw_brp___addr___lsb 0
#define reg_iop_spu_rw_brp___addr___width 12
#define reg_iop_spu_rw_brp___fsm___lsb 12
#define reg_iop_spu_rw_brp___fsm___width 1
#define reg_iop_spu_rw_brp___fsm___bit 12
#define reg_iop_spu_rw_brp___en___lsb 13
#define reg_iop_spu_rw_brp___en___width 1
#define reg_iop_spu_rw_brp___en___bit 13
#define reg_iop_spu_rw_brp_offset 204


/*           */
#define regk_iop_spu_attn_hi                      0x00000005
#define regk_iop_spu_attn_lo                      0x00000005
#define regk_iop_spu_attn_r0                      0x00000000
#define regk_iop_spu_attn_r1                      0x00000001
#define regk_iop_spu_attn_r10                     0x00000002
#define regk_iop_spu_attn_r11                     0x00000003
#define regk_iop_spu_attn_r12                     0x00000004
#define regk_iop_spu_attn_r13                     0x00000005
#define regk_iop_spu_attn_r14                     0x00000006
#define regk_iop_spu_attn_r15                     0x00000007
#define regk_iop_spu_attn_r2                      0x00000002
#define regk_iop_spu_attn_r3                      0x00000003
#define regk_iop_spu_attn_r4                      0x00000004
#define regk_iop_spu_attn_r5                      0x00000005
#define regk_iop_spu_attn_r6                      0x00000006
#define regk_iop_spu_attn_r7                      0x00000007
#define regk_iop_spu_attn_r8                      0x00000000
#define regk_iop_spu_attn_r9                      0x00000001
#define regk_iop_spu_c                            0x00000000
#define regk_iop_spu_flag                         0x00000002
#define regk_iop_spu_gio_in                       0x00000000
#define regk_iop_spu_gio_out                      0x00000005
#define regk_iop_spu_gio_out0                     0x00000008
#define regk_iop_spu_gio_out1                     0x00000009
#define regk_iop_spu_gio_out2                     0x0000000a
#define regk_iop_spu_gio_out3                     0x0000000b
#define regk_iop_spu_gio_out4                     0x0000000c
#define regk_iop_spu_gio_out5                     0x0000000d
#define regk_iop_spu_gio_out6                     0x0000000e
#define regk_iop_spu_gio_out7                     0x0000000f
#define regk_iop_spu_n                            0x00000003
#define regk_iop_spu_no                           0x00000000
#define regk_iop_spu_r0                           0x00000008
#define regk_iop_spu_r1                           0x00000009
#define regk_iop_spu_r10                          0x0000000a
#define regk_iop_spu_r11                          0x0000000b
#define regk_iop_spu_r12                          0x0000000c
#define regk_iop_spu_r13                          0x0000000d
#define regk_iop_spu_r14                          0x0000000e
#define regk_iop_spu_r15                          0x0000000f
#define regk_iop_spu_r2                           0x0000000a
#define regk_iop_spu_r3                           0x0000000b
#define regk_iop_spu_r4                           0x0000000c
#define regk_iop_spu_r5                           0x0000000d
#define regk_iop_spu_r6                           0x0000000e
#define regk_iop_spu_r7                           0x0000000f
#define regk_iop_spu_r8                           0x00000008
#define regk_iop_spu_r9                           0x00000009
#define regk_iop_spu_reg_hi                       0x00000002
#define regk_iop_spu_reg_lo                       0x00000002
#define regk_iop_spu_rw_brp_default               0x00000000
#define regk_iop_spu_rw_brp_size                  0x00000004
#define regk_iop_spu_rw_ctrl_default              0x00000000
#define regk_iop_spu_rw_event_cfg_size            0x00000004
#define regk_iop_spu_rw_event_mask_size           0x00000004
#define regk_iop_spu_rw_event_val_size            0x00000004
#define regk_iop_spu_rw_gio_out_default           0x00000000
#define regk_iop_spu_rw_r_size                    0x00000010
#define regk_iop_spu_rw_reg_access_default        0x00000000
#define regk_iop_spu_stat_in                      0x00000002
#define regk_iop_spu_statin_hi                    0x00000004
#define regk_iop_spu_statin_lo                    0x00000004
#define regk_iop_spu_trig                         0x00000003
#define regk_iop_spu_trigger                      0x00000006
#define regk_iop_spu_v                            0x00000001
#define regk_iop_spu_wsts_gioout_spec             0x00000001
#define regk_iop_spu_xor                          0x00000003
#define regk_iop_spu_xor_bus0_r2_0                0x00000000
#define regk_iop_spu_xor_bus0m_r2_0               0x00000002
#define regk_iop_spu_xor_bus1_r3_0                0x00000001
#define regk_iop_spu_xor_bus1m_r3_0               0x00000003
#define regk_iop_spu_yes                          0x00000001
#define regk_iop_spu_z                            0x00000002
#endif /*                      */
