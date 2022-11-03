/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#ifndef SRC_DFE_SAMPLES_DATA_H_
#define SRC_DFE_SAMPLES_DATA_H_

#include <stdint.h>

/** @brief IQ samples package header structure
 */
struct dfe_header {
	uint32_t length;
	uint32_t frequency;
};

/** @brief IQ sample data structure
 *
 * The data are stored as a union.
 * Second member data is an array that is a helper used by math ARM functions.
 */
union dfe_iq_f {
	struct {
		float i; //!< 12bit
		float q; //!< 12bit
	};
	float data[2];
};

/** @brief IQ samples collected for single antenna data structure
 *
 */
/** @brief IQ samples collected for single antenna data structure
 *
 */
struct dfe_samples {
	uint8_t samples_num;					//!< number of samples in a data array
	uint8_t antenna_id;						//!< index of antenna used to collect samples
	union dfe_iq_f *data;					//!< IQ samples
} __attribute__((packed));

/** @brief This is a fixed value for reference period duration 8us and min sampling
 * spacing 125ns.
 */
#define DF_REF_SAMPLES_COUNT (64)

/** @brief IQ samples collected during reference period
 *
 * This structure differs from @see dfe_samples by size of data array.
 * Number of samples in reference period is bigger than number of samples
 * for single antenna in switching period.
 */
struct dfe_ref_samples {
	uint8_t samples_num;
	uint8_t antenna_id;
	union dfe_iq_f data[DF_REF_SAMPLES_COUNT];
} __attribute__((packed));

/** @brief Single DFE IQ samples mapped to antennas
 *
 * The structure holds data for a single DFE run.
 * It consists of a header, reference period IQ samples and
 * antenna switching period IQ samples.
 */
struct dfe_mapped_packet {
	struct dfe_header header;
	struct dfe_ref_samples ref_data;
	struct dfe_samples *sampl_data;
} __attribute__((packed));

#endif /* SRC_DFE_SAMPLES_DATA_H_ */
