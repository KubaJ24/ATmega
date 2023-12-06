#include <avr/io.h>
#include <avr/delay.h>

//D8 -> PB4
//D9 -> PB5 (ADC12)

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);

  ADCSRA = 0b11000111;
  //Źródłem odniesienia jest AVcc (Vcc)
  ADMUX = 0b01000000;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    // int loval = 0;
    // int hival = 0;
  int wynik = 0;
    // loval = ADCL;
    // hival = ADCH;
    // wynik = (hival<<8) | loval; 
  wynik = analogRead(A0);
  Serial.println(wynik);
  delay(500);
}
