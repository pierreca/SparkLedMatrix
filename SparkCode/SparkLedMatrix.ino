#include "LedControl.h"

LedControl *led;

uint8_t data = A5;
uint8_t load = A4;
uint8_t clk = A3;

uint8_t displayCount = 2;
uint8_t colsPerDisplay = 8;
uint8_t maxCols = displayCount * colsPerDisplay;

char message[64];
char recvBuffer[64];
int recvBufferLength = 0;
bool newMessage = false;

void setup() {
    led = new LedControl(data, clk, load, displayCount); // DIN, CLK, CS, HowManyDisplays

    for (int i = 0; i < displayCount; i++) {
        led->shutdown(i,false);
        led->setIntensity(i,8);
    }

    Spark.variable("recvBuffer", recvBuffer, STRING);
    Spark.function("display", displayMessage);
}

void loop() {
    if (newMessage) {
        strcpy(message, recvBuffer);
        newMessage = false;
    }

    scrollTextTrimSpaces(message, recvBufferLength, 50);
    delay(1000);
}

int displayMessage(String msg)
{
    recvBufferLength = msg.length() + 1;
    msg.toCharArray(recvBuffer, recvBufferLength);
    newMessage = true;
    return recvBufferLength - 1;
}

void scrollTextTrimSpaces(char *message, int messageLength, int speed) {
    const byte emptyColumn = 0;
    const byte spaceWidth = 4;

    byte columns[messageLength * 8 + maxCols * 2]; // 8 columns per letter by default + 2 times blank screens (before / after the message)
    bool alreadyHasSpace = false;
    int currentColumnIndex = 0;

    // STEP 1: Compute the column table
    // add some space at the beginning
    for (int i = 0; i < maxCols; i++) {
        columns[currentColumnIndex] = emptyColumn;
        currentColumnIndex++;
    }

    // scroll through letters and for each letter, copy columns, trimming all but one whitespace column.
    for(int i = 0; i < messageLength; i++) {
        if (message[i] == ' ') {
            for (int j = 0; j < spaceWidth; j++) {
                columns[currentColumnIndex] = emptyColumn;
                currentColumnIndex++;
            }
        } else {
            for (int j = 0; j < 8; j++) {
                byte candidate = cp437_font[message[i]][j];

                if (alreadyHasSpace && candidate == emptyColumn) {
                    continue;
                } else if (alreadyHasSpace && candidate != emptyColumn) {
                    alreadyHasSpace = false;
                } else if (!alreadyHasSpace && candidate == emptyColumn) {
                    alreadyHasSpace = true;
                }

                columns[currentColumnIndex] = candidate;
                currentColumnIndex++;
            }
        }
    }

    // add some space at the end
    for (int i = 0; i < maxCols; i++) {
        columns[currentColumnIndex] = emptyColumn;
        currentColumnIndex++;
    }

    // STEP 2: clear displays
    for (int i = 0; i < displayCount; i++) {
        led->clearDisplay(i);
    }

    // STEP 3: scroll through the columns table and draw each time.
    for (int j = 0; j < currentColumnIndex - maxCols - 1; j++) {
        for(int i = maxCols; i >= 0; i--) {
            led->setColumn(i / colsPerDisplay, i % colsPerDisplay, columns[maxCols - i + j]);
        }
        delay(speed);
    }
}


// this one won't trim space and will just scroll text with the monospaced font cp437 from LedControl.h
void scrollText(char *message, int messageLength, int speed) {
    for (int i = 0; i < displayCount; i++) {
        led->clearDisplay(i);
    }

    for (int j = 0; j < (messageLength - 1) * 8; j++) {
        for(int i = maxCols; i >= 0; i--) {
            // i is the column on which we want to draw
            // (maxCols - i + j) / 8 is the index of the character we're looking at
            // (maxCols - i + j) % 8 is the column of the character we want to draw
            led->setColumn(i / 8, i % 8, cp437_font[message[(maxCols - i + j) / 8]][(maxCols - i + j) % 8]);
        }
        delay(speed);
    }
}
