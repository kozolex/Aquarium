#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DS3231.hpp"

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);
RealTimeDS3231 realT;

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    // clear /EOSC bit
    // Sometimes necessary to ensure that the clock
    // keeps running on just battery power. Once set,
    // it shouldn't need to be reset but it's a good
    // idea to make sure.
    Wire.beginTransmission(0x68); // address DS3231
    Wire.write(0x0E); // select register
    Wire.write(0b00011100); // write register bitmap, bit 7 is /EOSC
    Wire.endTransmission();

    lcd.begin();// initialize the LCD
	// Turn on the blacklight and print a message.
	lcd.backlight();
    lcd.print("    AQUARIUM 1.0");
    
}

void loop()
{
    realT.readClock();
    lcd.setCursor(0,2);
    lcd.print(realT.hours); lcd.print(":"); lcd.print(realT.minutes); lcd.print(":"); lcd.print(realT.seconds);
}
