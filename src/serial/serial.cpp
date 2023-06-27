#include "serial.h"

uint8_t count = 0;
char buffer[BUFFER_SIZE];

static void serialize(uint8_t *array, size_t length) {
    buffer[0] = '\0';
    for (int i = 0; i < length; ++i) {
        sprintf(buffer + strlen(buffer), "%d", array[i]);
        if (i != length - 1) {
            sprintf(buffer + strlen(buffer), ",");
        }
    }
}

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

void writeFlowRates(uint8_t *flowRates) {
    serialize(flowRates, N_FLOW_POINTS);
    Serial.println(buffer);
}
