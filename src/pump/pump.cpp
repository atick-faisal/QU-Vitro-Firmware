// Copyright 2023 Atick Faisal

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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

        flowRates[i] = getFlowRate();
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
