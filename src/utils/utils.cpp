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

void initializeUtils() {
    pinMode(LED_BUILTIN, OUTPUT);
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