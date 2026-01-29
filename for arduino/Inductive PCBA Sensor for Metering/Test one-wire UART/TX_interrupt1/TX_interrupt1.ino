#include <SoftwareSerial.h>

#define PIN 5

SoftwareSerial uno(PIN, PIN);

int Time1;
int Time2;
int Time;

void setup() {
  Serial.begin(9600);
  uno.begin(9600);

  Serial.print("input your number (1-4) : ");

  
}

void loop() {

  pinMode(PIN, OUTPUT); //ส่ง
  digitalWrite(PIN, LOW);
  
  if (Serial.available() > 0) {
    int input1 = Serial.parseInt();
    
    if (input1 >= 1 && input1 <= 4) { /
      digitalWrite(PIN, HIGH); 
      Time1 = millis();
      delay(input1 * 60); 
      Time2 = millis();
      Time = Time2 - Time1;
      uno.println(Time); //Send the message back to board B

      digitalWrite(PIN, LOW);
    
      pinMode(PIN, INPUT_PULLUP); // Switch back to receive mode
    }
  }

  if (uno.available() > 0) {
    // delay(100); 
    String message = uno.readStringUntil('\n'); // Read message from board B
    Serial.println(message); // Show received message in the Serial Monitor
    Serial.print("input your number (1-4) : ");

  }
}

