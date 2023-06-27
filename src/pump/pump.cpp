#include "pump.h"

static uint8_t getCorrectedMotorSpeed(uint8_t targetFlow, float currentFlow) {
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

        float flowRate = getFlowRate();
        uint8_t motorSpeed = getCorrectedMotorSpeed(flowProfile[i], flowRate);
        analogWrite(MOTOR_PIN, motorSpeed);

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
}
