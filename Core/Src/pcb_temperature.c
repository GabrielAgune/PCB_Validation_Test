#include "pcb_temperature.h"
#include "adc.h"

// --- CONSTANTES DE CALIBRA��O (BASEADO NOS SEUS DADOS) ---
// --- CONSTANTES DE CALIBRA��O (ATUALIZADAS COM SEUS NOVOS DADOS) ---
#define ADC_POINT1      3251.0f
#define TEMP_POINT1     21.1f
#define ADC_POINT2      3398.0f
#define TEMP_POINT2     27.2f

uint32_t Temperature_Read_Raw(void)
{
  #define NUM_AMOSTRAS 10 // N�mero de amostras para a m�dia. Aumente para mais suavidade.
  
  uint32_t soma_adc = 0;
  uint32_t valor_adc_instantaneo = 0;

  for (int i = 0; i < NUM_AMOSTRAS; i++)
  {
    // Inicia a convers�o
    HAL_ADC_Start(&hadc1);

    // Espera a convers�o terminar
    if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
    {
      valor_adc_instantaneo = HAL_ADC_GetValue(&hadc1);
      soma_adc += valor_adc_instantaneo;
    }

    // Para a convers�o
    HAL_ADC_Stop(&hadc1);
    
    // Pequena pausa entre as leituras para capturar varia��es no tempo
    HAL_Delay(1); 
  }

  // Retorna a m�dia das leituras
  return soma_adc / NUM_AMOSTRAS;
}


/**
  * @brief  Converte o valor ADC bruto para Graus Celsius usando CALIBRA��O LINEAR.
  * @param  adc_raw_value: O valor de 12 bits lido do ADC.
  * @retval Temperatura calculada em Graus Celsius.
  */
float Temperature_ConvertToCelsius(uint32_t adc_raw_value)
{
  float adc_atual = (float)adc_raw_value;
  float temperatura;

  // Calcula o "slope" (inclina��o da reta)
  float slope = (TEMP_POINT2 - TEMP_POINT1) / (ADC_POINT2 - ADC_POINT1);

  // Aplica a f�rmula de interpola��o linear: y = y1 + m * (x - x1)
  temperatura = TEMP_POINT1 + (slope * (adc_atual - ADC_POINT1));

  return temperatura;
}