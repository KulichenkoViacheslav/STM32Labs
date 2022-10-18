#include "tsi.h"
#include "adc.h"

#define COUNT_CHANNELS 3
#define COUNT_VALUE 10
#define ADC_BUFFER_SIZE (COUNT_CHANNELS * COUNT_VALUE)

#define V_25 0.76
#define AVG_SLOPE 2.5

static uint32_t adc_value_buffer[ADC_BUFFER_SIZE] = {0};

void tsi_init(void)
{
  HAL_ADC_Start_DMA(&hadc1, adc_value_buffer, ADC_BUFFER_SIZE);
}

float tsi_get_value(void)
{
  uint32_t value_vcc = 0;
  uint32_t value_tsi = 0;
  uint8_t index = 0;
  
  for(index = 0; index < COUNT_VALUE; index ++)
  {
    value_vcc += adc_value_buffer[COUNT_CHANNELS * index];
    value_tsi += adc_value_buffer[COUNT_CHANNELS * index + 1];
  }
  value_vcc = value_vcc / COUNT_VALUE;
  value_tsi = value_tsi / COUNT_VALUE;
  
  float vcc = 1.21 * 4095 / value_vcc;
  float tsi = vcc * value_tsi / 4095;
  float temperature = ((tsi - V_25) / (AVG_SLOPE / 1000))  + 25;
  
  return temperature;
}
