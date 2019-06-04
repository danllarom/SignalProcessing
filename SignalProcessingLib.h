#include <Arduino.h>
#ifndef _SignalProcessing_h
#define _SignalProcessing_h

class SignalProcessing{
    public:
      //atributos publicos:
      double proportional_constant=1; 
      double offset_constant=0;
      double time_now;
      double time_before;
      
      double instant_value;
      double instant_value_before;
      double sampling_frequency;
      double maximun_frequency;
      double low_factor_frequencies;
      double high_factor_frequencies;  

      double loosen_signal;   //desface  

      double pre_average_value;
      double pre2_average_value;
      double average_value;

      double pre_average_quadratic_value;
      double pre2_average_quadratic_value;
      double average_quadratic_value;

      double pre_positive_average_value;
      double pre2_positive_average_value;
      double positive_average_value;

      double pre_negative_average_value;
      double pre2_negative_average_value;
      double negative_average_value;

      double pre_sign_factor;
      double pre2_sign_factor;
      double sign_factor;

      double average_negative_values_respect_average_value;


      //constructores: 
      SignalProcessing(double proportional, double offset, double maximun_frequency);
                              
      //metodos:
      void Processing(double value, double t);

    private:
      //atributos privados:
      void instantValue(double value);
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
