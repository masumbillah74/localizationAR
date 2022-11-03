/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#ifndef SRC_DFE_SAMPLES_DATA_H_
#define SRC_DFE_SAMPLES_DATA_H_

#include <stdint.h>
#include <bluetooth/dfe_data.h>

/** @brief IQ samples package header structure
 */
struct dfe_header {
	uint32_t length;
	uint32_t frequency;
} __attribute__((packed));

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
} __attribute__((packed));

/* Max length of SWITH PERIOD supported by our radio is 8us.
 * Smallest samples spacing is 125ns.
 * Max total number of gathered samples is 32 (that includes only sampling slots)
 */
#define DF_SAMPLES_COUNT (32)

/** @brief IQ samples collected for single antenna data structure
 *
 */
struct dfe_samples {
	union dfe_iq_f data[DFE_SAMPLES_PER_SLOT_NUM];
	uint8_t samples_num;
	uint8_t antenna_id;
} __attribute__((packed));

/** @brief IQ samples collected during reference period
 *
 * This structure differs from @see dfe_samples by size of data array.
 * Number of samples in reference period is bigger than number of samples
 * for single antenna in switching period.
 */
struct dfe_ref_samples {
	union dfe_iq_f data[DFE_REF_SAMPLES_NUM];
	uint8_t samples_num;
	uint8_t antenna_id;
} __attribute__((packed));


/* Max length of CTE is 160us. With removed guard period(4us) and reference period(8us)
 * we have 148us. Smallest reasonable antenna switching period is 2us.
 * That gives us up to 74 samples set per antenna.
 */
#define DF_MAX_EFFECTIVE_ANT_COUNT (32)
/** @brief Single DFE IQ samples mapped to antennas
 *
 * The structure holds data for a single DFE run.
 * It consists of a header, reference period IQ samples and
 * antenna switching period IQ samples.
 */
struct dfe_mapped_packet {
	struct dfe_header header;
	struct dfe_ref_samples ref_data;
	struct dfe_samples sampl_data[DFE_TOTAL_SLOTS_NUM];
} __attribute__((packed));

#endif /* SRC_DFE_SAMPLES_DATA_H_ */
