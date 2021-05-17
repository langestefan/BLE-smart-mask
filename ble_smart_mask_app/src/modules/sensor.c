/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr.h>

/* logging */
#include <logging/log.h>
#define MODULE sensor
LOG_MODULE_REGISTER(MODULE);

#include "config_event.h"
#include "trigger_measurement_event.h"
#include "sensor_packet_event.h"

#define SENSOR_THREAD_STACK_SIZE 800
#define SENSOR_THREAD_PRIORITY 1
#define SENSOR_THREAD_SLEEP 30000

static K_THREAD_STACK_DEFINE(sensor_thread_stack,
			     SENSOR_THREAD_STACK_SIZE);

static struct k_thread sensor_thread;

/* variables */
static int8_t value1;

/* Sensor thread main function, this will loop every 500 miliseconds */
static void sensor_thread_fn(void)
{
        int counter = 0;

	while (true) 
        {
                LOG_INF("Sleep %i ms", SENSOR_THREAD_SLEEP);
		k_sleep(K_MSEC(SENSOR_THREAD_SLEEP));
                struct trigger_measurement_event *event = new_trigger_measurement_event();
                event->init_value1 = counter;
                EVENT_SUBMIT(event);      
                counter++;
	}
}

/* Init function is called when initial config event is triggered */
static void init(void)
{
	k_thread_create(&sensor_thread,
			sensor_thread_stack,
			SENSOR_THREAD_STACK_SIZE,
			(k_thread_entry_t)sensor_thread_fn,
			NULL, NULL, NULL,
			SENSOR_THREAD_PRIORITY,
			0, K_NO_WAIT);
}

/* Event handler. Called whenever an event comes in.  */
static bool event_handler(const struct event_header *eh)
{
	if (is_config_event(eh)) 
        {
                /* config event received */
                LOG_INF("Config event received by sensor module");
		struct config_event *ce = cast_config_event(eh); // access the event data

                value1 = ce->init_value1; // acces data in event header, write to variable

		init();
		return false;
	}

	/* If event is unhandled, unsubscribe. */
	__ASSERT_NO_MSG(false);

	return false;
}

EVENT_LISTENER(MODULE, event_handler);
EVENT_SUBSCRIBE(MODULE, config_event);