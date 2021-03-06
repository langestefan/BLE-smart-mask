/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr.h>
#include <settings/settings.h>

#include "event_manager.h"

#define MODULE settings_loader
#include <caf/events/module_state_event.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(MODULE);

#define THREAD_STACK_SIZE	1024
#define THREAD_PRIORITY		K_PRIO_PREEMPT(K_LOWEST_APPLICATION_THREAD_PRIO)

#define SETTINGS_LOADER_USE_THREAD 1

static struct k_thread thread;
static K_THREAD_STACK_DEFINE(thread_stack, THREAD_STACK_SIZE);


static void load_settings_thread(void)
{
	LOG_INF("Settings load thread started");

	int err = settings_load();

	if (err) {
		LOG_ERR("Cannot load settings");
		module_set_state(MODULE_STATE_ERROR);
	} else {
		LOG_INF("Settings loaded");
		module_set_state(MODULE_STATE_READY);
	}
}

static void start_loading_thread(void)
{
	k_thread_create(&thread, thread_stack,
			THREAD_STACK_SIZE,
			(k_thread_entry_t)load_settings_thread,
			NULL, NULL, NULL,
			THREAD_PRIORITY, 0, K_NO_WAIT);
	k_thread_name_set(&thread, MODULE_NAME "_thread");
}

static void load_settings(void)
{
	if (IS_ENABLED(SETTINGS_LOADER_USE_THREAD)) {
		start_loading_thread();
	} else {
		int err = settings_load();

		if (err) {
			LOG_ERR("Cannot load settings");
			module_set_state(MODULE_STATE_ERROR);
		} else {
			LOG_INF("Settings loaded");
			module_set_state(MODULE_STATE_READY);
		}
	}
}

static bool module_event_handler(const struct module_state_event *event)
{
	/* Settings need to be loaded after all client modules are ready. */
	const void * const req_modules[] = {
		MODULE_ID(main),
//		MODULE_ID(ble_adv),
//                MODULE_ID(ble_state),
                #if CONFIG_CAF_BLE_BOND_SUPPORTED 
 //               MODULE_ID(ble_bond), 
                #endif
	};

	static uint32_t req_state;

	BUILD_ASSERT(ARRAY_SIZE(req_modules) < (8 * sizeof(req_state)),
			"Array size bigger than number of bits");

	if (req_state == BIT_MASK(ARRAY_SIZE(req_modules))) {
		/* Already initialized */
		return false;
	}

	for (size_t i = 0; i < ARRAY_SIZE(req_modules); i++) {
		if (check_state(event, req_modules[i], MODULE_STATE_READY)) {
			unsigned int flag = BIT(i);

			/* Catch double initialization of any module */
			__ASSERT_NO_MSG((req_state & flag) == 0);

			req_state |= flag;

			if (req_state == BIT_MASK(ARRAY_SIZE(req_modules))) {
				load_settings();
			}

			break;
		}
	}
	return false;
}

static bool event_handler(const struct event_header *eh)
{
	if (is_module_state_event(eh)) {
		return module_event_handler(cast_module_state_event(eh));
	}

	/* If event is unhandled, unsubscribe. */
	__ASSERT_NO_MSG(false);

	return false;
}

EVENT_LISTENER(MODULE, event_handler);
EVENT_SUBSCRIBE(MODULE, module_state_event);
