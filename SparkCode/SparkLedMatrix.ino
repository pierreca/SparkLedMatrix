#include "LedControl.h"

LedControl *led;

uint8_t data = A5;
uint8_t load = A4;
uint8_t myclock = A3;

byte spaceChar = 0;

uint8_t displayCount = 2;
uint8_t colsPerDisplay = 8;
uint8_t maxCols = displayCount * colsPerDisplay;

void setup() {
    led = new LedControl(data, myclock, load, displayCount); //DIN,CLK,CS,HowManyDisplays

    for (int i = 0; i < displayCount; i++) {
        led->shutdown(i,false);
        led->setIntensity(i,8);
    }
}

void loop() {
    scrollTextTrimSpaces("hello, world!", 13, 100);
    delay(1000);
}

void scrollTextTrimSpaces(char *message, int messageLength, int speed) {
    // First compute the column table.
    byte columns[messageLength * 8 + maxCols * 2]; // 8 columns per letter by default + 2 times blank screens (before / after the message)
    bool alreadyHasSpace = false;
    int currentColumnIndex = 0;

    // add some space at the beginning
    for (int i = 0; i < maxCols; i++) {
        columns[currentColumnIndex] = spaceChar;
        currentColumnIndex++;
    }

    // scroll through letters and for each letter, copy columns, trimming all but one whitespace column.
    for(int i = 0; i < messageLength; i++) {
        for (int j = 0; j < 8; j++) {
            byte candidate = cp437_font[message[i]][j];
            
            if (alreadyHasSpace && candidate == spaceChar) {
                continue;
            } else if (alreadyHasSpace && candidate != spaceChar) {
                alreadyHasSpace = false;
            } else if (!alreadyHasSpace && candidate == spaceChar) {
                alreadyHasSpace = true;
            }

            columns[currentColumnIndex] = candidate;
            currentColumnIndex++;
        }
    }

    // add some space at the end
    for (int i = 0; i < maxCols; i++) {
        columns[currentColumnIndex] = spaceChar;
        currentColumnIndex++;
    }

    // clear displays
    for (int i = 0; i < displayCount; i++) {
        led->clearDisplay(i);
    }

    // then scroll through the columns table and draw each time.
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
