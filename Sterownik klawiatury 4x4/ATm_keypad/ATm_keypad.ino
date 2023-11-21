#include <avr/io.h>
#include <util/delay.h>

/*
Kolumny - PB0 do PB3
Wiersze - PC0 do PC3
*/

uint8_t var = 0;

void PIN_SETUP(void);

void setup() {

  Serial.begin(9600);

  PIN_SETUP();
  PORTB |= 0b1000;
}

void loop() {
  var = PINC;
  Serial.println(var, BIN);

  delay(100);

}

void PIN_SETUP(void){
  //COLUMNS
  DDRB = 0xFF;
  PORTB = 0;

  //ROWS
  DDRC = 0x00;
  PORTC = 0xFF;
}