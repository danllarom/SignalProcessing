#include <Arduino.h>
#ifndef _SignalProcessing_h
#define _SignalProcessing_h

class SignalProcessing{
    public:
      //atributos publicos:
      float proportional_constant=1; 
      float offset_constant=0;
      float time_now;
      float time_before;
      
      float instant_value;
      float instant_value_before;
      float sampling_frequency;
      float maximun_frequency;
      float low_factor_frequencies;
      float high_factor_frequencies;  

      float loosen_signal;   //desface  

      float pre_average_value;
      float average_value;

      float pre_average_quadratic_value;
      float average_quadratic_value;

      float pre_positive_average_value;
      float positive_average_value;

      float pre_negative_average_value;
      float negative_average_value;

      float pre_sign_factor;
      float sign_factor;

      float average_negative_values_respect_average_value;


      //constructores: 
      SignalProcessing(float proportional, float offset, float maximun_frequency);
                              
      //metodos:
      void Processing(float value, uint32_t t);

    private:
      //atributos privados:
      void instantValue(float value);
      void samplingFrequency();
      void loosenSignal();
      void averageValue();
      void averageQuadraticValue();
      void positiveAverageValue();
      void negativeAverageValue();
      void signFactor();
      void averageNegativeValuesRespectAverageValue();
      void factorFrequencies();
};

#endif
