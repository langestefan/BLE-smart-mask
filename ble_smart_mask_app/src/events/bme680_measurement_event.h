/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _BME680_MEASUREMENT_EVENT_H_
#define _BME680_MEASUREMENT_EVENT_H_

/**
 * bme680_measurement_event. This event contains BME680 sensor data.
 *
 */

#include "event_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

struct bme680_measurement_event {
	struct event_header header;

	float bme680_temp;    /* Temperature */
	float bme680_pres;    /* Pressure */
	float bme680_hum;     /* Humidity */
};

EVENT_TYPE_DECLARE(bme680_measurement_event);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _BME680_MEASUREMENT_EVENT_H_ */
