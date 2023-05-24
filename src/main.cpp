#include <Arduino.h>

const char *DELIMETER = ",";
const uint8_t MOTOR_PIN = 10;
const uint8_t N_DATA_POINTS = 50;
const uint8_t BUFFER_SIZE = 255;
const uint32_t FLOW_PERIOD = 2000;
const uint32_t WAIT_THRESHOLD = 3000;
uint8_t flowProfile[N_DATA_POINTS];

void initializeFlowProfile();
uint8_t getSpeed(uint8_t step, uint8_t n_steps);
void deserialize(char *stream, uint8_t *values, size_t length,
                 const char *delimiter);
void applyMotorSpeeds(uint8_t *speeds, size_t length, uint32_t period,
                      uint8_t motorPin);
void printValues(uint8_t *array, size_t length);
void clearBuffer(char *buffer, size_t length);
void resetSettings();
void blink();

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
    if (Serial.available()) {
        motorFlag = false;
        while (Serial.available()) {
            char c = (char)Serial.read();
            // Serial.print(c);
            if (c == '\r' || c == '\n') continue;
            if (c == ',') commaCount++;
            buffer[count++] = c;
            delay(1);
        }
        if (commaCount >= N_DATA_POINTS - 1) {
            buffer[count] = '\0';
            strcpy(temp, buffer);
            // delay(1000);
            deserialize(temp, flowProfile, N_DATA_POINTS, DELIMETER);
            resetSettings();
        }
    }
    if (motorFlag) {
        applyMotorSpeeds(flowProfile, N_DATA_POINTS, FLOW_PERIOD, MOTOR_PIN);
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
    for (int i = 0; i < N_DATA_POINTS; i++) {
        flowProfile[i] = getSpeed(i, N_DATA_POINTS);
    }
}

void deserialize(char *stream, uint8_t *values, size_t length,
                 const char *delimiter) {
    uint8_t idx = 0;
    char *token = strtok(stream, delimiter);
    while (token != NULL) {
        values[idx++] = (uint8_t)atoi(token);
        token = strtok(NULL, delimiter);
        if (idx == length) break;
    }
    delay(1000);
    if (idx == 50)
        blink();
    else
        digitalWrite(LED_BUILTIN, HIGH);
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
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
    }
}
