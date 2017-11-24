#include <Wire.h>

class RealTimeDS3231
{
public:
    int seconds, minutes, hours;
    void readClock();
private:
};