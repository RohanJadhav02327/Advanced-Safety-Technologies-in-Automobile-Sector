#include <LiquidCrystal.h>
const int rs = 13, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define Sober 200   // Define max value that we consider sober
#define Drunk 400   // Define min value that we consider drunk
#define MQ3 0
float sensorValue;  //variable to store sensor value

//ultrasonic sensor var
const int trigPin = 7;
const int echoPin = 6;
long duration;
int distance;

//IR sensor var
#define IR A1

//GPS var
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial gpsSerial(8,9);
TinyGPSPlus gps;
float lattitude,longitude;


void setup() {
 gpsSerial.begin(9600);
 Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Advanced Safety Tech");
  lcd.setCursor(0,1);
  lcd.print(" in Automobile");
  pinMode(IR, INPUT);
  pinMode(10, OUTPUT);
  delay(20000); // allow the MQ3 to warm up 20000
  lcd.clear();
}

void loop() {

while (gpsSerial.available())
  {
    int data = gpsSerial.read();
    if (gps.encode(data))
    {
      lattitude = (gps.location.lat());
      longitude = (gps.location.lng());
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("LA-");
      lcd.setCursor(3,0);
      lcd.print(lattitude);
      lcd.setCursor(0,1);
      lcd.print("LO-");
      lcd.setCursor(3,1);
      lcd.print(longitude);
      delay(1500);
      lcd.clear();
    }
  }
  
// MQ3 Sensor data reading
  sensorValue = analogRead(MQ3); // read analog input pin 0
  // Determine the status
  if (sensorValue < Sober) {
     lcd.setCursor(0,0);
     lcd.print("Status: Sober");

  } else if (sensorValue >= Sober && sensorValue < Drunk) {
     lcd.setCursor(0,0);
     lcd.print("Status:L_Drink");
     for(int i=0; i=2;i++){
      digitalWrite(10,HIGH);  // 3beep if drunk in limit
      delay(200);
      digitalWrite(10,LOW);
      delay(200);
      digitalWrite(10,HIGH);  
      delay(200);
      digitalWrite(10,LOW);
      delay(200);
      digitalWrite(10,HIGH);  
      delay(200);
      digitalWrite(10,LOW);
      delay(200);
    }

  } else {

    Serial.println("Status: DRUNK");
    lcd.setCursor(0,0);
    lcd.print("Status: DRUNK");
     Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
     delay(1000);  // Delay of 1 second
     Serial.println("AT+CMGS=\"+918855903684\"\r"); // Replace x with mobile number
     delay(1000);
     Serial.println("DRUNK");// The SMS text you want to send
     Serial.println(lattitude);
     Serial.println(longitude);
     delay(100);
     Serial.println((char)26);// ASCII code of CTRL+Z for saying the end of sms to  the module 
     
      digitalWrite(10,HIGH); // 5 Beep if person has drunk 
      delay(200);
      digitalWrite(10,LOW);
      delay(200);
      digitalWrite(10,HIGH);  
      delay(200);
      digitalWrite(10,LOW);
      delay(200);
      digitalWrite(10,HIGH); 
      delay(200);
      digitalWrite(10,LOW);
      delay(200);
      digitalWrite(10,HIGH);
      delay(200);
      digitalWrite(10,LOW);
      delay(200);
      digitalWrite(10,HIGH); 
      delay(200);
      digitalWrite(10,LOW);
      delay(200);
  }
  
 // Ultrsonic sensor data reading 
 // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on the HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration*0.0343/2;
  lcd.setCursor(0,1);
  lcd.print("D-");
  lcd.setCursor(2,1);
  lcd.print(distance);

  // IR Sensor Reading
  int slp = digitalRead(IR);
  if(slp== LOW){
  lcd.setCursor(8,1);
  lcd.print("Sleeping");
  digitalWrite(10,HIGH); // 2 Beep if person is sleeping 
  delay(200);
  digitalWrite(10,LOW);
  delay(200);
  digitalWrite(10,HIGH); // 2 Beep if person is sleeping 
  delay(200);
  digitalWrite(10,LOW);
  delay(200);
  }
  
  else{
  lcd.setCursor(8,1);
  lcd.print("Awake");
  }
  delay(1500);
   
}
