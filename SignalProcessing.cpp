#include "SignalProcessingLib.h"

SignalProcessing::SignalProcessing(float proportional, float offset, float max_frequency){
  proportional_constant=proportional;
  offset_constant=offset;
  maximun_frequency=max_frequency;
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

void SignalProcessing::factorFrequencies(){
  low_factor_frequencies = maximun_frequency/sampling_frequency;
  if((low_factor_frequencies <= 0.001)){// && (low_factor_frequencies >= 1)){
    low_factor_frequencies = 0.001;
  }
  high_factor_frequencies = 1 - low_factor_frequencies;
}

void SignalProcessing::loosenSignal(){

}

void SignalProcessing::averageValue(){
  pre_average_value=pre_average_value*high_factor_frequencies+instant_value*low_factor_frequencies;  
  average_value=average_value*high_factor_frequencies+pre_average_value*low_factor_frequencies;
}

void SignalProcessing::averageQuadraticValue(){
  pre_average_quadratic_value=sqrt(pre_average_quadratic_value*pre_average_quadratic_value*high_factor_frequencies+instant_value*instant_value*low_factor_frequencies);
  average_quadratic_value=average_quadratic_value*high_factor_frequencies+pre_average_quadratic_value*low_factor_frequencies;
}

void SignalProcessing::positiveAverageValue(){
  if(instant_value > 0){
    pre_positive_average_value=pre_positive_average_value*high_factor_frequencies+instant_value*low_factor_frequencies;
  }
  else{
    pre_positive_average_value=pre_positive_average_value*high_factor_frequencies;
  }
  positive_average_value=positive_average_value*high_factor_frequencies+pre_positive_average_value*low_factor_frequencies;
}

void SignalProcessing::negativeAverageValue(){

  if(instant_value < 0){
    pre_negative_average_value=pre_negative_average_value*high_factor_frequencies+instant_value*low_factor_frequencies;
  }
  else{
    pre_negative_average_value=pre_negative_average_value*high_factor_frequencies;
  }
  negative_average_value=negative_average_value*high_factor_frequencies+pre_negative_average_value*low_factor_frequencies;
  
  
}

void SignalProcessing::signFactor(){

  if(instant_value < 0){
    pre_sign_factor=pre_sign_factor*high_factor_frequencies+1*low_factor_frequencies;
  }
  else{
    pre_sign_factor=pre_sign_factor*high_factor_frequencies;
  }
  sign_factor=sign_factor*high_factor_frequencies+pre_sign_factor*low_factor_frequencies;
}

void SignalProcessing::averageNegativeValuesRespectAverageValue(){
  average_negative_values_respect_average_value=average_value * sign_factor - negative_average_value;
}
