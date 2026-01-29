#include <SoftwareSerial.h>

#define PIN 5

SoftwareSerial uno(PIN, PIN);

unsigned long receivedTime; 

void setup() {
  Serial.begin(9600);
  uno.begin(9600);
  pinMode(PIN, INPUT_PULLUP); 
}

void loop() {
  if (uno.available() > 0) {
    receivedTime = uno.parseInt(); // Get data from Uno1 and store in receivedTime

    pinMode(PIN, OUTPUT); // Switch to transmit mode
    delay(10);

    if(receivedTime >= 58 && receivedTime <= 62){
      uno.print("Received Time Q1 :");
      uno.println(receivedTime);
    } else if (receivedTime >= 118 && receivedTime <= 122){
      uno.print("Received Time Q2 :");
      uno.println(receivedTime);
    } else if (receivedTime >= 178 && receivedTime <= 182){
      uno.print("Received Time Q3 :");
      uno.println(receivedTime);
    } else if (receivedTime >= 238 && receivedTime <= 242){
      uno.print("Received Time Q4 :");
      uno.println(receivedTime);
    } else if (receivedTime == 0){
      uno.print("Time_Zero: ");
      uno.println(receivedTime);
    } else {
      uno.println("error");
    }

    digitalWrite(PIN, LOW); // Set LOW again after timeout

    
    pinMode(PIN, INPUT_PULLUP); // Switch back to receive mode
  }
}
