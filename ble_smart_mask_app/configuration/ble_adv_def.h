/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */
 
#include <zephyr.h>
#include <bluetooth/bluetooth.h>

static const struct bt_data ad_unbonded[] = {
      BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
      BT_DATA_BYTES(BT_DATA_UUID16_ALL,
                    0x0f, 0x18,          /* Battery Service */
      ),
};

static const struct bt_data ad_bonded[] = {
      BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
      BT_DATA_BYTES(BT_DATA_UUID16_ALL,
                    0x18, 0x0f,  /* Battery Service */
      ),
};

static const struct bt_data sd[] = {};