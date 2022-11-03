/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <errno.h>
#include <device.h>
#include <drivers/uart.h>

#include "if.h"

/** @brief Storage for internals of output interface handling functionality */
static struct if_data g_if;

/** @brief UART ISR handler.
 *
 * The function is responsible for a logging information if
 * UART is interrupted when TX is ready.
 *
 * @param[in] dev	UARD device
 */
static void if_uart_app_isr(struct device *dev);

/** @brief Send data via UART
 *
 * @param[in] buffer	Data to be send
 * @param[in] length	Size of memory in @p buffer
 */
static void uart_send(uint8_t *buffer, uint16_t length);

struct if_data *if_initialization(void)
{
	g_if.dev = device_get_binding(CONFIG_AOA_LOCATOR_UART_PORT);
	if (!g_if.dev) {
		printk("[UART] - Device not found or cannot be used\r\n");
		return NULL;
	}

	uart_irq_rx_disable(g_if.dev);
	uart_irq_tx_disable(g_if.dev);
	uart_irq_callback_set(g_if.dev, if_uart_app_isr);
	uart_irq_rx_enable(g_if.dev);

	g_if.send = uart_send;

	return &g_if;
}

static void if_uart_app_isr(struct device *dev)
{
	while (uart_irq_update(dev) && uart_irq_is_pending(dev))
	{
		if (!uart_irq_rx_ready(dev))
		{
			if (uart_irq_tx_ready(dev))
			{
				printk("[UART] - transmit ready");
			}
			else
			{
				printk("[UART] - spurious interrupt");
			}

			break;
		}
	}
}

static void uart_send(uint8_t *buffer, uint16_t length)
{
	size_t i = 0;

	for(i=0; i<length; i++)
	{
		uart_poll_out(g_if.dev, buffer[i]);
	}
}
