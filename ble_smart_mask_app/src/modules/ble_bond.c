/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <bluetooth/bluetooth.h>

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


/* main event handler function */
static bool event_handler(const struct event_header *eh)
{
        LOG_INF("BLE bond event handler");

        if (is_config_event(eh)) 
        {
                /* config event received */
                LOG_INF("Config event");
		//struct config_event *ce = cast_config_event(eh); // access the event data
		//init();
		return false;
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
EVENT_SUBSCRIBE(MODULE, config_event);
