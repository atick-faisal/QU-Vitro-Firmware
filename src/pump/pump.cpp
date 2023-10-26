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

PumpConfig pumpConfig = PumpConfig{PERILSTALTIC, 1000, 100};
uint16_t pauseBetweenSteps = pumpConfig.flowPeriod / N_FLOW_POINTS;

static uint8_t getCorrectedMotorSpeed(uint8_t targetFlow, uint8_t currentFlow) {
    // ... Implement PID control here
    uint8_t correctedSpeed = targetFlow;
    return correctedSpeed;
}

void controlPump() {
    for (uint8_t i = 0; i < N_FLOW_POINTS; i++) {
        unsigned long waitUntil = millis() + pauseBetweenSteps;
        measuredFlowRate[i] = getFlowRate(i);
        uint8_t motorSpeed =
            getCorrectedMotorSpeed(targetFlowRate[i], measuredFlowRate[i]);

        if (pumpConfig.pumpType == PERILSTALTIC) {
#ifdef PWM_MODE_ARDUINO
            analogWrite(MOTOR_PIN, motorSpeed);
#elif defined(PWM_MODE_ESP32)
            ledcWrite(PWM_CHANNEL, motorSpeed);
#endif
        } else if (pumpConfig.pumpType == SYRINGE) {
            // TODO(Implement this)
        }

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
    writeFlowRates(measuredFlowRate);
}

void setPumpConfig(uint8_t pumpType, uint16_t flowPeriod,
                   uint16_t chipDiameter) {
    pumpConfig.pumpType = pumpType == 0 ? SYRINGE : PERILSTALTIC;
    pumpConfig.flowPeriod = flowPeriod;
    pumpConfig.chipDiameter = chipDiameter;
    pauseBetweenSteps = pumpConfig.flowPeriod / N_FLOW_POINTS;
}