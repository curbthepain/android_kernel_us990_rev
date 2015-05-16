#ifndef __SOUND_AZT3328_H
#define __SOUND_AZT3328_H

/*                                                          
                                                                 */

/*                                */
/*                                                            */
#define AZF_IO_SIZE_CTRL	0x80
#define AZF_IO_SIZE_CTRL_PM	0x70

/*                                                       
                                    
                                                          
                                                
                                                                     
                              */

#define AZF_IO_OFFS_CODEC_PLAYBACK	0x00
#define AZF_IO_OFFS_CODEC_CAPTURE	0x20
#define AZF_IO_OFFS_CODEC_I2S_OUT	0x40

#define IDX_IO_CODEC_DMA_FLAGS       0x00 /*           */
     /*                                                             
                                        
                                                                    */
  #define DMA_RESUME			0x0001 /*                    */
     /*                                                  
                                                      */
     /*                                                             
                                         */
  #define DMA_RUN_SOMETHING1		0x0002 /*                        */
     /*                                       */
  #define DMA_RUN_SOMETHING2		0x0004 /*        */
  #define SOMETHING_ALMOST_ALWAYS_SET	0x0008 /*                      */
  #define DMA_EPILOGUE_SOMETHING	0x0010
  #define DMA_SOMETHING_ELSE		0x0020 /*     */
  #define SOMETHING_UNMODIFIABLE	0xffc0 /*                        */
#define IDX_IO_CODEC_IRQTYPE     0x02 /*           */
  /*                                                                          
                                                                          
                                                                          
                                                                  
                                                                            */
  #define IRQ_SOMETHING			0x0001 /*                 */
  #define IRQ_FINISHED_DMABUF_1		0x0002 /*                           */
  #define IRQ_FINISHED_DMABUF_2		0x0004 /*                           */
  #define IRQMASK_SOME_STATUS_1		0x0008 /*                */
  #define IRQMASK_SOME_STATUS_2		0x0010 /*                              */
  #define IRQMASK_UNMODIFIABLE		0xffe0 /*                        */
  /*                                                       */
#define IDX_IO_CODEC_DMA_START_1 0x04
  /*                                                       */
#define IDX_IO_CODEC_DMA_START_2 0x08
  /*                                                  
                                                */
#define IDX_IO_CODEC_DMA_LENGTHS 0x0c
#define IDX_IO_CODEC_DMA_CURRPOS 0x10 /*                                     */
  /*                                                    */
#define IDX_IO_CODEC_DMA_CURROFS 0x14
#define IDX_IO_CODEC_SOUNDFORMAT 0x16 /*           */
  /*                                        */
  #define SOUNDFORMAT_FREQUENCY_MASK	0x000f
  #define SOUNDFORMAT_XTAL1		0x00
  #define SOUNDFORMAT_XTAL2		0x01
    /*                                                                    
                                                    
                                                                       
                                                                        
                                                                  */
    #define SOUNDFORMAT_FREQ_SUSPECTED_4000	0x0c | SOUNDFORMAT_XTAL1
    #define SOUNDFORMAT_FREQ_SUSPECTED_4800	0x0a | SOUNDFORMAT_XTAL1
    #define SOUNDFORMAT_FREQ_5510		0x0c | SOUNDFORMAT_XTAL2
    #define SOUNDFORMAT_FREQ_6620		0x0a | SOUNDFORMAT_XTAL2
    #define SOUNDFORMAT_FREQ_8000		0x00 | SOUNDFORMAT_XTAL1 /*                                */
    #define SOUNDFORMAT_FREQ_9600		0x08 | SOUNDFORMAT_XTAL1
    #define SOUNDFORMAT_FREQ_11025		0x00 | SOUNDFORMAT_XTAL2 /*                                */
    #define SOUNDFORMAT_FREQ_SUSPECTED_13240	0x08 | SOUNDFORMAT_XTAL2 /*                     */
    #define SOUNDFORMAT_FREQ_16000		0x02 | SOUNDFORMAT_XTAL1
    #define SOUNDFORMAT_FREQ_22050		0x02 | SOUNDFORMAT_XTAL2
    #define SOUNDFORMAT_FREQ_32000		0x04 | SOUNDFORMAT_XTAL1
    #define SOUNDFORMAT_FREQ_44100		0x04 | SOUNDFORMAT_XTAL2
    #define SOUNDFORMAT_FREQ_48000		0x06 | SOUNDFORMAT_XTAL1
    #define SOUNDFORMAT_FREQ_SUSPECTED_66200	0x06 | SOUNDFORMAT_XTAL2 /*                                                  */
  #define SOUNDFORMAT_FLAG_16BIT	0x0010
  #define SOUNDFORMAT_FLAG_2CHANNELS	0x0020


