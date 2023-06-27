#include <Arduino.h>

const char FLOW_PROFILE_START_FLAG = '<';
const char FLOW_PROFILE_END_FLAG = '>';

const char *DELIMETER = ",";
const uint8_t MOTOR_PIN = 10;
const uint8_t N_FLOW_POINTS = 50;
const uint8_t BUFFER_SIZE = 255;
const uint16_t FLOW_PERIOD = 2000;
const uint32_t WAIT_THRESHOLD = 3000;
uint8_t flowProfile[N_FLOW_POINTS];

const uint16_t PAUSE_BETWEEN_STEPS = (uint16_t)(FLOW_PERIOD / N_FLOW_POINTS);

bool readMode = false;

void initializeFlowProfile();
uint8_t getSpeed(uint8_t step, uint8_t n_steps);
void deserialize(char *stream, uint8_t *values);
void applyMotorSpeeds(uint8_t *speeds, size_t length, uint32_t period,
                      uint8_t motorPin);
void printValues(uint8_t *array, size_t length);
void clearBuffer(char *buffer, size_t length);
void resetSettings();
void blink();

void readFlowProfile();
void controlAndMonitorPump();

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(MOTOR_PIN, OUTPUT);
    initializeFlowProfile();
}

uint8_t count = 0;
uint8_t commaCount = 0;
char buffer[BUFFER_SIZE];
char temp[BUFFER_SIZE];
bool motorFlag = false;

void loop() {
    if (readMode) {
        readFlowProfile();
    } else {
        controlAndMonitorPump();
    }
}

void readFlowProfile() {
    if (Serial.available() > 0) {
        char received = (char)Serial.read();
        if (received == FLOW_PROFILE_END_FLAG) {
            deserialize(buffer, flowProfile);
            readMode = false;
            count = 0;
            return;
        }
        buffer[count++] = received;
    }
}

void controlAndMonitorPump() {
    for (uint8_t i = 0; i < N_FLOW_POINTS; i++) {
        unsigned long waitUntil = millis() + PAUSE_BETWEEN_STEPS;
        analogWrite(MOTOR_PIN, flowProfile[i]);
        while (millis() < waitUntil) {
            if (Serial.available() > 0) {
                char c = (char) Serial.read();
                if (c == FLOW_PROFILE_START_FLAG) {
                    digitalWrite(LED_BUILTIN, HIGH);
                    readMode = true;
                    return;
                }
            }
            delay(1);
        }
    }
}

void applyMotorSpeeds(uint8_t *speeds, size_t length, uint32_t period,
                      uint8_t motorPin) {
    uint32_t pause = (uint32_t)round((float)period / (float)length);
    for (uint8_t i = 0; i < length; i++) {
        analogWrite(motorPin, speeds[i]);
        delay(pause);
    }
}

void initializeFlowProfile() {
    for (int i = 0; i < N_FLOW_POINTS; i++) {
        flowProfile[i] = getSpeed(i, N_FLOW_POINTS);
    }
}

void deserialize(char *stream, uint8_t *values) {
    uint8_t idx = 0;
    char *token = strtok(stream, ",");
    while (token != NULL) {
        values[idx++] = (uint8_t)atoi(token);
        token = strtok(NULL, ",");
    }
    blink();
}

uint8_t getSpeed(uint8_t step, uint8_t n_steps) {
    double speed = sin(((double)step / (double)n_steps) * 2 * PI);
    if (speed < 0) speed = 0;
    return (uint8_t)round(speed * 255);
}

void printValues(uint8_t *array, size_t length) {
    for (uint8_t i = 0; i < length; i++) {
        Serial.print(array[i]);
        Serial.print("\t");
    }
    Serial.println();
}

void resetSettings() {
    // delay(1000);
    count = 0;
    commaCount = 0;
    motorFlag = true;
    clearBuffer(buffer, BUFFER_SIZE);
    // delay(1000);
}

void clearBuffer(char *buffer, size_t length) {
    for (size_t i = 0; i < length; i++) {
        buffer[i] = '0';
    }
}

void blink() {
    for (int i = 0; i < 10; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(40);
        digitalWrite(LED_BUILTIN, LOW);
        delay(40);
    }
}
