#ifndef PUMP_CONFIG
#define PUMP_CONFIG

#include <Arduino.h>

// ... Peristaltic pump motor pin
const uint8_t MOTOR_PIN = 10;

// ... Buffer size for reading and writing flow profile
const uint8_t BUFFER_SIZE = 255;

// ... Number of data-points in flow profile
const uint8_t N_FLOW_POINTS = 50;

// ... Duration of one flow profile in millisecond
const uint16_t FLOW_PERIOD = 2000;

// ... Pause between each step
const uint16_t PAUSE_BETWEEN_STEPS = (uint16_t)(FLOW_PERIOD / N_FLOW_POINTS);

// ... Start and end char of flow profile
// ... e.g. <0,1,4,...,255,....>
const char FLOW_PROFILE_START_FLAG = '<';
const char FLOW_PROFILE_END_FLAG = '>';

#endif