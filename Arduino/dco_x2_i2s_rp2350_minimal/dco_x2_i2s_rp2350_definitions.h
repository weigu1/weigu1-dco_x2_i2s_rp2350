/* Definitions file for dco_x2_i2s_rp2350.ino */

/* ------ Pin assignments ------ */
#define I2S_BCLK_PIN    9
#define I2S_LRCK_PIN    10
#define I2S_DATA_PIN    11

/* ------ WS2812b LED assignments ------ */
#define LED_PIN         16
#define LED_COUNT       1 // only one LED

/* --- FV1 effects processor switch outputs - 3.3V logic, CC controlled --- */
#define FV1_PIN_0       2   // eeprom 1
#define FV1_PIN_1       4   // eeprom 2
#define FV1_PIN_2       8   // eeprom 3
#define FV1_PIN_3       12  // button 0
#define FV1_PIN_4       13  // button 2
#define FV1_PIN_5       14  // button 2
#define FV1_PIN_6       15  // internal - external

#define FV1_PIN_COUNT   7

/* ------ MIDI channels (1-based) ------ */
#define VOICE_CHANNEL    1      // <<< change per stamp: 1-8
#define CONTROL_CHANNEL  1      // shared across all stamps

/* ------  DCO1: CC assignments on the control channel ------ */
/* --- Standard MIDI --- */
#define CC_MOD_WHEEL        1   // modulation wheel
#define CC_PORTAMENTO_TIME  5   // portamento rate
#define CC_PORTAMENTO_SW    65  // portamento on/off (>=64=on)
#define CC_DCO1_OCTAVE   15     // octave switch DCO1
#define CC_DCO2_OCTAVE   16     // octave switch DCO2
/* --- DCO1 oscillator --- */
#define CC_DCO1_SAW_DETUNE  17  // saw detune spread
#define CC_DCO1_SAW_COUNT   18  // saw voice count 1-5
#define CC_DCO1_PULSE_WIDTH 19  // DCO1 pulse width
#define CC_DCO1_PWM_DEPTH   20  // DCO1 mod wheel PWM depth
#define CC_DCO1_SAW_LEVEL   21  // saw level in mix
#define CC_DCO1_PULSE_LEVEL 22  // DCO1 pulse level in mix
#define CC_DCO1_TRI_LEVEL   23  // DCO1 triangle level
/* --- Pitch --- */
#define CC_PITCHBEND_RANGE  24  // pitchbend range 1-12 semitones
/* --- LFO1 (FM/vibrato) --- */
#define CC_LFO1_RATE        25  // LFO1 rate 0.1-20Hz
#define CC_LFO1_WAVEFORM    26  // LFO1 waveform tri/sq/saw
#define CC_LFO1_FM_DEPTH    27  // LFO1 -> FM depth
#define CC_LFO1_DELAY_TIME  55  // LFO1 delay time before onset
#define CC_LFO1_DELAY_RAMP  56  // LFO1 ramp up time after delay
#define CC_LFO1_RETRIG      57  // >= 64 retrigger on, < 64 legato
#define CC_NOTES_HELD       58  // >= 64 notes held, < 64 all released
#define CC_AT_FM_DEPTH      28  // aftertouch -> vibrato depth
#define CC_MW_FM_DEPTH      29  // mod wheel -> FM depth
#define CC_ADC_FM_DEPTH     30  // ADC FM input depth
#define CC_XMOD_DEPTH       53  // X-MOD depth DCO2->DCO1 freq
/* --- LFO2 (PWM) --- */
#define CC_LFO2_RATE        31  // LFO2 rate 0.1-20Hz
#define CC_LFO2_WAVEFORM    32  // LFO2 waveform tri/sq/saw
#define CC_DCO1_LFO2_PWM    33  // LFO2 -> DCO1 PWM depth
#define CC_DCO2_LFO2_PWM    34  // LFO2 -> DCO2 PWM depth
#define CC_DCO1_ADC_PWM     35  // DCO1 ADC PWM input depth
/* --- DCO2 oscillator --- */
#define CC_DCO2_SAW_LEVEL   36  // DCO2 sawtooth level
#define CC_DCO2_PULSE_WIDTH 37  // DCO2 pulse width
#define CC_DCO2_PULSE_LEVEL 38  // DCO2 pulse level
#define CC_DCO2_SUB_LEVEL   39  // DCO2 sub level
#define CC_DCO2_PWM_DEPTH   40  // DCO2 mod wheel PWM depth
#define CC_DCO2_ADC_PWM     41  // DCO2 ADC PWM input depth
#define CC_DCO2_DETUNE      42  // DCO2 detune cents, centre=64
#define CC_DCO2_INTERVAL    43  // DCO2 interval semitones, centre=64
/* --- Oscillator sync --- */
#define CC_SYNC_MODE        44  // 0-42=off 43-84=soft 85-127=hard
/* --- DCO2 sweep envelope --- */
#define CC_ENV_ATTACK       45  // attack  0=slow 127=fast
#define CC_ENV_DECAY        46  // decay   0=slow 127=fast
#define CC_ENV_SUSTAIN      47  // sustain level
#define CC_ENV_RELEASE      48  // release 0=slow 127=fast
#define CC_ENV_DEPTH        49  // envelope -> DCO2 pitch depth
#define CC_KEYTRACK_DEPTH   54  // keytrack CV output scaling
/* FV1 effects processor switch outputs - 0=low, 127=high */
#define CC_FV1_SW_0     60
#define CC_FV1_SW_1     61
#define CC_FV1_SW_2     62
#define CC_FV1_SW_3     63
#define CC_FV1_SW_4     64
#define CC_FV1_SW_5     66
#define CC_FV1_SW_6     67
#define CC_ENV_DCO1_PWM     50  // envelope -> DCO1 PWM depth
#define CC_ENV_DCO2_PWM     51  // envelope -> DCO2 PWM depth


