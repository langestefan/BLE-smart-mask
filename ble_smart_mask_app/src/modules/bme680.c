/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/sensor.h>
#include <stdio.h>
//#include <devicetree.h>

/* logging */
#include <logging/log.h>
#define MODULE bme680s
LOG_MODULE_REGISTER(MODULE);

#include "config_event.h"
#include "trigger_measurement_event.h"

/* variables */
const struct device *dev = NULL;
struct sensor_value temp, press, humidity, gas_res;

/* Init function is called when initial config event is triggered */
static void init(void)
{
        /* build device */
        dev = device_get_binding(DT_LABEL(DT_INST(0, bosch_bme680)));
        LOG_INF("Device %p name is %s\n", dev, dev->name);
}

/* Event handler. Called whenever an event comes in.  */
static bool event_handler(const struct event_header *eh)
{
	if (is_config_event(eh)) 
        {
                /* config event received */
                LOG_INF("Config event");
		//struct config_event *ce = cast_config_event(eh); // access the event data
		init();
		return false;
	}

        if (is_trigger_measurement_event(eh)) 
        {
                /* trigger measurement received */
                LOG_INF("Trigger measurement event");
                sensor_sample_fetch(dev);
		sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
		sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
		sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);
		sensor_channel_get(dev, SENSOR_CHAN_GAS_RES, &gas_res);

                /* print result */
		LOG_INF("T: %d.%02d; P: %d.%02d; H: %d.%02d; G: %d.%02d\n",
				temp.val1, temp.val2, press.val1, press.val2,
				humidity.val1, humidity.val2, gas_res.val1,
				gas_res.val2);

                return false;
	}

	/* If event is unhandled, unsubscribe. */
	__ASSERT_NO_MSG(false);

	return false;
}

EVENT_LISTENER(MODULE, event_handler);
EVENT_SUBSCRIBE(MODULE, config_event);
EVENT_SUBSCRIBE(MODULE, trigger_measurement_event);