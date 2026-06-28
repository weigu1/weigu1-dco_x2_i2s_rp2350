/* dco_x2_i2s_rp2350_minimal
 *
 * All credits to Craig Barnes https://github.com/craigyjp
 * 
 * Reduced version by weigu.lu and jcf to better understand the code
 * 
 * Pico 2 with WS2812b LED on GPIO16 or Waveshare RP2350-zero
 *
 * Wiring:
 *   MIDI IN   -> GPIO1  (Serial1 RX)
 *   I2S BCLK  -> GPIO9  (PCM5102 BCK)
 *   I2S LRCK  -> GPIO10 (PCM5102 LRCK)
 *   I2S DATA  -> GPIO11 (PCM5102 DIN)
 *   on PCM5102 breakout board DCO1 -> Left channel, DCO2 -> Right channel
 *
 * Dependencies:
 *   - Arduino MIDI Library (FortySevenEffects) via Library Manager
 *
 * Change VOICE_CHANNEL per stamp (1-8)
 * CONTROL_CHANNEL is the same on all stamps */

#include <Arduino.h>
#include <MIDI.h>
#include <string.h>
#include "hardware/timer.h"
#include "hardware/pwm.h"
#include "i2s_audio.h"
#include "dco_engine.h"
#include "dco_x2_i2s_rp2350_definitions.h"
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel led(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

/* ------ MIDI instance on Serial1 (GPIO0=RX) ------ */
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

/* ------- MIDI callbacks ------ */ 
void myNoteOn(byte channel, byte note, byte velocity) {
    if (channel == VOICE_CHANNEL) {        
        DCO_NoteOn(note, velocity);
        led.setPixelColor(0, led.Color(0, 0, 255));  // blue on note on
        led.show();
    }
}

void myNoteOff(byte channel, byte note, byte velocity) {
    if (channel == VOICE_CHANNEL) {        
        DCO_NoteOff(note);
        led.setPixelColor(0, led.Color(0, 0, 0));    // off on note off
        led.show();
    }
}

void myControlChange(byte channel, byte cc, byte value) {
    if (channel == CONTROL_CHANNEL) {
        switch (cc) {
            /* --- DCO1 --- */
            case CC_MOD_WHEEL:        DCO_SetModWheel(value);        break;
            case CC_PORTAMENTO_TIME:  DCO_SetPortamentoRate(value);  break;
            case CC_PORTAMENTO_SW:    DCO_SetPortamento(value);      break;
            case CC_DCO1_OCTAVE:      DCO_SetOctave(value);          break;
            case CC_DCO2_OCTAVE:      DCO2_SetOctave(value);         break;
            case CC_DCO1_SAW_DETUNE:  DCO_SetSawDetune(value);       break;
            case CC_DCO1_SAW_COUNT:   DCO_SetSawCount(value);        break;
            case CC_DCO1_PULSE_WIDTH: DCO_SetPulseWidth(value);      break;
            case CC_DCO1_PWM_DEPTH:   DCO_SetPWMDepth(value);        break;
            case CC_DCO1_SAW_LEVEL:   DCO_SetSawLevel(value);        break;
            case CC_DCO1_PULSE_LEVEL: DCO_SetPulseLevel(value);      break;
            case CC_DCO1_TRI_LEVEL:   DCO_SetSubLevel(value);        break;
            case CC_PITCHBEND_RANGE:  DCO_SetPitchBendRange(value);  break;
            case CC_LFO1_RATE:        DCO_SetLFORate(value);         break;
            case CC_LFO1_WAVEFORM:    DCO_SetLFOWaveform(value);     break;
            case CC_LFO1_FM_DEPTH:    DCO_SetLFOFMDepth(value);      break;
            case CC_LFO1_DELAY_TIME:  DCO_SetLFO1DelayTime(value);   break;
            case CC_LFO1_DELAY_RAMP:  DCO_SetLFO1DelayRamp(value);   break;
            case CC_LFO1_RETRIG:      DCO_SetLFO1DelayRetrig(value); break;
            case CC_NOTES_HELD:       DCO_SetNotesHeld(value);       break;
            case CC_LFO2_RATE:       DCO_SetLFO2Rate(value);        break;
            case CC_LFO2_WAVEFORM:   DCO_SetLFO2Waveform(value);    break;
            case CC_DCO1_LFO2_PWM:   DCO_SetLFO2PWMDepth(value);    break;
            case CC_DCO2_LFO2_PWM:   DCO_SetLFO2DCO2PWMDepth(value); break;
            case CC_SYNC_MODE:       DCO_SetSyncMode(value);        break;
            case CC_ENV_ATTACK:      DCO_SetEnvAttack(value);       break;
            case CC_ENV_DECAY:       DCO_SetEnvDecay(value);        break;
            case CC_ENV_SUSTAIN:     DCO_SetEnvSustain(value);      break;
            case CC_ENV_RELEASE:     DCO_SetEnvRelease(value);      break;
            case CC_ENV_DEPTH:       DCO_SetEnvSweepDepth(value);    break;
            case CC_ENV_DCO1_PWM:    DCO_SetEnvDCO1PWMDepth(value);  break;
            case CC_ENV_DCO2_PWM:    DCO_SetEnvDCO2PWMDepth(value);  break;
            case CC_AT_FM_DEPTH:     DCO_SetAftertouchFMDepth(value);  break;
            case CC_MW_FM_DEPTH:     DCO_SetModWheelFMDepth(value);    break;
            /* --- DCO2 --- */
            case CC_DCO2_SAW_LEVEL:   DCO2_SetSawLevel(value);      break;
            case CC_DCO2_PULSE_WIDTH: DCO2_SetPulseWidth(value);    break;
            case CC_DCO2_PULSE_LEVEL: DCO2_SetPulseLevel(value);    break;
            case CC_DCO2_SUB_LEVEL:   DCO2_SetSubLevel(value);      break;
            case CC_DCO2_DETUNE:      DCO2_SetDetune(value);        break;
            case CC_DCO2_INTERVAL:    DCO2_SetInterval(value);      break;
            case CC_DCO2_PWM_DEPTH:   DCO2_SetPWMDepth(value);      break;
            case CC_DCO2_ADC_PWM:     DCO2_SetADCPWMDepth(value);   break;
            default: break;
        }
    }
}

void myPitchBend(byte channel, int bend) {
    if (channel == CONTROL_CHANNEL)
        DCO_PitchBend((uint16_t)(bend + 8192));
}

void myAfterTouch(byte channel, byte pressure) {
    if (channel == CONTROL_CHANNEL) {        
        DCO_SetAftertouch(pressure);
    }
}

/* ------ I2S audio callback (both DCOs processed together) ------ */  
void I2S_CB_FillBuffer(float *out1, float *out2, int len) {
    DCO_ProcessBoth(out1, out2, len); // DCO1: left ch., DCO2: right ch.
}

/* ------ Setup ------ */
void setup() {
    Serial.begin(115200); // for debugging  
    int timeout = 1000; // multiple of 10ms
    while (!Serial && timeout > 0) {
      delay(10);
      timeout--;
    }    
    Serial.println("Starting program...");
    led.begin();
    led.setBrightness(50);  // 0-255, don't need full brightness
    led.clear();
    led.show();

    /* MIDI */
    MIDI.begin(0);
    MIDI.setHandleNoteOn(myNoteOn);
    MIDI.setHandleNoteOff(myNoteOff);
    MIDI.setHandleControlChange(myControlChange);
    MIDI.setHandlePitchBend(myPitchBend);
    MIDI.setHandleAfterTouchChannel(myAfterTouch);

    /* DCO engine */
    DCO_Init(48000.0f);

    /* DCO1 defaults */
    DCO_SetOctave(32);          // 8' default */
    DCO2_SetOctave(32);         // 8' default */
    DCO_SetSyncMode(0);         // sync off by default */
    DCO_SetEnvAttack(64);       // medium attack       */
    DCO_SetEnvDecay(64);        // medium decay        */
    DCO_SetEnvSustain(80);      // sustain at 63%      */
    DCO_SetEnvRelease(64);      // medium release      */
    DCO_SetEnvSweepDepth(0);    // DCO2 pitch sweep off    */
    DCO_SetEnvDCO1PWMDepth(0);  // DCO1 PWM sweep off      */
    DCO_SetEnvDCO2PWMDepth(0);  // DCO2 PWM sweep off      */
    DCO_SetPortamento(0);       // off by default */
    DCO_SetPortamentoRate(0);   // fastest rate   */
    DCO_SetAftertouchFMDepth(0);
    DCO_SetModWheelFMDepth(0);
    DCO_SetSawLevel(100);
    DCO_SetSubLevel(0); 
    DCO_SetSawCount(20);
    DCO_SetSawDetune(0);
    DCO_SetPulseLevel(0);
    DCO_SetPulseWidth(64);    
    DCO_SetPitchBendRange(2);
    DCO_SetLFORate(20);
    DCO_SetLFOWaveform(127);    // sawtooth */
    DCO_SetLFOFMDepth(0);
    DCO_SetLFO1DelayTime(0);    // no delay by default */
    DCO_SetLFO1DelayRamp(0);    // instant onset by default */
    DCO_SetLFO1DelayRetrig(127); // retrigger on by default */
    DCO_SetLFO2Rate(20);
    DCO_SetLFO2Waveform(0);     // triangle */
    DCO_SetLFO2PWMDepth(0);
    DCO_SetLFO2DCO2PWMDepth(0);

    /* --- DCO2 defaults - silent until enabled via CC --- */
    DCO2_SetSawLevel(100);        // saw off until enabled
    DCO2_SetPulseWidth(64);     // 50% square
    DCO2_SetPulseLevel(0);      // off until enabled
    DCO2_SetSubLevel(0);        // off until enabled
    DCO2_SetDetune(64);         // centre = 0 cents
    DCO2_SetInterval(64);       // centre = 0 semitones
    DCO2_SetPWMDepth(0);
    /* --- DCO2 LFO PWM now controlled via CC_LFO2_DCO2_PWM (CC52) --- */
    DCO2_SetADCPWMDepth(0);

    /* --- I2S audio - init last --- */
    I2SAudio_Init(I2S_BCLK_PIN, I2S_LRCK_PIN, I2S_DATA_PIN, 48000);
    Serial.println("Setup done!");    
  }
    
/* ------ Loop --- */
void loop() {    
    MIDI.read();    
    I2SAudio_Process();
    //Serial.println(".");
}