/**************************************************************************/
/*  pump.cpp                                                              */
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

#include "pump.h"

static uint8_t getCorrectedMotorSpeed(uint8_t targetFlow, uint8_t currentFlow) {
    // ... Implement PID control here
    uint8_t correctedSpeed = targetFlow;
    return correctedSpeed;
}

void initializePump() {
    pinMode(MOTOR_PIN, OUTPUT);
    initializeFlowProfile();
}

void controlPump() {
    for (uint8_t i = 0; i < N_FLOW_POINTS; i++) {
        unsigned long waitUntil = millis() + PAUSE_BETWEEN_STEPS;

        flowRates[i] = getFlowRate(i);
        uint8_t motorSpeed =
            getCorrectedMotorSpeed(flowProfile[i], flowRates[i]);

#ifdef PWM_MODE_ARDUINO
        analogWrite(MOTOR_PIN, motorSpeed);
#elif defined(PWM_MODE_ESP32)
        ledcWrite(PWM_CHANNEL, motorSpeed);
#endif

        // ... Check for serial data
        while (millis() < waitUntil) {
            if (Serial.available() > 0) {
                char c = (char)Serial.read();
                if (c == FLOW_PROFILE_START_FLAG) {
                    readMode = true;
                    return;
                }
            }
            delay(1);
        }
    }
    writeFlowRates(flowRates);
}
