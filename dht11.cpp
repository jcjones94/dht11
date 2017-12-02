#include "dht11.h"

dht::dht(uint8_t pin = 2){
	_pin = pin;
	_maxcycles = 2000;
}

void dht::begin(void){
	pinMode(_pin, INPUT_PULLUP);
	_lastreadtime = 0;
}

bool dht::read(bool force){
	uint32_t currenttime = millis();
    if (!force && ((currenttime - _lastreadtime) < 2000) || millis() < 1000) {
      return 0; // return last correct measurement
    }
    _lastreadtime = currenttime;
	
	data[0] = data[1] = data[2] = data[3] = data[4] = 0;
	
	digitalWrite(_pin, HIGH);
    delay(250);

    // First set data line low for 20 milliseconds.
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(20);
	uint32_t cycles[80];
	
	digitalWrite(_pin, HIGH);
	delayMicroseconds(40);
	
	pinMode(_pin, INPUT_PULLUP);
    delayMicroseconds(10);
	
    pulseCount(LOW);
      
    pulseCount(HIGH);
	
	for (int i=0; i<80; i+=2) {
      cycles[i]   = pulseCount(LOW);
      cycles[i+1] = pulseCount(HIGH);
    }
	convertData(cycles);
	//Serial.println();
	return 1;
}
uint8_t* dht::getData(void){
	
	return data;
}
void dht::convertData(uint32_t* cycles){
	uint32_t lowcount = cycles[0];
    for(int i = 1; i < 80;i += 2){
		if(cycles[i] > lowcount){
			data[i/16] = data[i/16] + (1<<((16 - i%16)/2));
		}
		//Serial.print(data[(int)i/16]);
		//Serial.print(" , ");
    }
	
}
uint32_t dht::pulseCount(bool value){
	uint32_t count = 0;
	while(digitalRead(_pin) == value){
		if(count++ >= _maxcycles){
			return 0;
		}
	}
	return count;
}