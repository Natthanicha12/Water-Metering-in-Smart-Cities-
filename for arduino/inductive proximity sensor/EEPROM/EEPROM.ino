#include <EEPROM.h>

int sw = 3;
int A;

void setup() {
  Serial.begin(9600);
  pinMode(sw, INPUT_PULLUP);
  
  // Read value A from EEPROM
  EEPROM.get(0, A);
}

void loop() {
  if (digitalRead(sw) == 1) {
    A++;

    Serial.println(A);
    delay(1000);

    if ( A % 10 == 0){ //Save value every 10
    
    // Write value A to EEPROM
    EEPROM.put(0, A);

    //  Read value A from EEPROM
    EEPROM.get(0, A);

    
    }
  }
} 