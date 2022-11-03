/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <assert.h>
#include <string.h>

#include <kernel.h>
#include <zephyr/types.h>
#include <sys/printk.h>
#include <bluetooth/dfe_data.h>

#include "if.h"
#include "protocol.h"
#include "dfe_local_config.h"
#include "ble.h"

/** @brief Number of ms to wait for a data before printing no data note
 */
#define WAIT_FOR_DATA_BEFORE_PRINT (1000)

/** @brief Queue defined by BLE Controller to provide IQ samples data
 */
extern struct k_msgq df_packet_msgq;

/** @brief Main function of the example.
 *
 * The function is responsible for:
 * - initialization of UART output
 * - initialization of Direction Finding in Bluetooth stack
 * - initialization of Bluetooth stack
 * - receive DFE data from Bluetooth controller
 * - mapping received data to antenna numbers
 * - forwarding data by UART
 *
 * Following steps: data receive, mapping and their forwarding
 * is done in never ending loop.
 */
void main(void)
{
	printk("Starting AoA Locator CL!\r\n");
	/* initialize UART interface to provide I/Q samples */
	struct if_data* iface = if_initialization();

	if (iface == NULL) {
		printk("Locator stopped!\r\n");
		return;
	}

	int err;

	err = protocol_initialization(iface);
	if (err) {
		printk("Locator stopped!\r\n");
		return;
	}

	const struct dfe_sampling_config* sampl_conf = NULL;
	const struct dfe_antenna_config* ant_conf = NULL;
	const struct dfe_ant_gpio* ant_gpio = NULL;
	u8_t ant_gpio_len = 0;

	sampl_conf = dfe_get_sampling_config();
	ant_conf = dfe_get_antenna_config();
	ant_gpio_len = dfe_get_ant_gpios_config_len();
	ant_gpio = dfe_get_ant_gpios_config();

	assert(sampl_conf != NULL);
	assert(ant_conf != NULL);
	assert(ant_gpio != NULL);
	assert(ant_gpio_len != 0);

	printk("Initialize DFE\r\n");
	err = dfe_init(sampl_conf, ant_conf, ant_gpio, ant_gpio_len);
	if (err) {
		printk("Locator stopped!\r\n");
		return;
	}

	printk("Initialize Bluetooth\r\n");
	ble_initialization();

	while(1)
	{
		static struct dfe_packet df_data_packet;
		static struct dfe_mapped_packet df_data_mapped;

		memset(&df_data_packet, 0, sizeof(df_data_packet));
		memset(&df_data_mapped, 0, sizeof(df_data_mapped));
		k_msgq_get(&df_packet_msgq, &df_data_packet, K_MSEC(WAIT_FOR_DATA_BEFORE_PRINT));
		if (df_data_packet.hdr.length != 0) {
			printk("\r\nData arrived...\r\n");

			dfe_map_iq_samples_to_antennas(&df_data_mapped,
						      &df_data_packet,
						      sampl_conf, ant_conf);
			err = protocol_handling(sampl_conf, &df_data_mapped);
			if (err) {
				printk("Error in protocol handling!\r\n");
				printk("Locator stopped!\r\n");
				return;
			}
		}
		else
		{
			printk("\r\nNo data received.");
		}
		k_sleep(K_MSEC(CONFIG_AOA_LOCATOR_DATA_SEND_WAIT_MS));
	}
}
