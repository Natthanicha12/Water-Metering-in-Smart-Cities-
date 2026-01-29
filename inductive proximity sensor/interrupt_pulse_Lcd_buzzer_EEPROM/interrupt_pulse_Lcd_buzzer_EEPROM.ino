#include <EEPROM.h>

#include <LiquidCrystal_I2C.h>
#include <Wire.h> //สื่อสารไลบราลี
LiquidCrystal_I2C Icd(0x27, 16, 2); 


const int inputPin = 2; // Define the input pin for pulse counting

unsigned long Time_1  ;
unsigned long Time_2 ;
unsigned long Time_3 ;
unsigned long Time_total ;
unsigned long Time_positive ;
unsigned long Time_zero  ;
double A , B , C;
float frequency;
double Duty;
double water_use_total = 0.0;
int x = 0;
int y = 0;
int water_use_counter = 0;
int count_zero;
int count_postive;

void setup() {
  pinMode(inputPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(inputPin), pulseCounting, CHANGE); // Attach interrupt to the input pin
  Serial.begin(9600);
  Serial.println(" hello ");

  pinMode(11, OUTPUT); 

  Icd.init(); 
  Icd.backlight(); 
  Icd.home(); 

  EEPROM.get(0, water_use_counter);
  EEPROM.get(sizeof(water_use_counter), water_use_total);
}

void loop() {

    if(x==1 && y==1 ){

    if( Time_2 > Time_1){
      Time_zero = Time_2 - Time_1;
      Serial.print("Time_zero : ");
      Serial.print(Time_zero);
      Serial.println(" ms ");

      count_zero = 1;

      x = 0;
    } else if (Time_1 > Time_2) {
      Time_positive = Time_1 - Time_2;
      Serial.print("Time_positive : ");
      Serial.print(Time_positive);
      Serial.println(" ms ");

      count_postive = 1;

      y = 0;
    }

    if(count_postive ==1 && count_zero ==1){

    Time_total = Time_positive + Time_zero;
    Serial.print("Time_total : ");
    Serial.print(Time_total);
    Serial.println(" ms ");

    A = Time_positive * 1000;
    B = Time_total * 1000;
    C = Time_zero * 1000;
    Duty = ( A / B ) * 100; 
    Serial.print("Duty : ");
    Serial.print(Duty); 
    Serial.println(" % ");

    water_use_counter++;
    Serial.print("water use counter (Low) : ");
    Serial.print((water_use_counter) * (C / B));
    Serial.println(" L ");
    Serial.print("water use counter (High) : ");
    Serial.print((water_use_counter) * (A / B));
    Serial.println(" L ");
    Serial.print("water use counter (total): ");
    Serial.print(water_use_counter);
    Serial.println(" L ");

    Icd.setCursor(0,0); 
    Icd.print("count:");
    Icd.setCursor(6,0); 
    Icd.print(water_use_counter);
    Icd.setCursor(13,0);
    Icd.print("L");

    water_use_total = water_use_counter / 1000.000;
    Serial.print("water use total : ");
    Serial.print(water_use_total, 3);
    Serial.println(" m^3 ");

    Icd.setCursor(0,1); 
    Icd.print("total:");
    Icd.setCursor(6,1); 
    Icd.print(water_use_total, 3); 
    Icd.setCursor(13,1);
    Icd.print("m^3");



    Serial.println("======================");
    count_zero = 0;
    count_postive = 0;

    if(water_use_counter % 10 == 0){
      beep();
    }

  }

 }
}



void pulseCounting() {
  if (digitalRead(inputPin) == 0) {
      x = 1;
      
      Time_1 = millis();
      //Serial.print("Time1 = ");
      //Serial.println(Time_1);
    }
  
    else {
    y = 1;
    Time_2 = millis();
  }
}

void beep() {
 tone(11, 1000, 1000); 

  EEPROM.put(0, water_use_counter);
  EEPROM.get(0, water_use_counter);

  EEPROM.put(sizeof(water_use_counter), water_use_total);
  EEPROM.get(sizeof(water_use_counter), water_use_total);
}