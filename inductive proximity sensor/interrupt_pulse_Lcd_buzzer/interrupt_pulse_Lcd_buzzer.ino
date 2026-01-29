#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
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
double water_use_total = 20.7500;
int x = 0;
int y = 0;
int z = 0;
double water_use_counter = 20750.0;
int count_zero;
int count_postive;

unsigned long excludeStart = 0;
unsigned long excludeEnd = 0;
unsigned long excludeDuration = 0;
unsigned long previousMillis = 0;
const long interval = 5000; // 5 seconds

void setup() {
  pinMode(inputPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(inputPin), pulseCounting, CHANGE); // Attach interrupt to the input pin
  Serial.begin(115200); // Initialize serial communication
  Serial.println("------------Start program-------------");

  pinMode(11, OUTPUT); // pin buzzer

  Icd.init(); // use init() or begin(ROW , column )
  Icd.backlight(); 
  Icd.home(); //  ICD default
}

void loop() {

    unsigned long currentMillis = millis();

    if(x==1 && y==1 ){

    if( Time_2  > Time_1){

      Time_zero  = Time_2 - Time_1;

      if(z != 1){
      Serial.print("Time_count_1 : ");
      Serial.print(Time_zero);
      Serial.println(" ms ");
      }

      count_zero = 1;

      x = 0;
      
      
    } else if (Time_1  > Time_2 ) {
      Time_positive = Time_1  - Time_2;

      if( z != 1){
      Serial.print("Time_count_2 : ");
      Serial.print(Time_positive);
      Serial.println(" ms ");
      }


      count_postive = 1;

      y = 0;    
      } 

    if(count_postive ==1 && count_zero ==1){

    if((z != 1)){
    Time_total = Time_positive + Time_zero;
    Serial.print("Time_total : ");
    Serial.print(Time_total);
    Serial.println(" ms ");

    if(Time_total > 0 && Time_total <= 1500){
      Serial.println("Speed level 1");
      Icd.setCursor(0,0);
      Icd.print("Speed level 1");
    }else if(Time_total > 1500 && Time_total <= 2500){
      Serial.println("Speed level 2");
      Icd.setCursor(0,0);
      Icd.print("Speed level 2");
    }else{
      Serial.println("Speed level 3");
      Icd.setCursor(0,0);
      Icd.print("Speed level 3");
    }

    A = Time_positive * 1000;
    B = Time_total * 1000;
    C = Time_zero * 1000;
    Duty = ( A / B ) * 100; 
    Serial.print("Duty : ");
    Serial.print(Duty); 
    Serial.println(" % ");

    water_use_counter++;
    Serial.print("water use counter (Low) : ");
    Serial.print((water_use_counter-1) + (C / B));
    Serial.println(" L ");
    // Serial.print("water use counter (High) : ");
    // Serial.print((water_use_counter-1) + (A / B));
    // Serial.println(" L ");
    } 

    Serial.print("water use counter (total): ");
    Serial.print(water_use_counter);
    Serial.println(" L ");

    // Icd.setCursor(0,0); 
    // Icd.print("count:");
    // Icd.setCursor(6,0); 
    // Icd.print(water_use_counter);
    // Icd.setCursor(13,0);
    // Icd.print("L");

    water_use_total = water_use_counter / 1000.000;
    Serial.print("water use total : ");
    Serial.print(water_use_total, 4); // 4 decimal places
    Serial.println(" m^3 ");

    Icd.setCursor(0,1); 
    Icd.print("total:");
    Icd.setCursor(6,1); 
    Icd.print(water_use_total, 4); // 4 decimal places
    Icd.setCursor(13,1);
    Icd.print("m^3");



    Serial.println("======================");
    count_zero = 0;
    count_postive = 0;
    z=0;

    Time_zero = 0;
    Time_positive = 0;

    if(fmod(water_use_counter, 2000.0) == 0.0){
      beep();
    }
  }
  
  
  previousMillis = millis();

 }else if (currentMillis - previousMillis >= interval) {


      // Serial.print("Time : ");
      // Serial.print((currentMillis - previousMillis) / 1000 );
      // Serial.println(" s");

      previousMillis = currentMillis; // Reset the timer
      Serial.println("Water is not running");

      if((x == 1 || y == 1) && z == 1) {
      water_use_counter += 0.5 ;

      x= 2;
      y= 2;
      }
      

    z = 1;
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
 tone(11, 1000, 2000); // tone(pin , frequency , delay)
}