/*                                                    */
enum azf_freq_t {
#define AZF_FREQ(rate) AZF_FREQ_##rate = rate
  AZF_FREQ(4000),
  AZF_FREQ(4800),
  AZF_FREQ(5512),
  AZF_FREQ(6620),
  AZF_FREQ(8000),
  AZF_FREQ(9600),
  AZF_FREQ(11025),
  AZF_FREQ(13240),
  AZF_FREQ(16000),
  AZF_FREQ(22050),
  AZF_FREQ(32000),
  AZF_FREQ(44100),
  AZF_FREQ(48000),
  AZF_FREQ(66200),
#undef AZF_FREQ
};

/*                                                                   */ 
#define IDX_IO_TIMER_VALUE	0x60 /*                                        */
  /*                                                            */
  #define TIMER_VALUE_MASK		0x000fffffUL
  /*                          */
  #define TIMER_COUNTDOWN_ENABLE	0x01000000UL
  /*                                      */
  #define TIMER_IRQ_ENABLE		0x02000000UL
  /*                                                                    
                                     */
  #define TIMER_IRQ_ACK			0x04000000UL
#define IDX_IO_IRQSTATUS        0x64
  /*                                                                           
                                                                               
                                                                          
                                                                              
                                                               
                                    */

  #define IRQ_PLAYBACK	0x0001
  #define IRQ_RECORDING	0x0002
  #define IRQ_I2S_OUT	0x0004 /*                                 */
  #define IRQ_GAMEPORT	0x0008 /*                                             */
  #define IRQ_MPU401	0x0010
  #define IRQ_TIMER	0x0020 /*               */
  #define IRQ_UNKNOWN2	0x0040 /*                                          */
  #define IRQ_UNKNOWN3	0x0080 /*                                          */
#define IDX_IO_66H		0x66    /*                               */
  /*                                                  
                                                                       */
#define IDX_IO_SOME_VALUE	0x68
  #define IO_68_RANDOM_TOGGLE1	0x0100	/*                  */
  #define IO_68_RANDOM_TOGGLE2	0x0200	/*                  */
  /*                                                                      
              
                                             
                                                                           
                                                                
                                                                    
                                                                           
                                                           
   */

/*                                                                       
                                                               */
#define IDX_IO_6AH		0x6A /*             */
  /*                                                                   
                                                             
                                                    
                                                                        
                                                          */
  #define IO_6A_SOMETHING1_GAMEPORT	0x0020
  /*                                                                   
                                               */
  #define IO_6A_PAUSE_PLAYBACK_BIT8	0x0100
  /*                                                                   
                                               */
  #define IO_6A_PAUSE_PLAYBACK_BIT9	0x0200
	/*                                                           
                                            
                                                              
                                     */
  /*                                                                 
                                                                               
                                                                             
                                                               */
  #define IO_6A_SOMETHING2_GAMEPORT      0x0400
	/*                                                   
                                                        
                                 */
	/*                                                 */
	/*                                                         
                                                                       
                                                                  
                                                                      
                        */
#define IDX_IO_6CH		0x6C	/*                              */
#define IDX_IO_6EH		0x6E
	/*                                                
                                                                    
                       */

/*                                                                       
                        */


/*                                */
/*                                                            */ 
#define AZF_IO_SIZE_GAME		0x08
#define AZF_IO_SIZE_GAME_PM		0x06

enum {
	AZF_GAME_LEGACY_IO_PORT = 0x200
};

#define IDX_GAME_LEGACY_COMPATIBLE	0x00
	/*                                                      
                          
                                                   
                                 
                                                                 */

#define IDX_GAME_AXES_CONFIG            0x01
	/*                                                                    
                           */

  /*                                      */
  #define GAME_AXES_ENABLE_1		0x01
  /*                                      */
  #define GAME_AXES_ENABLE_2		0x02
  /*                                      */
  #define GAME_AXES_ENABLE_3		0x04
  /*                                      */
  #define GAME_AXES_ENABLE_4		0x08
  /*                                                       
                              
                                                         */
  #define GAME_AXES_READ_MASK		0x30
  /*                                                        
                                                                        
                                                  */
  #define GAME_AXES_LATCH_ENABLE	0x40
  /*                                                  */
  #define GAME_AXES_SAMPLING_READY	0x80

  /*                                                           
                                                                     
                                 
                                                                        
                                 */
  /*                                                                        
                                                 */

  /*                                                                          
                                         
                                                  */

