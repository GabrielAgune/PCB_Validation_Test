#include <stdio.h>
#include <string.h>
#include "cli.h"
#include "usart.h"

// Nossos módulos de hardware
#include "pcb_relay.h"
#include "pcb_temperature.h"
#include "pcb_oscillator.h"
#include "pcb_frequency.h"
#include "tim.h" 

// --- Buffer e Flags de Controle ---
#define RX_BUFFER_SIZE 64
static uint8_t rx_buffer[RX_BUFFER_SIZE];
static uint8_t rx_char;
static uint32_t buffer_index = 0;
static volatile uint8_t command_ready_flag = 0;
static volatile uint8_t quit_monitor_flag = 0;

/**
 * @brief Função para o modo de monitoramento contínuo de frequência, com cálculo de min/max.
 */
static void CLI_Frequency_Monitor_Loop(void)
{
  uint64_t freq_max = 0;
  uint64_t freq_min = 20000000; // Inicia com um valor alto para garantir que a primeira leitura seja menor
  uint64_t freq_atual = 0;

  printf("\r\n--- MODO DE MONITORAMENTO DE FREQUENCIA ---\r\n");
  printf("Pressione a tecla 'q' para sair.\r\n\r\n");
  
  quit_monitor_flag = 0; 
  buffer_index = 0;
  command_ready_flag = 0;

  while (quit_monitor_flag == 0)
  {
    // Zera os contadores para uma nova medição de 1 segundo
    Frequency_Reset();
    
    // Aguarda a janela de tempo de 1 segundo
    HAL_Delay(1000);
    
    // Faz a leitura "atômica" dos contadores
    HAL_NVIC_DisableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
    uint32_t overflows = Frequency_Get_Overflow_Count();
    uint32_t final_count = Frequency_Get_Pulse_Count();
    HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
    
    // Calcula a frequência total
    freq_atual = ((uint64_t)overflows * 65536) + final_count;
    
    // Atualiza os valores mínimo e máximo
    if (freq_atual > freq_max)
    {
      freq_max = freq_atual;
    }
    if (freq_atual < freq_min)
    {
      freq_min = freq_atual;
    }
    
    // Imprime os valores na mesma linha
    printf("Atual: %-7llu Hz | Min: %-7llu Hz | Max: %-7llu Hz\n\r", freq_atual, freq_min, freq_max);
  }

  printf("\r\n\n--- Fim do Monitoramento ---\r\n");
  printf("Faixa de Frequencia do Trimpot:\r\n");
  printf("Minimo: %llu Hz\r\n", freq_min);
  printf("Maximo: %llu Hz\r\n", freq_max);
}

/**
 * @brief Imprime a lista de comandos disponíveis.
 */
static void CLI_Print_Help(void)
{
  printf("--- Comandos Disponiveis ---\r\n");
  printf("relay on        -> Liga o rele\r\n");
  printf("relay off       -> Desliga o rele\r\n");
  printf("temp            -> Le a temperatura (valor ADC)\r\n");
  printf("tempc           -> Le a temperatura em Celsius\r\n");
  printf("osc             -> Le o estado do oscilador\r\n");
  printf("osc frec        -> Mede a frequencia (leitura unica)\r\n");
  printf("osc monitor     -> Inicia medicao continua de frequencia\r\n");
  printf("                   (Pressione a tecla 'q' para sair)\r\n");
  printf("test pwm on     -> Liga o gerador de teste de 10kHz\r\n");
  printf("test pwm off    -> Desliga o gerador de teste\r\n");
  printf("help            -> Mostra esta ajuda\r\n");
  printf("----------------------------\r\n");
}


void CLI_Init(void)
{
  printf("----- CLI de Validacao de PCB -----\r\n");
  printf("Digite 'help' para ver os comandos.\r\n");
  printf("> ");
  HAL_UART_Receive_IT(&huart2, &rx_char, 1);
}

void CLI_Process(void)
{
  if (command_ready_flag == 0) return;
  printf("%s\r\n", rx_buffer);
  
  // Renomeei o comando 'osc freq' para 'osc frec' para evitar conflito com 'q'
  if (strcmp((char*)rx_buffer, "help") == 0) CLI_Print_Help();
  else if (strcmp((char*)rx_buffer, "relay on") == 0) { Relay_On(); printf("Rele LIGADO.\r\n"); }
  else if (strcmp((char*)rx_buffer, "relay off") == 0) { Relay_Off(); printf("Rele DESLIGADO.\r\n"); }
  else if (strcmp((char*)rx_buffer, "temp") == 0) { uint32_t val = Temperature_Read_Raw(); printf("Valor ADC da Temperatura: %u\r\n", val); }
  else if (strcmp((char*)rx_buffer, "tempc") == 0) { uint32_t raw = Temperature_Read_Raw(); float celsius = Temperature_ConvertToCelsius(raw); printf("Temperatura: %.2f C\r\n", celsius); }
  else if (strcmp((char*)rx_buffer, "osc") == 0) { GPIO_PinState state = Oscillator_Get_State(); printf("Estado do Oscilador: %s\r\n", state == GPIO_PIN_SET ? "HIGH (1)" : "LOW (0)"); }
  else if (strcmp((char*)rx_buffer, "osc frec") == 0)
  {
    printf("Iniciando medicao por 1 segundo...\r\n");
    Frequency_Reset();
    HAL_Delay(1000);
    HAL_NVIC_DisableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
    uint32_t overflows = Frequency_Get_Overflow_Count();
    uint32_t final_count = Frequency_Get_Pulse_Count();
    HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
    uint64_t total_pulsos = ((uint64_t)overflows * 65536) + final_count;
    printf("Frequencia do Oscilador: %llu Hz\r\n", total_pulsos);
  }
  else if (strcmp((char*)rx_buffer, "osc monitor") == 0) CLI_Frequency_Monitor_Loop();
  else if (strcmp((char*)rx_buffer, "test pwm on") == 0) { HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1); printf("Gerador de teste de 10kHz LIGADO no pino PA6.\r\n"); }
  else if (strcmp((char*)rx_buffer, "test pwm off") == 0) { HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1); printf("Gerador de teste DESLIGADO.\r\n"); }
  else printf("Comando desconhecido: '%s'\r\n", rx_buffer);
  command_ready_flag = 0;
  printf("> ");
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART2)
  {
    HAL_UART_Receive_IT(&huart2, &rx_char, 1);
    if (rx_char == 'q' || rx_char == 'Q')
    {
      quit_monitor_flag = 1;
      return; 
    }
    if (rx_char == '\r' || rx_char == '\n')
    {
      if (buffer_index > 0)
      {
        rx_buffer[buffer_index] = '\0';
        command_ready_flag = 1;
        buffer_index = 0;
      }
    }
    else if (buffer_index < RX_BUFFER_SIZE - 1)
    {
      rx_buffer[buffer_index++] = rx_char;
    }
  }
}