/*
 * Line6 Linux USB driver - 0.9.1beta
 *
 * Copyright (C) 2004-2010 Markus Grabner (grabner@icg.tugraz.at)
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License as
 *	published by the Free Software Foundation, version 2.
 *
 */

#ifndef LINE6_CONTROL_H
#define LINE6_CONTROL_H

/* 
                              
                                                                 
                                                                             
                    

                                                                               
                                                                            
                               
*/

/*              */

enum {
	POD_tweak                          =   1,
	POD_wah_position                   =   4,
	POD_compression_gain               =   5,  /*                             */
	POD_vol_pedal_position             =   7,
	POD_compression_threshold          =   9,
	POD_pan                            =  10,
	POD_amp_model_setup                =  11,
	POD_amp_model                      =  12,  /*               */
	POD_drive                          =  13,
	POD_bass                           =  14,
	POD_mid                            =  15,  /*                             */
	POD_lowmid                         =  15,  /*                                 */
	POD_treble                         =  16,  /*                             */
	POD_highmid                        =  16,  /*                                 */
	POD_chan_vol                       =  17,
	POD_reverb_mix                     =  18,  /*                             */
	POD_effect_setup                   =  19,
	POD_band_1_frequency               =  20,  /*               */
	POD_presence                       =  21,  /*                             */
	POD_treble__bass                   =  21,  /*                                 */
	POD_noise_gate_enable              =  22,
	POD_gate_threshold                 =  23,
	POD_gate_decay_time                =  24,
	POD_stomp_enable                   =  25,
	POD_comp_enable                    =  26,
	POD_stomp_time                     =  27,
	POD_delay_enable                   =  28,
	POD_mod_param_1                    =  29,
	POD_delay_param_1                  =  30,
	POD_delay_param_1_note_value       =  31,
	POD_band_2_frequency__bass         =  32,  /*                                 */ /*               */
	POD_delay_param_2                  =  33,
	POD_delay_volume_mix               =  34,
	POD_delay_param_3                  =  35,
	POD_reverb_enable                  =  36,  /*                             */
	POD_reverb_type                    =  37,  /*                             */
	POD_reverb_decay                   =  38,  /*                             */
	POD_reverb_tone                    =  39,  /*                             */
	POD_reverb_pre_delay               =  40,  /*                             */
	POD_reverb_pre_post                =  41,  /*                             */
	POD_band_2_frequency               =  42,  /*                             */     /*               */
	POD_band_3_frequency__bass         =  42,  /*                                 */ /*               */
	POD_wah_enable                     =  43,
	POD_modulation_lo_cut              =  44,  /*                                 */
	POD_delay_reverb_lo_cut            =  45,  /*                                 */
	POD_volume_pedal_minimum           =  46,  /*                             */     /*               */
	POD_eq_pre_post                    =  46,  /*                                 */ /*               */
	POD_volume_pre_post                =  47,
	POD_di_model                       =  48,  /*                                 */
	POD_di_delay                       =  49,  /*                                 */
	POD_mod_enable                     =  50,
	POD_mod_param_1_note_value         =  51,
	POD_mod_param_2                    =  52,
	POD_mod_param_3                    =  53,
	POD_mod_param_4                    =  54,
	POD_mod_param_5                    =  55,  /*                                 */
	POD_mod_volume_mix                 =  56,
	POD_mod_pre_post                   =  57,
	POD_modulation_model               =  58,
	POD_band_3_frequency               =  60,  /*                             */     /*               */
	POD_band_4_frequency__bass         =  60,  /*                                 */ /*               */
	POD_mod_param_1_double_precision   =  61,
	POD_delay_param_1_double_precision =  62,
	POD_eq_enable                      =  63,  /*               */
	POD_tap                            =  64,
	POD_volume_tweak_pedal_assign      =  65,
	POD_band_5_frequency               =  68,  /*                                 */ /*               */
	POD_tuner                          =  69,
	POD_mic_selection                  =  70,
	POD_cabinet_model                  =  71,
	POD_stomp_model                    =  75,
	POD_roomlevel                      =  76,
	POD_band_4_frequency               =  77,  /*                             */     /*               */
	POD_band_6_frequency               =  77,  /*                                 */ /*               */
	POD_stomp_param_1_note_value       =  78,
	POD_stomp_param_2                  =  79,
	POD_stomp_param_3                  =  80,
	POD_stomp_param_4                  =  81,
	POD_stomp_param_5                  =  82,
	POD_stomp_param_6                  =  83,
	POD_amp_switch_select              =  84,  /*                         */
	POD_delay_param_4                  =  85,
	POD_delay_param_5                  =  86,
	POD_delay_pre_post                 =  87,
	POD_delay_model                    =  88,  /*                             */
	POD_delay_verb_model               =  88,  /*                                 */
	POD_tempo_msb                      =  89,
	POD_tempo_lsb                      =  90,
	POD_wah_model                      =  91,  /*               */
	POD_bypass_volume                  = 105,  /*                */
	POD_fx_loop_on_off                 = 107,  /*                        */
	POD_tweak_param_select             = 108,
	POD_amp1_engage                    = 111,
	POD_band_1_gain                    = 114,  /*               */
	POD_band_2_gain__bass              = 115,  /*                                 */ /*               */
	POD_band_2_gain                    = 116,  /*                             */     /*               */
	POD_band_3_gain__bass              = 116,  /*                                 */ /*               */
	POD_band_3_gain                    = 117,  /*                             */     /*               */
	POD_band_4_gain__bass              = 117,  /*                                 */ /*               */
	POD_band_5_gain__bass              = 118,  /*                                 */ /*               */
	POD_band_4_gain                    = 119,  /*                             */     /*               */
	POD_band_6_gain__bass              = 119   /*                                 */ /*               */
};

