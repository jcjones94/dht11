#ifndef DHT_H
#define DHT_H
#include "Arduino.h"


#endif

class dht{
	public:
	  dht(uint8_t pin);
	  void begin(void);
	  bool read(bool);
      //float getTemperature(void);
	  uint8_t* getData(void);
	  
	private:
	  uint8_t data[5];
	  uint8_t _pin;
	  uint32_t _lastreadtime, _maxcycles;
	  
	  void convertData(uint32_t* cycles);
	  uint32_t pulseCount(bool value);
	
	
};