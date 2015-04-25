#include "LedControl.h"

#define SPARK_API_MSG_SIZE 63

class DisplayLine {
    private:
        LedControl *ledDisplay;
        ColumnsTable *colsTable;
        char message[SPARK_API_MSG_SIZE];
        int messageLength;
        int displayCount;
        int scrollIndex;
        int scrollDelay;

    public:
        DisplayLine(int dataPin, int clkPin, int csPin, int numDevices);
        ~DisplayLine();
        void activate(int intensity);
        void deactivate();
        void setText(char *text, int length);
        void refreshDisplay();
        void clear();
        void setScrollDelay(int scrollDelay);
};
