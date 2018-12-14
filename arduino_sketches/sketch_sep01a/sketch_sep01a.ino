
/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"


// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

int counter = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(1);
  }
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 

  Serial.println("status of cap.begin() = "); Serial.println(cap.begin());

  Serial.println("on next line");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  //if (!cap.begin(0x5A)) {
    //Serial.println("MPR121 not found, check wiring?");
    // while (1);
  //}
  Serial.println("MPR121 found!");
}

void loop() {
  // put your main code here, to run repeatedly:
  // put a delay so it isn't overwhelming


}
