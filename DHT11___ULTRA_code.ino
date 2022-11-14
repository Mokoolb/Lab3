/* Ultrasonic and DHT with LCD
   The goal of this program is receive humidity values, temperature values
   and ultrasonic values and display them on an 16 by 2 LCD
 */
//arduino STUFF
unsigned long myTime;//This variable time is for using millis() (time since the robot started)
int times = 0;//for the amount of times it the program has looped
float second; this variable is used to calculate the 500 ms intervals
int mode = 0;// this is used to change screens between the ultrasonic values and the DH11 values
//LCD
#include <LiquidCrystal.h>//includes the built in LCD library
LiquidCrystal Lcd(12, 11, 5, 4, 3, 2);//sets up the pins for the LCD
// Include DHT Libraries from Adafruit
// Dependant upon Adafruit_Sensors Library
#include "DHT.h";
#define DHTPIN 7       // DHT-22 Output Pin connection
#define DHTTYPE DHT11   // DHT Type is DHT 11 
DHT dht(DHTPIN, DHTTYPE);// Setup DHT sensor for normal 16mhz Arduino
float hum;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius
//ULTRASONIC
#define trigPin 10//defines the output ultrasonic value pin
#define echoPin 13//defines the input ultrasonic value pin 
float duration, distance;//setting up variables for the duration before the wave is received and calculates the distance
void setup()//this code runs once
{   
  dht.begin();// Initialize DHT-11
    Lcd.begin(16,2);//initializes the LCD's size
  pinMode(6,INPUT_PULLUP);//setting the pin for the button
  Lcd.setCursor(0,0);//set's cursor of LCD on the top right corner 
  pinMode(trigPin, OUTPUT);// setting pin 10 as an output
  pinMode(echoPin, INPUT);//setting pin 13 as an input
}
void loop()//this code runs repeatidly 
{
    myTime = millis();//setting the variable myTime to the function millis()
  //BUTTON
   if(digitalRead(6) == LOW){if the button on pin 6 is pressed
    mode += 1;//adds 1 to the variable mode
    if(mode == 2){//if the mode goes to 2 or passed 1 it resets the count(only 2 mode, 0 and 1)
    mode = 0;//resets variable
    }
    delay(250);//delays program for a quarter of a second
  }
  //TEMPERAATURE/HUMIDITY
  if(mode == 1){//if out of the two modes(0,1) it is mode 1 it will do this code
  hum = dht.readHumidity();  // Get Humidity value
  temp= dht.readTemperature();  // Get Temperature value
  Lcd.setCursor(0,0);//sets cursor of LCD on the top right corner 
  Lcd.print("Temp:  ");//prints text on the LCD screen to help indicate what the next number is
  Lcd.print(temp);//prints the temperature value onto the LCD
  Lcd.print(" C");//prints text on the LCD screen to help indicate what the previous value is
  Lcd.setCursor(0,1);//sets cursor of LCD on the bottom right corner
  Lcd.print("Humid: ");//prints text on the LCD screen to help indicate what the next number is
  Lcd.print(hum);//prints the temperature value onto the LCD
  Lcd.print(" %");//prints text on the LCD screen to help indicate what the previous value is
  }
  //ULTRASONIC
  else if(mode == 0){//if out of the two modes(0,1) it is mode 0 it will do this code
  if(second < 500){// if the veriable second is less then 500 it will do nothing    
  }
  else{//if second is 500 then it will do the ultrasonic reading code
    times += 1;// will add 1 to times variable(which idicates how many times 500 has elapsed
  Lcd.setCursor(0,0);//sets cursor of LCD on the top right corner 
  // Write a pulse to the HC-SR04 Trigger Pin 
  digitalWrite(trigPin, LOW);//sets pin 10 off
  delayMicroseconds(2);//delays for 2 microseconds
  digitalWrite(trigPin, HIGH);;//sets pin 10 on
  delayMicroseconds(10);//delays for 10 microseconds
  digitalWrite(trigPin, LOW);;//sets pin 10 off
  duration = pulseIn(echoPin, HIGH);;//reads the value returned from pin 13 and stores it in duration(of wave)
  distance = (duration / 2) * 0.0343;//converts duration into distance in metric centimeters 
  Lcd.print("Distance =           ");//prints text to the LCD at the position of cursor
  Lcd.setCursor(0,1);//sets cursor of LCD on the bottom right corner
  if (distance >= 400 || distance <= 2) {//all checks if distance is less then 2 or greater then 400 which would be out of range
     Lcd.print("Out of range   ");//prints text to the LCD at the position of cursor
  }
  else {
    Lcd.print(distance);//prints text to the LCD at the position of cursor
    Lcd.print(" cm         ");//the mesurement of the previous value is printed onto the LCD
  }
  }
  }
  second = myTime - times*500;//a value between 0 and 500 would be added to second
}
