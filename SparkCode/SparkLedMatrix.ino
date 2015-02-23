#include "LedControl.h"

#define MATRIX_PER_LINE 3
#define LINE_COUNT 2
#define SPARK_API_MSG_SIZE 63


LedControl* lines[LINE_COUNT];

uint8_t cs_0 = A5;
uint8_t clk_0 = A6;
uint8_t din_0 = A7;

uint8_t cs_1 = D0;
uint8_t clk_1 = D1;
uint8_t din_1 = D2;

char message[SPARK_API_MSG_SIZE];
char recvBuffer[SPARK_API_MSG_SIZE];
int recvBufferLength = 0;

bool newMessage = false;
int active_line = 0;

void setup() {
    lines[0] = new LedControl(din_0, clk_0, cs_0, MATRIX_PER_LINE); // DIN, CLK, CS, HowManyDisplays
    lines[1] = new LedControl(din_1, clk_1, cs_1, MATRIX_PER_LINE); // DIN, CLK, CS, HowManyDisplays

    for (int j = 0; j < LINE_COUNT; j++) {
        for (int i = 0; i < MATRIX_PER_LINE; i++) {
            lines[j]->shutdown(i,false);
            lines[j]->setIntensity(i,8);
        }
    }

    Spark.variable("recvBuffer", recvBuffer, STRING);
    Spark.variable("activeLine", &active_line, INT);
    Spark.function("setMessage", setMessage);
    Spark.function("setActiveLine", setActiveLine);
}

void loop() {
    if (newMessage) {
        strcpy(message, recvBuffer);
        newMessage = false;
    }

    lines[active_line]->scrollTextTrimSpaces(message, recvBufferLength, 50);
    lines[active_line]->setTextTrimSpaces(message, recvBufferLength);

    delay(1000);
}

int setMessage(String msg) {
        recvBufferLength = msg.length() + 1;
        msg.toCharArray(recvBuffer, recvBufferLength);
        newMessage = true;
        return recvBufferLength - 1;
}

int setActiveLine(String msg) {
    int new_active_line = msg.toInt();
    if(new_active_line < 0 || new_active_line >= LINE_COUNT) {
        return -1;
    } else {
        active_line = new_active_line;
    }

    return active_line;
}
