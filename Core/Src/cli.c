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

// ... (CLI_Print_Help e CLI_Frequency_Monitor_Loop continuam iguais à versão que você tem) ...
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

static void CLI_Frequency_Monitor_Loop(void)
{
  printf("\r\n--- MODO DE MONITORAMENTO DE FREQUENCIA ---\r\n");
  printf("Pressione a tecla 'q' para sair.\r\n\r\n");
  quit_monitor_flag = 0; 
  buffer_index = 0;
  while (quit_monitor_flag == 0)
  {
    #define JANELA_DE_TEMPO_MONITOR_MS 10 
    Frequency_Reset();
    HAL_Delay(JANELA_DE_TEMPO_MONITOR_MS);
    uint32_t pulsos_contados = Frequency_Get_Pulse_Count();
    uint32_t frequencia_hz = pulsos_contados * (1000 / JANELA_DE_TEMPO_MONITOR_MS);
    printf("Frequencia: %-10u Hz\r", (unsigned int)frequencia_hz);
  }
  printf("\r\n\n--- Fim do Monitoramento ---\r\n");
}


void CLI_Init(void)
{
  printf("----- CLI de Validacao de PCB -----\r\n");
  printf("Digite 'help' para ver os comandos.\r\n");
  printf("> ");
  HAL_UART_Receive_IT(&huart2, &rx_char, 1);
}

// ... (A função CLI_Process também continua igual à última versão) ...
void CLI_Process(void)
{
  if (command_ready_flag == 0) return;
  printf("%s\r\n", rx_buffer);
  if (strcmp((char*)rx_buffer, "help") == 0) CLI_Print_Help();
  else if (strcmp((char*)rx_buffer, "relay on") == 0) { Relay_On(); printf("Rele LIGADO.\r\n"); }
  else if (strcmp((char*)rx_buffer, "relay off") == 0) { Relay_Off(); printf("Rele DESLIGADO.\r\n"); }
  else if (strcmp((char*)rx_buffer, "temp") == 0) { uint32_t val = Temperature_Read_Raw(); printf("Valor ADC da Temperatura: %u\r\n", val); }
  else if (strcmp((char*)rx_buffer, "tempc") == 0) { uint32_t raw = Temperature_Read_Raw(); float celsius = Temperature_ConvertToCelsius(raw); printf("Temperatura: %.2f C\r\n", celsius); }
  else if (strcmp((char*)rx_buffer, "osc") == 0) { GPIO_PinState state = Oscillator_Get_State(); printf("Estado do Oscilador: %s\r\n", state == GPIO_PIN_SET ? "HIGH (1)" : "LOW (0)"); }
  else if (strcmp((char*)rx_buffer, "osc frec") == 0) {
    #define JANELA_DE_TEMPO_MS 10
    printf("Iniciando medicao por %d ms...\r\n", JANELA_DE_TEMPO_MS);
    Frequency_Reset();
    HAL_Delay(JANELA_DE_TEMPO_MS);
    uint32_t pulsos_contados = Frequency_Get_Pulse_Count();
    uint32_t frequencia_hz = pulsos_contados * (1000 / JANELA_DE_TEMPO_MS);
    printf("Frequencia do Oscilador: %u Hz\r\n", (unsigned int)frequencia_hz);
  }
  else if (strcmp((char*)rx_buffer, "osc monitor") == 0) CLI_Frequency_Monitor_Loop();
  else if (strcmp((char*)rx_buffer, "osc reset") == 0) { Frequency_Reset(); printf("Contador de frequencia reiniciado.\r\n"); }
  else if (strcmp((char*)rx_buffer, "test pwm on") == 0) { HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1); printf("Gerador de teste de 10kHz LIGADO no pino PA6.\r\n"); }
  else if (strcmp((char*)rx_buffer, "test pwm off") == 0) { HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1); printf("Gerador de teste DESLIGADO.\r\n"); }
  else printf("Comando desconhecido: '%s'\r\n", rx_buffer);
  command_ready_flag = 0;
  printf("> ");
}

/**
  * @brief  Callback da interrupção da UART. Versão FINAL.
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART2)
  {
    // Reativa a interrupção imediatamente.
    HAL_UART_Receive_IT(&huart2, &rx_char, 1);

    // Se o caractere for 'q', ele apenas ativa o flag de saída e não faz mais nada.
    // Não será adicionado ao buffer e não irá gerar um "comando desconhecido".
    if (rx_char == 'q' || rx_char == 'Q')
    {
      quit_monitor_flag = 1;
      return; 
    }

    // Processa o caractere para montar a string de comando.
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