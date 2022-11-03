/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <sys/printk.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>

#include "ble.h"


int ble_initialization(void)
{
	struct bt_le_scan_param scan_param = {
		.type       = BT_HCI_LE_SCAN_PASSIVE,
		.filter_dup = BT_HCI_LE_SCAN_FILTER_DUP_DISABLE,
		.interval   = 0x0020,
		.window     = 0x0020,
	};
	int err;

	printk("[BT] Initialization started\r\n");

	err = bt_enable(NULL);
	if (err)
	{
		printk("[BT] Initialization failed (err %d)\r\n", err);
		return err;
	}

	printk("[BT] Starting scanning\r\n");
	err = bt_le_scan_start(&scan_param, NULL);
	if (err)
	{
		printk("[BT] Start scanning failed (err %d)\n", err);
		return err;
	}
	return 0;
}
