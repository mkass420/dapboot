#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/rcc.h>

static void adc_setup(void) {
  int i;

  rcc_periph_clock_enable(RCC_ADC1);

  /* Make sure the ADC doesn't run during config. */
  adc_power_off(ADC1);

  /* We configure everything for one single conversion. */
  adc_disable_scan_mode(ADC1);
  adc_set_single_conversion_mode(ADC1);
  adc_disable_external_trigger_regular(ADC1);
  adc_set_right_aligned(ADC1);
  /* We want to read the temperature sensor, so we have to enable it. */
  adc_enable_temperature_sensor();
  adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_28DOT5CYC);

  adc_power_on(ADC1);

  /* Wait for ADC starting up. */
  for (i = 0; i < 800000; i++) /* Wait a bit. */
    __asm__("nop");

  adc_reset_calibration(ADC1);
  adc_calibrate(ADC1);
}
