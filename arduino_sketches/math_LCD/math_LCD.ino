/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int counter = 0; 
int reset_time = 0;
String timer = "   ";
String str = "Elliott";
//
int n1;
int n2;
int answered = 0;

void setup() {
//  int n1;
//  int n2;
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  print_new_problem();
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  counter = millis() / 1000 - reset_time;
  timer = String(10-counter)+"    ";
  if (answered==0){
    lcd.print(timer);
  }
  
  if (counter>=10) {
    reset_time = millis() / 1000;
      print_answer();
  }
}

int print_new_problem()
{
  randomSeed(analogRead(0));
  n1 = random(0,20);
  n2 = random(0,20);
  lcd.setCursor(0, 0);
  String thisString = String(n1)+'+'+String(n2)+"=?    ";
  lcd.print(thisString);
  lcd.setCursor(0, 1);

}

int print_answer() {
  lcd.setCursor(0, 0);
  int answer = n1+n2;
//  String the_answer = "the answer = " + String(n1);
  String the_answer = String(n1) + '+' + String(n2) + "=" + String(answer) + "    ";
  lcd.print(the_answer);
  lcd.setCursor(0, 1);
  lcd.print("Press reset");
  answered = 1;
}
