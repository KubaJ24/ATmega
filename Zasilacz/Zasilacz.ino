#include <avr/io.h>
#include <avr/delay.h>
#include "U8glib.h"

#define BUTTON_PRESSED ((PIND & (1 << PD2)) == 0)

#define SCK A5
#define SDA A4
#define RES 8  
#define DC 9
#define CS 10

const int ADC0 = 0;
const int ADC1 = 1;
const int ADC2 = 2;

float vol = 0;
uint8_t counter = 0;

//INT0 interrupt function
ISR(INT0_vect){
  while(BUTTON_PRESSED){
    //WAIT
  }
  delay(20);
  counter++;
  if(counter == 3) counter = 0;
}

uint16_t adc_result(uint8_t channel);
void adc_setup(void);
void button_int_setup(void);
void voltage_mes(uint8_t count);
void draw(uint8_t num, float vol);

U8GLIB_SH1106_128X64 u8g(SCK, SDA, CS, DC, RES);

void setup() {

  button_int_setup();

  DDRD = 0x00;
  PORTD = 0xFF;
  DDRC = 0x00;
  PORTC = 0x00;

  adc_setup();
  
}

void loop() {

  voltage_mes(counter);

}

uint16_t adc_result(uint8_t channel){
  ADMUX = 0b01000000;
  ADMUX |= channel;
  uint8_t loval = 0;
  uint8_t hival = 0;
  uint16_t value = 0;
  ADCSRA |= (1 << ADSC);
  while((ADCSRA & (1 << ADSC)) == 1){  }
  loval = ADCL;
  hival = ADCH;
  value = (hival<<8) | loval; 
  return value;
}

void adc_setup(void){
  ADMUX = 0b01000000;
  ADCSRA = 0b10000111;
}

void button_int_setup(void){
  //Interrupts on
  sei();
  //Falling edge
  EICRA = (1 << ISC01);
  //INT0 enable
  EIMSK = (1 << INT0);
}

void voltage_mes(uint8_t count){
  switch(count){
    case 0:
      vol = adc_result(ADC0);
      vol = (vol / 1023.0) * 12.0;
      u8g.firstPage();
      do {
      draw(0, vol);
      } while( u8g.nextPage() );
      delay(500);
    break;
    case 1:
      vol = adc_result(ADC1);
      vol = (vol / 1023.0) * 5.0;
      u8g.firstPage();
      do {
      draw(1, vol);
      } while( u8g.nextPage() );
      delay(500);
    break;
    case 2:
      vol = adc_result(ADC2);
      vol = (vol / 1023.0) * 12.0;
      u8g.firstPage();
      do {
      draw(2, vol);
      } while( u8g.nextPage() );
      delay(500);
    break;
  }
}

void draw(uint8_t num, float vol){
  u8g.setFont(u8g_font_helvR08);
  u8g.drawStr(3, 15, "Channel:");
  u8g.setPrintPos(50, 15);
  switch(num){
    case 0: u8g.print("regulowany"); break;
    case 1: u8g.print("5V"); break;
    case 2: u8g.print("12V"); break;
  }
  u8g.setFont(u8g_font_helvR18);
  u8g.setPrintPos(35, 50);
  u8g.print(vol);
}