#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "ble.h"
#include "ble_err.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_conn_params.h"
#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "boards.h"
#include "app_timer.h"
#include "app_button.h"
#include "ble_lbs.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "nrf_pwr_mgmt.h"

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "nrf_delay.h"

#include "window.h"

#define DIR_RELAY_PIN 16    // P0.16
#define POWER_RELAY_PIN 11  // P0.11
#define DIR_OPEN 1
#define DIR_CLOSE 0

APP_TIMER_DEF(m_single_shot_timer_id);

/**@brief Timeout handler for the single shot timer.
 */
void single_shot_timer_handler(void * p_context)
{
    nrf_gpio_pin_write(POWER_RELAY_PIN, 0);
}

void create_timers(){
  ret_code_t err_code;

    // Create timer
    err_code = app_timer_create(&m_single_shot_timer_id,
                                APP_TIMER_MODE_SINGLE_SHOT,
                                single_shot_timer_handler);
    APP_ERROR_CHECK(err_code);
}

/**@brief Function for opening window.
 */
void window_open(void){
  nrf_gpio_pin_write(DIR_RELAY_PIN, DIR_OPEN);
  nrf_gpio_pin_write(POWER_RELAY_PIN, 1);
  /*
  for(int i=0; i<10; i++){
    nrf_delay_ms(1000);
  }
  */
  app_timer_start(m_single_shot_timer_id, APP_TIMER_TICKS(10000), NULL);
  //nrf_gpio_pin_write(POWER_RELAY_PIN, 0);
}

/**@brief Function for closing window.
 */
void window_close(void){
  nrf_gpio_pin_write(DIR_RELAY_PIN, DIR_CLOSE);
  nrf_gpio_pin_write(POWER_RELAY_PIN, 1);
  /*
  for(int i=0; i<10; i++){
    nrf_delay_ms(1000);
  }
  */
  app_timer_start(m_single_shot_timer_id, APP_TIMER_TICKS(10000), NULL);
  //nrf_gpio_pin_write(POWER_RELAY_PIN, 0);
}

void window_actuate(uint8_t dir){

}