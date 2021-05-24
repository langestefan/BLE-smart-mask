#
# Copyright (c) 2019 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

cmake_minimum_required(VERSION 3.13.1)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project("BLE smart mask")

# Include application event headers
zephyr_library_include_directories(src/events)
zephyr_library_include_directories(src/modules)
zephyr_library_include_directories(configuration)

# Application sources
# NORDIC SDK APP START
target_sources(app PRIVATE src/main.c)

target_sources(app PRIVATE
		src/events/config_event.c
		src/events/sensor_packet_event.c
		src/events/bme680_measurement_event.c
		src/events/trigger_measurement_event.c
)

target_sources(app PRIVATE
		src/modules/bme680.c
		src/modules/sensor.c
#		src/modules/ble_bond.c # something is broken in ble_bond.c, stops advertising from starting
#		src/modules/settings_loader.c
)
# NORDIC SDK APP END
zephyr_library_include_directories(.)
