#include "SignalProcessing.h"

SignalProcessing::SignalProcessing(float proportional, float offset){
  proportional_constant=proportional;
  offset_constant=offset;
}

void SignalProcessing::Processing(float value, uint32_t t){
  time_before=time_now;
  time_now=(float)t/1000000;
  
  instantValue(value);
  samplingFrequency();
  signalFrequency();
  loosenSignal();
  averageValue();
  averageQuadraticValue();
  positiveAverageValue();
  negativeAverageValue();
  signFactor();
  averageOscillatingSignal();
  averageNegativeValuesRespectAverageValue();
}

void SignalProcessing::instantValue(float value){
  instant_value_before=instant_value;
  value=value*proportional_constant;
  instant_value=value-offset_constant;
}
void SignalProcessing::samplingFrequency(){
  sampling_frequency=time_now;
  sampling_frequency=sampling_frequency-time_before;
  sampling_frequency=1/sampling_frequency;
}

void SignalProcessing::signalFrequency(){
  float frequency=0;
  frequency=instant_value-instant_value_before;
  frequency=frequency/sampling_frequency;
  frequency=frequency/instant_value;
  signal_frequency=frequency*tan(signal_frequency*loosen_signal);
}

void SignalProcessing::loosenSignal(){
  if(instant_value==0){
      loosen_signal=0;
  }
  else if(instant_value>0){
      if(instant_value_before<0){
        loosen_signal=0; 
      }
  }
  else{
      loosen_signal=time_now-loosen_signal;
  }
}

void SignalProcessing::averageValue(){
  float a=signal_frequency/sampling_frequency;
  float b;
  if(a<0.001){
    a=0.001;
  }
  b=1-a;
  
  average_value=average_value*b+instant_value*a;
}

void SignalProcessing::averageQuadraticValue(){
  float a=signal_frequency/sampling_frequency;
  float b;
  if(a<0.001){
    a=0.001;
  }
  b=1-a;
  
  average_quadratic_value=sqrt(average_quadratic_value*average_quadratic_value*b+instant_value*instant_value*a);
}

void SignalProcessing::positiveAverageValue(){
  float a=signal_frequency/sampling_frequency;
  float b;
  if(a<0.001){
    a=0.001;
  }
  b=1-a;
  if(instant_value > 0){
    positive_average_value=positive_average_value*b+instant_value*a;
  }
}

void SignalProcessing::negativeAverageValue(){
  float a=signal_frequency/sampling_frequency;
  float b;
  if(a<0.001){
    a=0.001;
  }
  b=1-a;
  if(instant_value < 0){
    negative_average_value=negative_average_value*b+instant_value*a;
  }
}

void SignalProcessing::signFactor(){
  float a=signal_frequency/sampling_frequency;
  float b;
  if(a<0.001){
    a=0.001;
  }
  b=1-a;
  if(instant_value < 0){
    sign_factor=sign_factor*b+1*a;
  }
}

void SignalProcessing::averageOscillatingSignal(){
  float a=signal_frequency/sampling_frequency;
  float b;
  if(a<0.001){
    a=0.001;
  }
  b=1-a;
  if((instant_value - average_value) > 0){
    average_oscillating_signal=average_oscillating_signal*b+(instant_value - average_value)*a;
  }
}

void SignalProcessing::averageNegativeValuesRespectAverageValue(){
  average_negative_values_respect_average_value=average_value * sign_factor - negative_average_value;
}
