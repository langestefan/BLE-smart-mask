/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <event_manager.h>
#include <config_event.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/services/bas.h>

#define MODULE main
#include <caf/events/module_state_event.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(MODULE);

#define INIT_VALUE1 3

static void bas_notify(void)
{
	uint8_t battery_level = bt_bas_get_battery_level();

	battery_level--;

	if (!battery_level) {
		battery_level = 100U;
	}

	bt_bas_set_battery_level(battery_level);
}

void main(void)
{
	if (event_manager_init()) {
		LOG_ERR("Event Manager not initialized");
	} 

        else 
        {
		struct config_event *event = new_config_event();
		event->init_value1 = INIT_VALUE1;
		EVENT_SUBMIT(event);
                
                /* Let CAF know main module is ready */
                module_set_state(MODULE_STATE_READY);
	}

        while(1)
        {
          	k_sleep(K_SECONDS(1));

		/* Battery level simulation */
		bas_notify();
        }
}
