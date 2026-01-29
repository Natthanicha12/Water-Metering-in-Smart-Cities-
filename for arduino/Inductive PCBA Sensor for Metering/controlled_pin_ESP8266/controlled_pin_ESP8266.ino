#include <SoftwareSerial.h>

#define PIN D8
#define dataLength 5

SoftwareSerial uno(PIN, PIN); // Use one wire for both data input and output
bool check = true;
unsigned long lastSendTime = 0; // Save the last transmit time

unsigned long Time1;
unsigned long Time2;
unsigned long Time;

unsigned long count1;
unsigned long count2;
unsigned long count;


byte receivedData[dataLength]; // Receive buffer
int index1 = 0; //Received data index

unsigned long previousMillis = 0; // Store last message TX time
const long interval = 10000; //The delay duration (10,000 milliseconds = 10 seconds)

void setup() {
  Serial.begin(9600);
  uno.begin(2400);

  pinMode(PIN, OUTPUT); 
  digitalWrite(PIN, LOW);
}

void loop() {

   unsigned long currentMillis = millis(); //Store current millis

  if (currentMillis - previousMillis >= interval) {
    // If time exceeds 10 seconds.
    previousMillis = currentMillis; // Update last TX time

 
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


  // Receive data from the sensor and display it on the Serial Monitor
  if (uno.available() > 0 ) {
    Serial.println("Received Data: ");

    while (uno.available() > 0 ) {
      receivedData[index1] = uno.read();
      index1++;
    }

    // Show the received data
    for (int i = 0; i < index1; i++) {
      Serial.print(receivedData[i],HEX);
      Serial.print("(");
      Serial.print(receivedData[i]);
      Serial.print(")");
      Serial.print(" ");      
    }

    Serial.println("===========================================");
    //Reset receive index
    index1 = 0;

    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, LOW);
  }
}
