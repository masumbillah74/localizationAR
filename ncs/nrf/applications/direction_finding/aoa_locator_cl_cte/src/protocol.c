/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include <sys/printk.h>

#include "protocol.h"
#include "if.h"

#define SAMPLING_TIME_UNIT (125) //!< smallest possible time between samples [ns]

static struct protocol_data g_protocol_data;

static uint16_t protocol_convert_to_string(const struct dfe_sampling_config* sampl_conf,
					   const struct dfe_mapped_packet *mapped_data,
					   char *buffer, uint16_t length);

int protocol_initialization(struct if_data* iface)
{
	if (iface == NULL) {
		printk("[PROTOCOL] - iface is NULL, cannot initialize\r\n");
		return -EINVAL;
	}

	g_protocol_data.uart = iface;
	return 0;
}

int protocol_handling(const struct dfe_sampling_config *sampl_conf,
		      const struct dfe_mapped_packet *mapped_data)
{
	assert(sampl_conf != NULL);
	assert(mapped_data != NULL);
	uint16_t length = 0;

	length = protocol_convert_to_string(sampl_conf, mapped_data,
					    g_protocol_data.string_packet,
					    PROTOCOL_STRING_BUFFER_SIZE);
	g_protocol_data.uart->send(g_protocol_data.string_packet, length);

	return 0;
}

/** @brief Converts provided IQ samples into string
 *
 * The function stores provided IQ samples into a buffer.
 * Format of a stored data is fixed:
 * - header
 * - sampling settings
 * - not used fields for evaluated angles
 * - IQ samples
 * - footer
 *
 * @param[in]		sampl_config	Configuration of sampling
 * @param[in]		mapped_data	IQ	samples mapped to antennas
 * @param[in,out]	buffer			Memory to store string representation
 * @param[in] 		len				length of memory provided by @p buffer
 *
 * @return Number of characters stored in transmission buffer.
 */
static u16_t protocol_convert_to_string(const struct dfe_sampling_config* sampl_conf,
					   const struct dfe_mapped_packet *mapped_data,
					   char *buffer, uint16_t length)
{
	printk("DF_BEGIN\r\n");
	u16_t strlen = sprintf(buffer, "DF_BEGIN\r\n");

	strlen += sprintf(&buffer[strlen], "SW:%d\r\n", (int)sampl_conf->switch_spacing);
	strlen += sprintf(&buffer[strlen], "RR:%d\r\n", (int)sampl_conf->sample_spacing_ref);
	strlen += sprintf(&buffer[strlen], "SS:%d\r\n", (int)sampl_conf->sample_spacing);
	strlen += sprintf(&buffer[strlen], "FR:%d\r\n", (int)mapped_data->header.frequency);

	strlen += sprintf(&buffer[strlen], "ME:%d\r\n", (int)0);
	strlen += sprintf(&buffer[strlen], "MA:%d\r\n", (int)0);
	strlen += sprintf(&buffer[strlen], "KE:%d\r\n", (int)0);
	strlen += sprintf(&buffer[strlen], "KA:%d\r\n", (int)0);

	u16_t time_u = dfe_get_sample_spacing_ref_ns(sampl_conf->sample_spacing_ref) / SAMPLING_TIME_UNIT;
	u16_t ref_idx;

	for(ref_idx = 0; ref_idx < mapped_data->ref_data.samples_num; ++ref_idx)
	{
		strlen += sprintf(&buffer[strlen], "IQ:%d,%d,%d,%d,%d\r\n", ref_idx,
				time_u * ref_idx,
				 (int)mapped_data->ref_data.antenna_id,
				 (int)mapped_data->ref_data.data[ref_idx].q,
				 (int)mapped_data->ref_data.data[ref_idx].i);
	}
	/* compute delay  between last sample in reference period and first sample
	 * in antenna switching period.
	 */
	u16_t delay =  dfe_delay_before_first_sampl(sampl_conf) / SAMPLING_TIME_UNIT;
	delay += (time_u * (ref_idx-1));
	time_u = dfe_get_sample_spacing_ns(sampl_conf->sample_spacing) / SAMPLING_TIME_UNIT;

	for(u16_t idx=0; idx<mapped_data->header.length; ++idx)
	{
		const struct dfe_samples* sampl_data = &mapped_data->sampl_data[idx];

		for(u16_t jdx = 0; jdx < sampl_data->samples_num; ++jdx)
		{
			u16_t idx_offset = (sampl_data->samples_num * idx) + jdx;

			strlen += sprintf(&buffer[strlen], "IQ:%d,%d,%d,%d,%d\r\n", ref_idx + idx_offset,
					delay + (idx_offset) * time_u,
					 (int)sampl_data->antenna_id,
					 (int)sampl_data->data[jdx].q,
					 (int)sampl_data->data[jdx].i);
		}
	}

	strlen += sprintf(&buffer[strlen], "DF_END\r\n");

	return strlen;
}


