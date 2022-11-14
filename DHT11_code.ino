/* DHT 11 with LCD
   The goal of this program is receive humidity values, temperature values
   and display them on an 16 by 2 LCD
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
void setup()//this code runs once
{   
  dht.begin();// Initialize DHT-11
    Lcd.begin(16,2);//initializes the LCD's size
  Lcd.setCursor(0,0);//set's cursor of LCD on the top right corner 
}
void loop()//this code runs repeatidly 
{
  //TEMPERAATURE/HUMIDITy
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
