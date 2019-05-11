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

#include "window.h"


/**@brief Function for opening window.
 */
void window_open(void){
  nrf_gpio_pin_write(DIR_RELAY_PIN, DIR_OPEN);
  nrf_gpio_pin_write(POWER_RELAY_PIN, 1);
  for(int i=0; i<10; i++){
    //nrf_delay_ms(1000);
  }
  nrf_gpio_pin_write(POWER_RELAY_PIN, 0);
}

/**@brief Function for closing window.
 */
void window_close(void){
  nrf_gpio_pin_write(DIR_RELAY_PIN, DIR_CLOSE);
  nrf_gpio_pin_write(POWER_RELAY_PIN, 1);
  for(int i=0; i<10; i++){
    //nrf_delay_ms(1000);
  }
  nrf_gpio_pin_write(POWER_RELAY_PIN, 0);
}

void window_actuate(uint8_t dir){

}