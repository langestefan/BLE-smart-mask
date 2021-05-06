/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <stdio.h>

#include "sensor_packet_event.h"

static int log_measurement_event(const struct event_header *eh, char *buf,
				 size_t buf_len)
{
	struct measurement_event *event = cast_measurement_event(eh);

	return snprintf(buf, buf_len, 
                        "val1=%d val2=%d val3=%d", 
                        event->value1, event->value2, event->value3);
}

/* define info for profiling event */
EVENT_INFO_DEFINE(measurement_event,
		  NULL,
		  NULL,
		  NULL);

/* define event type */  
EVENT_TYPE_DEFINE(measurement_event,            /* Unique event name. */
		  true,                         /* Event logged by default. */
		  log_measurement_event,        /* Function logging event data. */
		  &measurement_event_info);     /* Measurement event info */
