/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _MEASUREMENT_EVENT_H_
#define _MEASUREMENT_EVENT_H_

/**
 * Measurement Event. Submits sensor data. 
 *
 */

#include "event_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

struct measurement_event {
	struct event_header header;

	int8_t value1;    /* Temperature */
	int16_t value2;   /* Pressure */
	int32_t value3;   /* Humidity */
};

EVENT_TYPE_DECLARE(measurement_event);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _MEASUREMENT_EVENT_H_ */
