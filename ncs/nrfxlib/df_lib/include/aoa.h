/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#ifndef __AOA_H
#define __AOA_H

#include "zephyr/types.h"
#include "dfe_samples_data.h"

/* Error codes */
/** The internal error of the library */
#define AOA_E_INT_ERR (__ELASTERROR + 1)
/** Too many samples provided, the library is not able to store them during
 * evaluation. */
#define AOA_E_NO_MEM (AOA_E_INT_ERR + 1)
/* Error codes end */

#define K_NSEC(ns)	(ns)

struct df_packet;

/** @brief Interface to externally provided interfaces e.g. system calls
 */
struct aoa_system_interface
{
	s64_t (*uptime_get)(void);
};

/** @brief AOA evaluation results structure
 */
struct aoa_result_data
{
	float elevation;
	float azimuth;
};

/** @brief AOA results package structure
 *
 * This data hold raw and filtered results.
 * Also there is available frequency used to provide samples.
 */
struct aoa_results
{
	uint16_t frequency;
	struct aoa_result_data raw_result;
	struct aoa_result_data filtered_result;
};

/** @brief AoA algorithm configuration structure
 */
struct aoa_configuration
{
	uint8_t matrix_size;
	uint8_t sampling_slots_num;
	uint8_t reference_period;
	uint8_t ant_switch_spacing;		//!< switch time in us [default 2us]
	uint16_t sample_spacing_ref;	//!< reference period sampling time [default 250ns]
	uint16_t sample_spacing;		//!< slot period sampling time [default 250ns]
	uint16_t slot_samples_num;
	uint32_t frequency;
	float array_distance;
};

/** @brief Initialize the angle of arrival evaluation library.
 *
 * The function is responsible for initialization of internals of angle of
 * arrival evaluation library. It must be called before run the evaluation procedure.
 *
 * @param[in]  sys_iface  Pointer to structure that provides access to system
 * 			  calls required by the library.
 * @param[in]  config Pointer to algorithm configuration data.
 * @param[out] handle     Pointer to memory where to store opaque pointer to
 * 			  handle to initialized algorithm.
 */
int aoa_initialize(const struct aoa_system_interface *sys_iface,
		   const struct aoa_configuration* config, void **handle);

/** @brief Function evaluates angle of arrival for provided data.
 *
 * The function is responsible for evaluation angle of arrival (azimuth and
 * elevation angles) of a beacon from provided data. Pay attention that
 * provided I/Q samples must be mapped to correct antennas used to provide
 * particular samples.
 *
 * @note The evaluation expects fixed antennas matrix geometry.
 * 	 Currently it is square matrix of antennas where:
 * 	 - antennas are placed on edges
 * 	 - there are no antennas in the center
 * 	 - total number of antennas is 12
 * 	 - distance between consecutive antennas is 5[cm]
 *
 * @param[in]  handle		Opaque pointer provided by aoa_initialize function.
 * @param[in]  df_mapped_data	Pointer to data structure that holds I/Q samples mapped
 * 				to antennas the samples were gathered with.
 * @param[out] results		Pointer to data structure where evaluation results will
 * 		 		be stored.
 *
 * @retval 0			If the evaluation was successful.
 * @retval -EINVAL		If one of arguments is NULL; handle is invalid; provided
 * 						I/Q data length is zero.
 * @retval -AOA_INT_ERR If there was an internal library error. That means
 * 						the library could not provide valid results.
 * @retval -AOA_NO_MEM	To many samples provided
 */
int aoa_handling(void *handle, struct dfe_mapped_packet *df_mapped_data,
		 struct aoa_results *results);
#endif
