/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#ifndef _TRIGGER_MEASUREMENT_EVENT_H_
#define _TRIGGER_MEASUREMENT_EVENT_H_

/**
 * @brief Trigger Measurement Event
 *
 */

#include "event_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Event datafields. Trigger measurement event will not contain any data */
struct trigger_measurement_event {
	struct event_header header;
	int8_t init_value1;
};

EVENT_TYPE_DECLARE(trigger_measurement_event);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _TRIGGER_MEASUREMENT_EVENT_H_ */
