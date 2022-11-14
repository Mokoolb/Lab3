/* Voltmeter with LCD
 The goal of this code is to read the values returned from the potientiometer
 and convert them from bit value to voltage, to then display on the LCD
*/
#include <LiquidCrystal.h>//to make writing code easier, we include a built in library for LCD
LiquidCrystal Lcd(12, 11, 5, 4, 3, 2);// Using code commands from the library, this sets the pins of the LCD
float analogPin = A0;   // potentiometer connected to PWM pin 9

void setup() {//the code in these brackets happens once
  Lcd.begin(16,2);//set's the sice of the screen using the libraries commands
  pinMode(9, OUTPUT);//set's the PWM pin 9 as OUTPUT for the potentiometer
  analogWrite(9, 255); // analogRead values go from 0 to 1023, analogWrite values from 0 to 255, so it sends max voltage
  
}
float voltage = 0;//creates the variable for volatge as a float
void loop() {//the code in these brackets happens repeatidly
  
  lcd.setCursor(0,0);//sets the LCD cursor to the top left corner
  voltage = analogRead(analogPin)/204.6;// takes the value read from pin AO and divides it by 204.6 to recieve a voltage value then stores it in a variable
  Lcd.print("Voltage:   " );//prints text on the LCD screen to help indicate what the next number is
  Lcd.setCursor(0,1);//sets the LCD cursor to the bottom left corner
  Lcd.print(voltage);//prints the voltage value from the variable onto the LCD
  Lcd.print("V ");//prints text on the LCD screen to help indicate what the previous value is


}
 
 
