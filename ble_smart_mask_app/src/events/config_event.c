/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include "config_event.h"
#include <stdio.h>

/* logging function for event */
static int log_config_event(const struct event_header *eh, char *buf,
			    size_t buf_len)
{
	struct config_event *event = cast_config_event(eh);

	return snprintf(buf, buf_len, "init_val_1=%d", event->init_value1);
}

/* define info for profiling event */
EVENT_INFO_DEFINE(config_event,
		  NULL,
		  NULL,
		  NULL);

/* define event type */  
EVENT_TYPE_DEFINE(config_event,           /* Unique event name. */
		  true,                   /* Event logged by default. */
		  log_config_event,       /* Function logging event data. */
		  &config_event_info);    /* Measurement event info */
