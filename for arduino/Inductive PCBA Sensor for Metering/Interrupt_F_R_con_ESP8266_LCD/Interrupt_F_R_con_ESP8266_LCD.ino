#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int inputPin = 14; // Define the input pin for pulse counting        //D5_F
const int inputPin1 = 12; //D6_R

volatile unsigned long pulseCount = 0; // Initialize pulse count variable
unsigned long Time_1;
unsigned long Time_2;
unsigned long Time_3;
unsigned long Time_total;
unsigned long Time_positive;
unsigned long Time_zero;
unsigned long R;
float frequency;
double Duty;

double water_use_total = 0.0;
int x = 0;
int y = 0;
double water_use_counter = 0.0;

int count_zero;
int count_postive;;

int count_F = 0;
int count_R = 0;
unsigned long pulse = 0;

//================================

#include <SoftwareSerial.h>

#define PIN D8
#define dataLength 5

SoftwareSerial uno(PIN, PIN);
bool check = true;2
unsigned long lastSendTime = 0;

unsigned long Time1;
unsigned long Time2;
unsigned long Time;

unsigned long count1;
unsigned long count2;
unsigned long count;

byte receivedData[dataLength]; 
int index1 = 0; 

unsigned long previousMillis = 0;
const long interval = 10000; // 10 seconds
unsigned long unoo = 0;

void setup() {
  
  pinMode(inputPin, INPUT_PULLUP);
  pinMode(inputPin1, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(inputPin), pulseCounting, CHANGE); // Attach interrupt to the input pin
  attachInterrupt(digitalPinToInterrupt(inputPin1), pulseCounting1, CHANGE);

  Serial.begin(115200); // Initialize serial communication
  uno.begin(2400);

  pinMode(13 , OUTPUT);

  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);

  lcd.init(); 
  lcd.backlight();  
  lcd.home(); 

  Serial.println("------------Start program-------------");
}

