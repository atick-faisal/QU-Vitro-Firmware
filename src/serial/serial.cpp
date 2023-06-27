#include "serial.h"

uint8_t count = 0;
char buffer[BUFFER_SIZE];

static void deserialize(char *stream, uint8_t *values) {
    uint8_t idx = 0;
    char *token = strtok(stream, ",");
    while (token != NULL) {
        values[idx++] = (uint8_t)atoi(token);
        token = strtok(NULL, ",");
    }
}

void initializeSerial() {
    Serial.begin(BAUD_RATE);
    while (!Serial) {
        ;
    }
}

void readFlowProfile() {
    if (Serial.available() > 0) {
        char received = (char)Serial.read();
        if (received == FLOW_PROFILE_END_FLAG) {
            deserialize(buffer, flowProfile);
            readMode = false;
            count = 0;
            blink();
            return;
        }
        buffer[count++] = received;
    }
}

