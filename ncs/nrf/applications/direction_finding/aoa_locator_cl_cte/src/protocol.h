/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include <zephyr/types.h>
#include <bluetooth/dfe_data.h>
#include "dfe_local_config.h"
#include "if.h"

/** @brief Header added to data message send via UART
 */
#define PROTOCOL_HEAD				"+AoA"
/** @brief Length of a string buffer used to send data via UART
 */
#define PROTOCOL_STRING_BUFFER_SIZE		10240

/** @brief UARD data transmission structure */
struct protocol_data
{
	/** @brief Member to access UARD port
	 */
	struct if_data *uart;
	/** @brief Transmission data buffer
	 */
	char string_packet[PROTOCOL_STRING_BUFFER_SIZE];
};

/** @brief Initializes data transfer internals.
 *
 * @param[in] iface Pointer to interface data
 *
 * @retval 0 successful initialization
 * @retval -EINVAL if @p iface is NULL
 */
int protocol_initialization(struct if_data *iface);

/** @brief Puts mapped IQ samples into transfer buffer.
 *
 * The function stores IQ samples including information like: mapped antenna
 * index, time delay from the beginning of CTE reception (first sample).
 * Pay attention that antenna index 255 means sample taken during switch period.
 * Time data related with particular samples is an integer value.
 * The unit of the value is 125[us]. E.g. Time 4 means 4*125=500[us].
 *
 * @param[in] smapl_conf	Pointer to sampling configuration
 * @param[in] mapped_data	Pointer to IQ samples mapped to antennas
 */
int protocol_handling(const struct dfe_sampling_config *sampl_conf,
					  const struct dfe_mapped_packet *mapped_data);
#endif
