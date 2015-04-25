#include "DisplayLine.h"

DisplayLine::DisplayLine(int dataPin, int clkPin, int csPin, int numDevices) {
    this->ledDisplay = new LedControl(dataPin, clkPin, csPin, numDevices);

    this->colsTable = new ColumnsTable();
    colsTable->columns = NULL;
    colsTable->columnsCount = 0;

    this->displayCount = numDevices;
    this->scrollIndex = 0;
    this->scrollDelay = 0;
    this->messageLength = 0;
}

DisplayLine::~DisplayLine() {
    delete(this->colsTable);
    delete(this->ledDisplay);
}

void DisplayLine::activate(int intensity) {
    for (int i = 0; i < this->displayCount; i++) {
        this->ledDisplay->shutdown(i, false);
        this->ledDisplay->setIntensity(i, intensity);
    }

    this->clear();
}

void DisplayLine::deactivate() {
    this->clear();

    for (int i = 0; i < this->displayCount; i++) {
        this->ledDisplay->shutdown(i,true);
    }
}

void DisplayLine::setText(char *text, int length) {
    strcpy(this->message, text);
    this->messageLength = length;
    this->ledDisplay->buildTrimmedText(this->message, this->messageLength, this->colsTable, this->scrollDelay != 0);
    this->clear();
    this->scrollIndex = 0;
}

void DisplayLine::refreshDisplay() {
    if (this->colsTable->columnsCount == 0 || this->colsTable->columns == NULL) {
        this->clear();
    } else {
        if (this->scrollIndex == this->colsTable->columnsCount - this->ledDisplay->getColumnsCount()) {
            this->scrollIndex = 0;
        }

        this->ledDisplay->displayTrimmedText(this->colsTable, this->scrollIndex);

        if (this->scrollDelay != 0) {
            this->scrollIndex++;
            delay(this->scrollDelay);
        }
    }
}

void DisplayLine::clear() {
    this->ledDisplay->clearAllDisplays();
}

void DisplayLine::setScrollDelay(int scrollDelay) {
    this->scrollDelay = scrollDelay;
}
