#include "dht11.h"

dht dht(2);
uint8_t *data;
void setup() {
  Serial.begin(9600);
  
  dht.begin();
}

void loop() {
  if(dht.read(0)){
    data = dht.getData();
    Serial.print(data[0]);
    Serial.print(" ");
    Serial.println(data[2]);
  }
}