/* 
                                            
*/
enum {
	VARIAX_body                        =   3,
	VARIAX_pickup1_enable              =   4,  /*                         */
	VARIAX_pickup1_type                =   8,
	VARIAX_pickup1_position            =   9,  /*                    */
	VARIAX_pickup1_angle               =  12,  /*                    */
	VARIAX_pickup1_level               =  15,  /*                    */
	VARIAX_pickup2_enable              =  18,  /*                         */
	VARIAX_pickup2_type                =  22,
	VARIAX_pickup2_position            =  23,  /*                    */
	VARIAX_pickup2_angle               =  26,  /*                    */
	VARIAX_pickup2_level               =  29,  /*                    */
	VARIAX_pickup_phase                =  32,  /*                              */
	VARIAX_capacitance                 =  33,  /*                    */
	VARIAX_tone_resistance             =  36,  /*                    */
	VARIAX_volume_resistance           =  39,  /*                    */
	VARIAX_taper                       =  42,  /*                     */
	VARIAX_tone_dump                   =  43,  /*                    */
	VARIAX_save_tone                   =  46,
	VARIAX_volume_dump                 =  47,  /*                    */
	VARIAX_tuning_enable               =  50,
	VARIAX_tuning6                     =  51,
	VARIAX_tuning5                     =  52,
	VARIAX_tuning4                     =  53,
	VARIAX_tuning3                     =  54,
	VARIAX_tuning2                     =  55,
	VARIAX_tuning1                     =  56,
	VARIAX_detune6                     =  57,  /*                    */
	VARIAX_detune5                     =  60,  /*                    */
	VARIAX_detune4                     =  63,  /*                    */
	VARIAX_detune3                     =  66,  /*                    */
	VARIAX_detune2                     =  69,  /*                    */
	VARIAX_detune1                     =  72,  /*                    */
	VARIAX_mix6                        =  75,  /*                    */
	VARIAX_mix5                        =  78,  /*                    */
	VARIAX_mix4                        =  81,  /*                    */
	VARIAX_mix3                        =  84,  /*                    */
	VARIAX_mix2                        =  87,  /*                    */
	VARIAX_mix1                        =  90,  /*                    */
	VARIAX_pickup_wiring               =  96   /*                        */
};

/* 
                                            
*/
enum {
	VARIAXMIDI_volume                  =   7,
	VARIAXMIDI_tone                    =  79,
};

/*             */

extern int line6_pod_create_files(int firmware, int type, struct device *dev);
extern void line6_pod_remove_files(int firmware, int type, struct device *dev);
extern int line6_variax_create_files(int firmware, int type,
				     struct device *dev);
extern void line6_variax_remove_files(int firmware, int type,
				      struct device *dev);

#endif