#define IDX_GAME_AXIS_VALUE	0x02
	/*                                                     
                                */

#define IDX_GAME_HWCONFIG	0x04
	/*                                                     
                       */
  /*                                                       */
  #define GAME_HWCFG_IRQ_ENABLE			0x01
  /*                                                
                                     
                                      
                              
               
                
                   */
  #define GAME_HWCFG_ADC_COUNTER_FREQ_MASK	0x06

  /*                                          */
  #define GAME_HWCFG_ADC_COUNTER_FREQ_STD	0
  #define GAME_HWCFG_ADC_COUNTER_FREQ_1_2	1
  #define GAME_HWCFG_ADC_COUNTER_FREQ_1_20	2
  #define GAME_HWCFG_ADC_COUNTER_FREQ_1_200	3

  /*                                           
                                                                         */
  #define GAME_HWCFG_LEGACY_ADDRESS_ENABLE	0x08

/*            */
#define AZF_IO_SIZE_MPU		0x04
#define AZF_IO_SIZE_MPU_PM	0x04

/*                */
/*                                                            */
#define AZF_IO_SIZE_OPL3	0x08
#define AZF_IO_SIZE_OPL3_PM	0x06
/*                                                      
                                                                
                                                                 */

/*                                 */
/*                                                           
                                                                          */
#define AZF_IO_SIZE_MIXER	0x40
#define AZF_IO_SIZE_MIXER_PM	0x22

  #define MIXER_VOLUME_RIGHT_MASK	0x001f
  #define MIXER_VOLUME_LEFT_MASK	0x1f00
  #define MIXER_MUTE_MASK		0x8000
#define IDX_MIXER_RESET		0x00 /*                                    */
#define IDX_MIXER_PLAY_MASTER   0x02
#define IDX_MIXER_MODEMOUT      0x04
#define IDX_MIXER_BASSTREBLE    0x06
  #define MIXER_BASSTREBLE_TREBLE_VOLUME_MASK	0x000e
  #define MIXER_BASSTREBLE_BASS_VOLUME_MASK	0x0e00
#define IDX_MIXER_PCBEEP        0x08
#define IDX_MIXER_MODEMIN       0x0a
#define IDX_MIXER_MIC           0x0c
  #define MIXER_MIC_MICGAIN_20DB_ENHANCEMENT_MASK	0x0040
#define IDX_MIXER_LINEIN        0x0e
#define IDX_MIXER_CDAUDIO       0x10
#define IDX_MIXER_VIDEO         0x12
#define IDX_MIXER_AUX           0x14
#define IDX_MIXER_WAVEOUT       0x16
#define IDX_MIXER_FMSYNTH       0x18
#define IDX_MIXER_REC_SELECT    0x1a
  #define MIXER_REC_SELECT_MIC		0x00
  #define MIXER_REC_SELECT_CD		0x01
  #define MIXER_REC_SELECT_VIDEO	0x02
  #define MIXER_REC_SELECT_AUX		0x03
  #define MIXER_REC_SELECT_LINEIN	0x04
  #define MIXER_REC_SELECT_MIXSTEREO	0x05
  #define MIXER_REC_SELECT_MIXMONO	0x06
  #define MIXER_REC_SELECT_MONOIN	0x07
#define IDX_MIXER_REC_VOLUME    0x1c
#define IDX_MIXER_ADVCTL1       0x1e
  /*                                */
  #define MIXER_ADVCTL1_3DWIDTH_MASK	0x000e
  #define MIXER_ADVCTL1_HIFI3D_MASK	0x0300 /*                                                                                                                                                                                                                */
#define IDX_MIXER_ADVCTL2       0x20 /*                                     */
  /*                                */
  #define MIXER_ADVCTL2_LPBK		0x0080 /*                                                                          */
  #define MIXER_ADVCTL2_MS		0x0100 /*                                                             */
  #define MIXER_ADVCTL2_MIX		0x0200 /*                                                                   */
  #define MIXER_ADVCTL2_3D		0x2000 /*                     */
  #define MIXER_ADVCTL2_POP		0x8000 /*                                   */
  
#define IDX_MIXER_SOMETHING30H	0x30 /*                      */

/*                       */
#define SET_CHAN_LEFT	1
#define SET_CHAN_RIGHT	2

/*                                                          */
#define AZF_ALIGN(x) (((x) + 3) & (~3))

#endif /*                    */
