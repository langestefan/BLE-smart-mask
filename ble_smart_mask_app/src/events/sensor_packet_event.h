/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _SENSOR_PACKET_EVENT_H_
#define _SENSOR_PACKET_EVENT_H_

/**
 * Sensor_packet_event. This event contains aggregated sensor data. 
 *
 */

#include "event_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

struct sensor_packet_event {
	struct event_header header;

	int8_t value1;    /* Temperature */
	int16_t value2;   /* Pressure */
	int32_t value3;   /* Humidity */
};

EVENT_TYPE_DECLARE(sensor_packet_event);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _SENSOR_PACKET_EVENT_H_ */
