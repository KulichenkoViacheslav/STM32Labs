#include "termometer.h"
#include "..\..\Components\Temperature_sensor_external\tse.h"
#include "..\..\Components\Temperature_sensor_internal\tsi.h"
#include "..\..\Components\Timer\timer.h"

float temperature_mcu = 0;

void termometer_init(void)
{
  tse_init();
  tsi_init();
  timer_init();
}


void termometer_run(void)
{
  temperature_mcu = tsi_get_value();
}
