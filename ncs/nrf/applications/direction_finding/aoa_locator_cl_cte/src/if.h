/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#ifndef __IF_H
#define __IF_H

/** @brief Output buffer size
 */
#define IF_BUFFER_SIZE		2048

/* Zephyrs device structure forward declaration */
struct device;

/* @brief Output interface data structure
 */
struct if_data
{
	/** Pointer to device driver */
	struct device *dev;
	/** output transfer buffer */
	u8_t tx_buffer[IF_BUFFER_SIZE];
	/** Index of last stored byte in transfer buffer */
	u16_t tx_index;
	/** callback to send data */
	void (*send)(u8_t *, u16_t);
};

/* @brief Initializes output interface
 *
 * @return pointer to output interface structure instance
 */
struct if_data* if_initialization(void);

#endif
