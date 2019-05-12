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

uint8_t window_position = 0;

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
  window_actuate(DIR_OPEN, 10000);
  window_position = 255;
}

/**@brief Function for closing window.
 */
void window_close(void){
  window_actuate(DIR_CLOSE, 10000);
  window_position = 0;
}

void window_set_position(uint8_t position){
  uint16_t duration = 0;
  uint8_t direction = DIR_CLOSE;
  if(position > window_position){
    duration = (OPENING_DURATION * (position - window_position)) / WINDOW_TRAVEL_LENGTH;
    direction = DIR_OPEN;
    window_actuate(direction, duration);
    window_position = position;
  } else if (position < window_position){
    duration = (CLOSING_DURATION * (window_position - position)) / WINDOW_TRAVEL_LENGTH;
    direction = DIR_CLOSE;
    window_actuate(direction, duration);
    window_position = position;
  } else {
    // Do nothing
  }
}

void window_actuate(uint8_t dir, uint16_t duration){
  nrf_gpio_pin_write(DIR_RELAY_PIN, dir);
  nrf_gpio_pin_write(POWER_RELAY_PIN, 1);
  app_timer_start(m_single_shot_timer_id, APP_TIMER_TICKS(duration), NULL);
}

uint8_t get_window_position(void){
  return window_position;
}