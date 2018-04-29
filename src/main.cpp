#include <Arduino.h>
#include <TinyWire.h>

#define ADC1 A3
#define ADC2 A2
#define PWM_PIN 1
#define I2C_ADDRESS 1

int ad_val1 {0}, ad_val2 {0}, pwmval {0};

void onI2CReceive(int howMany){
	// loops, until all received bytes are read
	while(TinyWire.available()>0){
		pwmval = TinyWire.read();
	}
}

void onI2CRequest() {
	TinyWire.send(ad_val1);
  TinyWire.send(ad_val2);
  TinyWire.send(pwmval);
}

void setup() {
  pinMode(PWM_PIN, OUTPUT);
  pinMode(ADC1, INPUT);
  pinMode(ADC2, INPUT);

  TinyWire.begin(I2C_ADDRESS);
  TinyWire.onReceive(onI2CReceive);
  TinyWire.onRequest(onI2CRequest);
}

void loop() {
  ad_val1 = analogRead(ADC1);
  ad_val2 = analogRead(ADC2);
  analogWrite(PWM_PIN, pwmval);
}
