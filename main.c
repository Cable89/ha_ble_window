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

#include "ble_stuff.h"
#include "window.h"

#define DIR_RELAY_PIN 16    // P0.16
#define POWER_RELAY_PIN 11  // P0.11

/**@brief Function for application main entry.
 */
int main(void)
{
    // Initialize.
    ble_init();
    nrf_gpio_cfg_output(DIR_RELAY_PIN);
    nrf_gpio_cfg_output(POWER_RELAY_PIN);
    nrf_gpio_pin_clear(DIR_RELAY_PIN);
    nrf_gpio_pin_clear(POWER_RELAY_PIN);

    create_timers();

    // Start execution.
    NRF_LOG_INFO("oysm ble window started");
    advertising_start();

    // Enter main loop.
    for (;;)
    {
        idle_state_handle();
    }
}
