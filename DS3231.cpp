#include "DS3231.hpp"

void RealTimeDS3231::readClock(){
// send request to receive data starting at register 0
Wire.beginTransmission(0x68); // 0x68 is DS3231 device address
Wire.write((byte)0); // start at register 0
Wire.endTransmission();
Wire.requestFrom(0x68, 3); // request three bytes (seconds, minutes, hours)
while(Wire.available())
    { 
    seconds = Wire.read(); // get seconds
    minutes = Wire.read(); // get minutes
    hours = Wire.read();   // get hours

    seconds = (((seconds & 0b11110000)>>4)*10 + (seconds & 0b00001111)); // convert BCD to decimal
    minutes = (((minutes & 0b11110000)>>4)*10 + (minutes & 0b00001111)); // convert BCD to decimal
    hours = (((hours & 0b00100000)>>5)*20 + ((hours & 0b00010000)>>4)*10 + (hours & 0b00001111)); // convert BCD to decimal (assume 24 hour mode)
    }
}
