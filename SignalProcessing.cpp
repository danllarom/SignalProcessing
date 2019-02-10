#include "SignalProcessingLib.h"

SignalProcessing::SignalProcessing(float proportional, float offset){
  proportional_constant=proportional;
  offset_constant=offset;
}

void SignalProcessing::Processing(float value, uint32_t t){
  time_before=time_now;
  time_now=(float)t/1000000;
  
  instantValue(value);
  samplingFrequency();
  factorFrequencies();
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
  sampling_frequency=time_now - time_before;
  sampling_frequency=1/sampling_frequency;
}

void SignalProcessing::signalFrequency(){

}

void SignalProcessing::factorFrequencies(){
  low_factor_frequencies = signal_frequency/(10*sampling_frequency);
  if((low_factor_frequencies <= 0.001)){// && (low_factor_frequencies >= 1)){
    low_factor_frequencies = 0.001;
  }
  high_factor_frequencies = 1 - low_factor_frequencies;
}

void SignalProcessing::loosenSignal(){
  if(instant_value == 0 && instant_value_before < instant_value){
      if(loosen_signal != 0){
        signal_frequency = signal_frequency*0.9 + 0.1/loosen_signal;
      }
      loosen_signal=0;
  }
  if(instant_value > 0){
      if(instant_value_before < 0){
        if(loosen_signal != 0){
          signal_frequency = signal_frequency*0.9 + 0.1/loosen_signal;
        }
        loosen_signal=0;
      }
  }  
  loosen_signal=loosen_signal+1/sampling_frequency;

}

void SignalProcessing::averageValue(){
    
  average_value=average_value*high_factor_frequencies+instant_value*low_factor_frequencies;
  
}

void SignalProcessing::averageQuadraticValue(){
  if((average_quadratic_value*average_quadratic_value*high_factor_frequencies+instant_value*instant_value*low_factor_frequencies) > 0){
    average_quadratic_value=sqrt(average_quadratic_value*average_quadratic_value*high_factor_frequencies+instant_value*instant_value*low_factor_frequencies);
  }
}

void SignalProcessing::positiveAverageValue(){

  if(instant_value > 0){
    positive_average_value=positive_average_value*high_factor_frequencies+instant_value*low_factor_frequencies;
  }
  positive_average_value=positive_average_value*high_factor_frequencies;

  
}

void SignalProcessing::negativeAverageValue(){

  if(instant_value < 0){
    negative_average_value=negative_average_value*high_factor_frequencies+instant_value*low_factor_frequencies;
  }
  negative_average_value=negative_average_value*high_factor_frequencies;
  
}

void SignalProcessing::signFactor(){

  if(instant_value < 0){
    sign_factor=sign_factor*high_factor_frequencies+1*low_factor_frequencies;
  }
  else{
    sign_factor=sign_factor*high_factor_frequencies;
  }
  
}

void SignalProcessing::averageOscillatingSignal(){

  if((instant_value - average_value) > 0){
    average_oscillating_signal=average_oscillating_signal*high_factor_frequencies+(instant_value - average_value)*low_factor_frequencies;
  }
  average_oscillating_signal=average_oscillating_signal*high_factor_frequencies;
  
}

void SignalProcessing::averageNegativeValuesRespectAverageValue(){
  average_negative_values_respect_average_value=average_value * sign_factor - negative_average_value;
}
