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
int x = 1;  
int y = 0;     
int sw = 0;
int val = 0;       // variable to store the read value
//
int n1;
int n2;
int answered = 0;
int answer = 0;
int score = 0;
int hold = 0;

int movement_threshold = 100;

String lr = "x";
String ud = "x";
String switch_state = "x";

String lr_last = "x";
String ud_last = "x";
String switch_state_last = "x";

void setup() {
//  int n1;
//  int n2;

  pinMode(x, INPUT);      // sets the digital pin 13 as output
  pinMode(y, INPUT);        // sets the digital pin 7 as input
  pinMode(sw, INPUT);        // sets the digital pin 7 as input
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  print_new_problem();
  lcd.setCursor(0, 1);
  lcd.print("Score = " + String(score) + "      ");
  Serial.begin(9600);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  Serial.print(hold);
  Serial.print(switch_state);
  Serial.println(switch_state_last);
  lcd.setCursor(0, 1);
  check_switch();
  check_x();
  check_y();
  if (hold==0) {
    increment_answer();
    print_problem();
  }
  else if (hold==1 and switch_state=="p" and switch_state_last=="x") {
    hold=0;
    switch_state_last="p";
    print_score();
    print_new_problem();
  }
  else if (hold==1 and switch_state=="x") {
    switch_state_last = "x";
  }

}

int check_x() {
  if (analogRead(x)<512-movement_threshold) {
    lr = "r";
  }
  else if (analogRead(x)>512+movement_threshold) {
    lr = "l";
  }
  else {
    lr = "x";
  }
}

int check_y() {
  if (analogRead(y)<512-movement_threshold) {
    ud = "u";
  }
  else if (analogRead(y)>512+movement_threshold) {
    ud = "d";
  }
  else {
    ud = "x";
  }
}

int check_switch() {
  if (digitalRead(sw)==0) {
    switch_state = "p";
  }
  else if (digitalRead(sw)==1) {
    switch_state = "x";
  }
}

int increment_answer() {
  if (lr == "r" and lr_last == "x") {
    answer += 1;
  }
  if (lr == "l" and lr_last == "x") {
    answer -= 1;
  }
  if (ud == "u" and ud_last == "x") {
    answer += 1;
  }
  if (ud == "d" and ud_last == "x") {
    answer -= 1;
  }
  if (switch_state == "p" and switch_state_last == "x") {
    check_answer();
  }
  lr_last = lr;
  ud_last = ud;
  switch_state_last = switch_state;
}

int print_new_problem()
{
  randomSeed(millis()+analogRead(3));
  n1 = random(0,20);
  n2 = random(0,20);
  lcd.setCursor(0, 0);
  String thisString = String(n1)+'+'+String(n2)+"=?    ";
  lcd.print(thisString);
  lcd.setCursor(0, 1);
}

int print_problem() {
  lcd.setCursor(0, 0);
//  String the_answer = "the answer = " + String(n1);
  String the_answer = String(n1) + '+' + String(n2) + "=" + String(answer) + "    ";
  lcd.print(the_answer);
  lcd.setCursor(0, 1);
}

int check_answer() {
  lcd.setCursor(0, 1);
  if (answer == n1+n2) {
    score += 1;
    lcd.print("Hurray Elliott!!      ");
    delay(1500);
    print_score();
    print_new_problem();
  }
  else {
    lcd.print("Nope, it's "+ String(n1+n2));
    hold=1;
  }
  answer = 0;
  
}

int print_score() {
    lcd.setCursor(0, 1);
    lcd.print("Score = " + String(score) + "           ");
}
