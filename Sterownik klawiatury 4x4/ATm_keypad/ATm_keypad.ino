#include <avr/io.h>
#include <util/delay.h>

/*
Kolumny - PB0 do PB3
Wiersze - PC0 do PC3
Wiersze PULL-DOWN 1k
*/

int a = 0;

void PIN_SETUP(void);
void UART_SETUP(void);
void GET_KEY(void);
void DISPLAY_KEY(uint8_t num);

void setup() {

  PIN_SETUP();
  UART_SETUP();

}

void loop() {
  GET_KEY();
}

void PIN_SETUP(void){
  //COLUMNS
  DDRC = 0xFF;
  PORTC = 0x00;

  //ROWS
  DDRB = 0x00;
  PORTB = 0x00;
}

void UART_SETUP(void){
  //UART SET, 8-BIT WORD LENGTH, 1-BIT STOP
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
  //BAUD RATE 9600
  UBRR0L = 103;
  //TRANSMITTER ENABLE
  UCSR0B = (1 << TXEN0);
}

void GET_KEY(void){
  for(uint8_t i = 0; i < 4; i++){
    PORTC = (1 << i);
    if(PINB == 1){ 
      DISPLAY_KEY(i);
      delay(250); 
    }
    else if(PINB == 2){ 
      DISPLAY_KEY(i + 5);
      while(PINB == 2){}
      delay(20); 
    }
    else if(PINB == 4){ 
      DISPLAY_KEY(i + 9);
      while(PINB == 4){}
      delay(20); 
    }
    else if(PINB == 8){ 
      DISPLAY_KEY(i + 13);
      while(PINB == 8){}
      delay(20); 
    }
  } 
}

void DISPLAY_KEY(uint8_t num){
  UDR0 = num;
  while((UCSR0A & (1 << UDRE0)) == 0){ /* WAIT */ }
}