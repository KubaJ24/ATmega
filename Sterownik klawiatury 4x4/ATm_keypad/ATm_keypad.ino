#include <avr/io.h>
#include <util/delay.h>

/*
Kolumny - PB0 do PB3
Wiersze - PC0 do PC3
Wiersze PULL-DOWN 1k
*/

uint8_t var = 0;

void PIN_SETUP(void);

void setup() {

  Serial.begin(9600);

  PIN_SETUP();
  PORTC |= 0b0000;
}

void loop() {
  for(uint8_t i = 0; i < 4; i++){
    PORTC = (1 << i);
    if(PINB == 1){ 
      Serial.print("PINB: ");
      Serial.print(PINB, BIN);
      Serial.print("   i: ");
      Serial.println(i); 
      delay(250); 
    }
    else if(PINB == 2){ 
      Serial.print("PINB: ");
      Serial.print(PINB);
      Serial.print("   i: ");
      Serial.println(i + 5); 
      while(PINB == 2){}
      delay(20); 
    }
    else if(PINB == 4){ 
      Serial.print("PINB: ");
      Serial.print(PINB);
      Serial.print("   i: ");
      Serial.println(i + 9); 
      while(PINB == 4){}
      delay(20); 
    }
    else if(PINB == 8){ 
      Serial.print("PINB: ");
      Serial.print(PINB);
      Serial.print("   i: ");
      Serial.println(i + 13); 
      while(PINB == 8){}
      delay(20); 
    }
  }
}

void PIN_SETUP(void){
  //COLUMNS
  DDRC = 0xFF;
  PORTC = 0x00;

  //ROWS
  DDRB = 0x00;
  PORTB = 0x00;
}