/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */



#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>
#include <drivers/gpio.h>
#include <soc.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

#include <bluetooth/services/bms.h>

#include <settings/settings.h>

#define MODULE ble_bond
#include <caf/events/module_state_event.h>
#include <caf/events/ble_common_event.h>
#include "config_event.h"

#include <logging/log.h>
LOG_MODULE_REGISTER(MODULE);



enum state {
	STATE_DISABLED,
	STATE_DISABLED_STANDBY,
	STATE_IDLE,
	STATE_STANDBY,
	STATE_SELECT_PEER,
};

struct state_switch {
	enum state state;
	enum state next_state;
	void (*func)(void);
};

//static const struct state_switch state_switch[] = {
//	 /* State           Event         Next state         Callback */
//};

static bool ble_peer_event_handler(const struct ble_peer_event *event)
{

	LOG_INF("BLE peer event");

	return false;
}


static int bms_init(void)
{
	struct bt_bms_init_params init_params = {0};

	/* Enable all possible operation codes */
	init_params.features.delete_requesting.supported = true;
	init_params.features.delete_rest.supported = true;
	init_params.features.delete_all.supported = true;

	/* Require authorization code for operations that
	 * also delete bonding information for other devices
	 * than the requesting client.
	 */
	init_params.features.delete_rest.authorize = true;
	init_params.features.delete_all.authorize = true;

	//init_params.cbs = &bms_callbacks;
                
        /* Let CAF know main module is ready */
        module_set_state(MODULE_STATE_READY);

	return bt_bms_init(&init_params);
        //return true;
}

/* module event handler */
static bool module_event_handler(const struct module_state_event *event)
{
        if (check_state(event, MODULE_ID(ble_state), MODULE_STATE_READY)) {
                LOG_INF("Found bond module ready");
                
                /* Let CAF know bond module is ready */
                module_set_state(MODULE_STATE_READY);
                return true; 
        }

        else {
                return false;
        }

}

/* main event handler function */
static bool event_handler(const struct event_header *eh)
{
        LOG_INF("BLE bond event handler");

        if (is_config_event(eh)) 
        {
                /* config event received */
                LOG_INF("Config event");
		//struct config_event *ce = cast_config_event(eh); // access the event data
		bms_init();
		return false;
	}

        
	if (is_module_state_event(eh)) {
		return module_event_handler(cast_module_state_event(eh));
	}



	if (IS_ENABLED(CONFIG_BT_PERIPHERAL) && is_ble_peer_event(eh)) {
		return ble_peer_event_handler(cast_ble_peer_event(eh));
	}

	/* If event is unhandled, unsubscribe. */
	__ASSERT_NO_MSG(false);

	return false;
}

EVENT_LISTENER(MODULE, event_handler);

EVENT_SUBSCRIBE(MODULE, ble_peer_event);
EVENT_SUBSCRIBE(MODULE, module_state_event);
EVENT_SUBSCRIBE(MODULE, config_event);
