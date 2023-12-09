#include <avr/io.h>
#include <avr/delay.h>

//D8 -> PB4
//D9 -> PB5 (ADC12)

const int ADC0 = 0;
const int ADC1 = 1;
const int ADC2 = 2;

uint16_t adc_result(uint8_t channel);

float VOL_REG = 0;
float VOL_5 = 0;
float VOL_12 = 0;

void setup() {

  DDRC = 0x00;
  PORTC = 0x00;
  //A0 -> ADC0
  ADMUX = 0b01000000;
  ADCSRA = 0b10000111;
  
  Serial.begin(9600);
}

void loop() {
  
  VOL_REG = adc_result(ADC0);
  VOL_REG = (VOL_REG / 1023.0) * 12.0;
  Serial.println(VOL_REG);
  delay(500);

  // VOL_5 = adc_result(ADC1);
  // VOL_5 = (VOL_5 / 1023.0) * 5.0;
  // Serial.println(VOL_5);
  // delay(500);

  // VOL_12 = adc_result(ADC2);
  // VOL_12 = (VOL_12 / 1023.0) * 12.0;
  // Serial.println(VOL_12);
  // delay(500);

}

uint16_t adc_result(uint8_t channel){
  ADMUX = 0b01000000;
  ADMUX |= channel;
  Serial.print("ADMUX:  ");
  Serial.println(ADMUX, BIN);
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