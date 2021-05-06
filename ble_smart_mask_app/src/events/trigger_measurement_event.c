/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include "trigger_measurement_event.h"
#include <stdio.h>


static int log_trigger_measurement_event(const struct event_header *eh, char *buf,
			    size_t buf_len)
{
	struct trigger_measurement_event *event = cast_trigger_measurement_event(eh);

	return snprintf(buf, buf_len, "init_val_1=%d", event->init_value1);
}

/* define info for profiling event */
EVENT_INFO_DEFINE(trigger_measurement_event,
		  NULL,
		  NULL,
		  NULL);

/* define event type */  
EVENT_TYPE_DEFINE(trigger_measurement_event,          /* Unique event name. */
		  true,                               /* Event logged by default. */
		  log_trigger_measurement_event,      /* Function logging event data. */
		  &trigger_measurement_event_info);   /* Measurement event info */
