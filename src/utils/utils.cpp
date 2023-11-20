/**************************************************************************/
/*  utils.cpp                                                             */
/**************************************************************************/
/*                          Author: Atick Faisal                          */
/*                           https://atick.dev/                           */
/**************************************************************************/
/* Copyright (c) 2023-present Atick Faisal                                */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "utils.h"

uint8_t targetFlowRate[N_FLOW_POINTS];
uint8_t measuredFlowRate[N_FLOW_POINTS];

void blink() {
    for (int i = 0; i < 10; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(40);
        digitalWrite(LED_BUILTIN, LOW);
        delay(40);
    }
}

void initializePins() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(MOT1_DIR_PIN, OUTPUT);
    pinMode(MOT1_STEP_PIN, OUTPUT);
    pinMode(HOME_SW1_PIN, INPUT_PULLUP);

#ifdef PWM_MODE_ESP32
    // Setup PWM for ESP32
    ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOLUTION);
    ledcAttachPin(MOTOR_PIN, PWM_CHANNEL);
#endif
}

static uint8_t getSpeed(uint8_t step, uint8_t n_steps) {
    double speed = sin(((double)step / (double)n_steps) * 2 * PI);
    if (speed < 0) speed = 0;
    return (uint8_t)round(speed * 255);
}

void initializeFlowProfile() {
    for (int i = 0; i < N_FLOW_POINTS; i++) {
        targetFlowRate[i] = getSpeed(i, N_FLOW_POINTS);
        measuredFlowRate[i] = 0;
    }
}