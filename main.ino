#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define ADRESS_RT 0x68
#define ADRESS_LIQ 0x3F
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(ADRESS_LIQ, 20, 4);

void setup()
{
    Wire.begin();
    Serial.begin(9600);
    // clear /EOSC bit
    // Sometimes necessary to ensure that the clock
    // keeps running on just battery power. Once set,
    // it shouldn't need to be reset but it's a good
    // idea to make sure.
    Wire.beginTransmission(ADRESS_RT); // address DS3231
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
    Wire.beginTransmission(ADRESS_RT); // 0x68 is DS3231 device address
    Wire.write((byte)0); // start at register 0
    Wire.endTransmission();
    Wire.requestFrom(ADRESS_RT, 6); // request three bytes (seconds, minutes, hours...)
    while(Wire.available())
        { 
        int seconds = Wire.read(); // get seconds
        int minutes = Wire.read(); // get minutes
        int hours = Wire.read();   // get hours
        int days = Wire.read();     // get days
        int months = Wire.read();   // get month
        int years = Wire.read();    // get year
    
        seconds = (((seconds & 0b11110000)>>4)*10 + (seconds & 0b00001111)); // convert BCD to decimal
        minutes = (((minutes & 0b11110000)>>4)*10 + (minutes & 0b00001111)); // convert BCD to decimal
        hours = (((hours & 0b00100000)>>5)*20 + ((hours & 0b00010000)>>4)*10 + (hours & 0b00001111)); // convert BCD to decimal (assume 24 hour mode)
        days = (((days & 0b11110000)>>4)*10 + (days & 0b00001111)); // convert BCD to decimal
        months = (((months & 0b11110000)>>4)*10 + (months & 0b00001111)); // convert BCD to decimal
        years = (((years & 0b11110000)>>4)*1000 +((years & 0b11110000)>>4)*100 +((years & 0b11110000)>>4)*10 + (years & 0b00001111)); // convert BCD to decimal
        lcd.setCursor(0,1);
        lcd.print(hours); lcd.print(":"); lcd.print(minutes); lcd.print(":"); lcd.print(seconds);
        lcd.setCursor(0,2);
        lcd.print(" date:"); lcd.print(days);lcd.print("/"); lcd.print(months);lcd.print("/"); lcd.print(years);
        }
    }