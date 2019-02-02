#include "SignalProcessing.h"
int i;
float constant=1, offset=0, value1, value2, value3;
uint32_t t;

SignalProcessing measurements(constant, offset);

void setup() {
  Serial.begin(9600);
}

void loop() {
  value1=analogRead(A0);
  value2=analogRead(A0);
  value3=analogRead(A0);
  t=micros();
  for(i=0 ; i<80 ; i++){
    measurements.Processing(value1, micros());
    //delayMicroseconds(200);
  }
  t=micros()-t;

  Serial.print("instant value = ");
  Serial.println(measurements.instant_value);
  Serial.print("average value = ");
  Serial.println(measurements.average_value);
  Serial.print("average quadratic value = ");
  Serial.println(measurements.average_quadratic_value);
  Serial.print("positive average value = ");
  Serial.println(measurements.positive_average_value);
  Serial.print("negative average valuee = ");
  Serial.println(measurements.negative_average_value);
  Serial.print("sign factor = ");
  Serial.println(measurements.sign_factor);
  Serial.print("sampling frequency = ");
  Serial.println(measurements.sampling_frequency);
  Serial.print("average oscillating signal = ");
  Serial.println(measurements.average_oscillating_signal);
  Serial.print("average negative values respect average value = ");
  Serial.println(measurements.average_negative_values_respect_average_value);
  Serial.print("time processin = ");
  Serial.println(t);
  Serial.println();

  delay(100);
}
