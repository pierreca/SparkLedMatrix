#include "DisplayLine.h"

#define MATRIX_PER_LINE 8
#define LINE_COUNT 2
#define SPARK_API_MSG_SIZE 63

DisplayLine* lines[LINE_COUNT];

uint8_t cs_0 = A5;
uint8_t clk_0 = A6;
uint8_t din_0 = A7;

uint8_t cs_1 = D0;
uint8_t clk_1 = D1;
uint8_t din_1 = D2;

char recvBuffer[SPARK_API_MSG_SIZE];
int recvBufferLength = 0;

bool newMessage = false;
int activeLine = 0;

void setup() {
    lines[0] = new DisplayLine(din_0, clk_0, cs_0, MATRIX_PER_LINE); // DIN, CLK, CS, HowManyDisplays
    lines[1] = new DisplayLine(din_1, clk_1, cs_1, MATRIX_PER_LINE); // DIN, CLK, CS, HowManyDisplays

    lines[0]->activate(8);
    lines[0]->setScrollDelay(50);
    lines[0]->setText("Hello!", 7);

    lines[1]->activate(8);

    Spark.variable("recvBuffer", recvBuffer, STRING);
    Spark.variable("activeLine", &activeLine, INT);
    Spark.variable("recvBufferLength", &recvBufferLength, INT);
    Spark.function("setMessage", setMessage);
    Spark.function("setActiveLine", setActiveLine);
    Spark.function("setScrollDelay", setScrollDelay);
}

void loop() {
    if (newMessage) {
        lines[activeLine]->setText(recvBuffer, recvBufferLength);
        newMessage = false;
    }

    for (int i = 0; i < LINE_COUNT; i++) {
        lines[i]->refreshDisplay();
    }
}

int setMessage(String msg) {
    recvBufferLength = msg.length() + 1;
    msg.toCharArray(recvBuffer, recvBufferLength);
    newMessage = true;
    return recvBufferLength - 1;
}

int setActiveLine(String msg) {
    int new_activeLine = msg.toInt();

    if (new_activeLine < 0 || new_activeLine >= LINE_COUNT) {
        return -1;
    } else {
        activeLine = new_activeLine;
    }

    return activeLine;
}

int setScrollDelay(String msg) {
    int new_scrollDelay = msg.toInt();
    if (new_scrollDelay < 0) {
        return -1;
    } else {
        lines[activeLine]->setScrollDelay(new_scrollDelay);
    }

    return new_scrollDelay;
}
