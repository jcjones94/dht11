bool x;
void read(){
  digitalWrite(2, HIGH);
  delay(250);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  delay(20);

  uint32_t cycles[80];

  digitalWrite(2, HIGH);
  delayMicroseconds(40);

  pinMode(2, INPUT_PULLUP);
  delayMicroseconds(10);

  for(int i = 0; i< 80; i++){
    cycles[i] = digitalRead(2);
    delayMicroseconds(10);
  }
  for(int i = 0; i< 80; i++){
    Serial.print(cycles[i]);
    Serial.print(" , ");
  }
   Serial.println();
}
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
}

void loop() {
  read();
}