void loop() {
  unsigned long currentMillis = millis();

  if (x == 1 && y == 1) {
   // Serial.println("-");
    if( Time_2  > Time_1){

      Time_zero  = Time_2  - Time_1;

      Serial.print("Time_count_1 : ");
      Serial.print(Time_zero);
      Serial.println(" ms ");

      count_zero = 1;

      x = 0;
      
      
    } else if (Time_1  > Time_2 ) {
      Time_positive = Time_1 - Time_2;

      Serial.print("Time_count_2 : ");
      Serial.print(Time_positive);
      Serial.println(" ms ");


      count_postive = 1;

      y = 0;

    } 
    
    if ((count_postive == 1 && count_zero == 1) && ((Time_positive >= 60 && Time_positive <=66) || (Time_zero >= 60 && Time_zero <=66))) {

     if (digitalRead(inputPin) == 1  &&  digitalRead(inputPin1) == 0) {
        lcd.setCursor(0,1);
        lcd.print("Forward pulse");

        Serial.println("-----------------------");
        Serial.println("Forward ");
        Serial.println("-----------------------");
        water_use_counter++;

        count_F++;
        if (count_F == 1) {
          Time1 = millis();
          digitalWrite(PIN, HIGH);
          delay(500);
          Time2 = millis();
          digitalWrite(PIN, LOW);
          Time = Time2 - Time1;
          Serial.print("Sent to sensor(F): ");
          Serial.println(Time); 

          uno.write(Time);
          uno.flush(); 

          pinMode(PIN, INPUT_PULLUP);
          delay(100);

          count_F = 0;
        }
      } else if (digitalRead(inputPin) == 0  &&  digitalRead(inputPin1) == 1) {
        water_use_counter--;
        R++;
        lcd.setCursor(0,1);
        lcd.print("Reverse:");
        lcd.setCursor(8,1); 
        lcd.print(R);
        lcd.setCursor(13,1); 
        lcd.print("L");

        Serial.println("-----------------------");
        Serial.print("Reverse : ");
        Serial.print(R);
        Serial.println("L");
        Serial.println("-----------------------");

        count_R++;
        if (count_R == 1) { 
          Time1 = millis();
          digitalWrite(PIN, HIGH);
          delay(500);
          Time2 = millis();
          digitalWrite(PIN, LOW);
          Time = Time2 - Time1;
          Serial.print("Sent to sensor(R): ");
          Serial.println(Time);

          uno.write(Time);
          uno.flush(); 

          pinMode(PIN, INPUT_PULLUP);
          delay(100);
          count_R = 0;
        } 
      
      } 
      
      Serial.print("water use counter : ");
      Serial.print(water_use_counter);
      Serial.println(" L ");

      lcd.setCursor(0,0);
      lcd.print("count:");
      lcd.setCursor(6,0); 
      lcd.print(water_use_counter);
      lcd.setCursor(13,0);
      lcd.print("L");

      if(fmod(water_use_counter, 100.0) == 0.0){
      beep();
      }

      //Serial.println("-");

      count_zero = 0;
      count_postive = 0;

      Time_zero = 0;
      Time_positive = 0;


      
      // Time_2 = 0 ;
      // Time_3 = 0 ;
    }

    previousMillis = millis(); // Reset the timer after if block execution

 } 
  else if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis; // Reset the timer

    Time1 = millis();
    digitalWrite(PIN, HIGH);
    delay(500);
    Time2 = millis();
    digitalWrite(PIN, LOW);
    Time = Time2 - Time1;
    Serial.print("Sent to sensor: ");
    Serial.println(Time);

    uno.write(Time);
    uno.flush(); 


    pinMode(PIN, INPUT_PULLUP);
    delay(1000);

  }

  if (uno.available() > 0) {
    Serial.println("Received Data: ");

    while (uno.available() > 0) {
      receivedData[index1] = uno.read();
      index1++;
    }

    // แสดงข้อมูลที่รับ
    for (int i = 0; i < index1; i++) {
      // Serial.print(receivedData[i],HEX);
      // Serial.print("(");
      // Serial.print(receivedData[i]);
      // Serial.print(")");
      // Serial.print(" ");

      switch(i){
          case 0 :  
              switch(receivedData[i]){
              case 250 :  Serial.println("command 2 : 250ms"); break; // T = 250 
              case 119 :  Serial.println("command 3 : 375ms"); break; // T = 375
              case 244 :  Serial.println("command 4 : 500ms"); break; // T = 500
              } 
          break;

          case 6 :  
              //lowByte(x) , highByte(x)
              Serial.print("6) Signal intensity(Low) : "); Serial.print(lowByte(receivedData[i]) , HEX);  Serial.print("("); Serial.print(receivedData[i]);  Serial.println(")"); break; // T4 ...................................
              Serial.print("6) Signal intensity(HIGH) : "); Serial.print(highByte(receivedData[i]) , HEX);  Serial.print("("); Serial.print(receivedData[i]);  Serial.println(")"); break; // T4 ...................................
          break;

          case 7 :  
              Serial.print("7) Signal indication(Low) : "); Serial.print(lowByte(receivedData[i]) , HEX);  Serial.print("("); Serial.print(receivedData[i]);  Serial.println(")"); break; // T4........................................
              Serial.print("7) Signal indication(High) : "); Serial.print(highByte(receivedData[i]) , HEX);  Serial.print("("); Serial.print(receivedData[i]);  Serial.println(")"); break; // T4........................................
          break;
          break;
        }

    }

    index1 = 0;

    Serial.println(" ");
    Serial.println("======================");

    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, LOW);
  }
}

ICACHE_RAM_ATTR void pulseCounting() {
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

ICACHE_RAM_ATTR void pulseCounting1() {
  if (digitalRead(inputPin1) == 0) {
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
 tone(13, 1000, 1000); 
}
