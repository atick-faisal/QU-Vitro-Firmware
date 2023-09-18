/*
 *  Copyright 2023 Atick Faisal
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "utils.h"

uint8_t flowProfile[N_FLOW_POINTS];
uint8_t flowRates[N_FLOW_POINTS];

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
        flowProfile[i] = getSpeed(i, N_FLOW_POINTS);
        flowRates[i] = 0;
    }
}