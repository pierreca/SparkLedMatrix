#include "LedControl.h"

#define MATRIX_PER_LINE 8
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
int activeLine = 0;
int scrollSpeed = 0;
int scrollIndex = 0;
ColumnsTable *colsTable = NULL;
uint8_t maxCols = 0;

void setup() {
    lines[0] = new LedControl(din_0, clk_0, cs_0, MATRIX_PER_LINE); // DIN, CLK, CS, HowManyDisplays
    lines[1] = new LedControl(din_1, clk_1, cs_1, MATRIX_PER_LINE); // DIN, CLK, CS, HowManyDisplays

    maxCols = lines[0]->getColumnsCount();

    colsTable = new ColumnsTable();
    colsTable->columns = NULL;
    colsTable->columnsCount = 0;

    for (int j = 0; j < LINE_COUNT; j++) {
        for (int i = 0; i < MATRIX_PER_LINE; i++) {
            lines[j]->shutdown(i,false);
            lines[j]->setIntensity(i,8);
        }
    }

    String str = String("Hello!");
    setMessage(str);

    Spark.variable("recvBuffer", recvBuffer, STRING);
    Spark.variable("activeLine", &activeLine, INT);
    Spark.variable("scrollSpeed", &scrollSpeed, INT);
    Spark.function("setMessage", setMessage);
    Spark.function("setActiveLine", setActiveLine);
    Spark.function("setScrollSpeed", setScrollSpeed);
}

void loop() {
    if (newMessage) {
        strcpy(message, recvBuffer);
        lines[activeLine]->buildTrimmedText(message, recvBufferLength, colsTable, scrollSpeed != 0);
        lines[activeLine]->clearAllDisplays();
        scrollIndex = 0;
        newMessage = false;
    }

    if (scrollIndex == colsTable->columnsCount - maxCols) {
        scrollIndex = 0;
    }

    lines[activeLine]->displayTrimmedText(colsTable, scrollIndex);

    if(scrollSpeed != 0) {
        scrollIndex++;
        delay(scrollSpeed);
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

    if(new_activeLine < 0 || new_activeLine >= LINE_COUNT) {
        return -1;
    } else {
        activeLine = new_activeLine;
    }

    return activeLine;
}

int setScrollSpeed(String msg) {
    int new_scrollSpeed = msg.toInt();
    if(new_scrollSpeed < 0) {
        return -1;
    } else {
        scrollSpeed = new_scrollSpeed;
    }

    return scrollSpeed;
}
