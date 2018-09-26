#include <Arduino.h>
#include <LiquidCrystal.h> 

extern HardwareSerial Serial;

#define TRIGGER_PIN   26 // Arduino pin tied to trigger pin on ping sensor.
#define ECHO_PIN      27 // Arduino pin tied to echo pin on ping sensor.
#define MAX_DISTANCE 400 // Maximum distance (in cm) to ping.

// select the pins used on the LCD panel 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 
unsigned long pingTime;
unsigned long lastPing=0;
unsigned long maxPingTime = MAX_DISTANCE * 58;
    

void setup() {
    Serial.begin(115200);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    
    lcd.begin(16, 2);              // start the library 
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Booting up...."); // print a simple message 
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Dist: ");
}

void loop() {
    while (digitalRead(ECHO_PIN))
    {
//        Serial.println("***OOPS*** ECHO_PIN is HIGH");
//        digitalWrite(TRIGGER_PIN, HIGH);
//        delayMicroseconds(10);
//        digitalWrite(TRIGGER_PIN, LOW);
        delayMicroseconds(50);
    }
    //delay(100);
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(4);             // Wait for pin to go low.
    digitalWrite(TRIGGER_PIN, HIGH);  // Set trigger pin high, this tells the sensor to send out a ping.
    delayMicroseconds(10);            // Wait long enough for the sensor to realize the trigger pin is high. Sensor specs say to wait 10uS.
    digitalWrite(TRIGGER_PIN, LOW);
//    if (digitalRead(ECHO_PIN))
//    {
//        Serial.println("***OOPS*** ECHO_PIN is HIGH after trigger");
////        digitalWrite(TRIGGER_PIN, HIGH);
////        delayMicroseconds(10);
////        digitalWrite(TRIGGER_PIN, LOW);
//        //delay(50);
//    }
    pingTime = pulseIn(ECHO_PIN, HIGH, maxPingTime);
    
    if (pingTime != lastPing)
    {
        lcd.setCursor(6,0);   
        lcd.print("   ");
        lcd.setCursor(6,0); 
        lcd.print(pingTime/148);      // display seconds elapsed since power-up
        lastPing = pingTime;
    }
   
    
    
    
//    Serial.print("Dist: ");
//    Serial.println(pingTime/148);
//    if (pingTime == 0)
//    {
//        lcd.setCursor(0,1); 
//        lcd.print("Waiting...");
//        delay(189);
//        lcd.setCursor(0,1); 
//        lcd.print("          ");
//     }else delay(50);
 }

//boolean ping_trigger() {
//    digitalWrite(TRIGGER_PIN, LOW);   // Set the trigger pin low, should already be low, but this will make sure it is.
//    delayMicroseconds(4);             // Wait for pin to go low.
//    digitalWrite(TRIGGER_PIN, HIGH);  // Set trigger pin high, this tells the sensor to send out a ping.
//    delayMicroseconds(10);            // Wait long enough for the sensor to realize the trigger pin is high. Sensor specs say to wait 10uS.
//    digitalWrite(TRIGGER_PIN, LOW);   // Set trigger pin back to low.
//
//    if (digitalRead(ECHO_PIN)) return false;                // Previous ping hasn't finished, abort.
//    _max_time = micros() + _maxEchoTime + MAX_SENSOR_DELAY; // Maximum time we'll wait for ping to start (most sensors are <450uS, the SRF06 can take up to 34,300uS!)
//    while (!digitalRead(ECHO_PIN))                          // Wait for ping to start.
//        if (micros() > _max_time) return false;             // Took too long to start, abort.
//}
