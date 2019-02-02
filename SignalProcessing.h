#include <arduino.h>

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
      float signal_frequency;
      float loosen_signal;   //desface           
      float average_value;
      float average_quadratic_value;
      float positive_average_value;
      float negative_average_value;
      float sign_factor;
      float average_oscillating_signal;
      float average_negative_values_respect_average_value;
      //constructores: 
      SignalProcessing(float proportional, float offset);
                              
      //metodos:
      void Processing(float value, uint32_t t);

    private:
      //atributos privados:
      void instantValue(float value);
      void samplingFrequency();
      void signalFrequency();
      void loosenSignal();
      void averageValue();
      void averageQuadraticValue();
      void positiveAverageValue();
      void negativeAverageValue();
      void signFactor();
      void averageOscillatingSignal();
      void averageNegativeValuesRespectAverageValue();
};
