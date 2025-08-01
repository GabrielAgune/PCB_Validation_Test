#ifndef INC_PCB_TEMPERATURE_H_
#define INC_PCB_TEMPERATURE_H_

#include "main.h"

// Protótipos das Funções Públicas
uint32_t Temperature_Read_Raw(void);
float Temperature_ConvertToCelsius(uint32_t adc_raw_value); // <-- ADICIONE ESTA LINHA

#endif /* INC_PCB_TEMPERATURE_H_ */