.. _bluetooth-aoa-Locator-conectionless-cte:

Bluetooth: AoA locator with connectionless CTE
##############################################

The Angle of Arrival (AoA) locator with connectionless Constant Tone Extension (CTE) sample provides a reference implementation of an AoA locator.

Overview
********

The locator application uses Constant Tone Extension (CTE) added to regular advertising packets to gather IQ samples.
The samples are forwarded to UART output.
The application does not allow to establish a connection.
The application uses fixed MAC address to get IQ samples only from a particular beacon.

Requirements
************

A Nordic board with Bluetooth LE 5.1 support:

   * nRF52833 Development Kit board (PCA10100)

Building and running
********************

.. code-block:: console
	mkdir build
	cd build
	cmake -DBOARD=nrf52833_pca10100 ..
	make
	make flash

KConfig
=======

The application provides the following custom configuration options:

	* ``AOA_LOCATOR_UART_PORT`` defines the name of the UART port use to forward IQ samples.
	* ``AOA_LOCATOR_DATA_SEND_WAIT_MS`` wait duration after send of data by UART port.

prj.conf
========

The application configuration file consists of the following parts:

   * General kernel configuration that sets the stacks and heap.
   * General Bluetooth configuration that enables scanning for incoming advertising.
   * UART configuration that enables driver and setup interrupts.
   * Direction finding configuration that enables: 
	* CONFIG_BT_CTLR_DF_SUBSYSTEM enables Direction Finding Bluetooth subsystem
	* CONFIG_BT_CTLR_DFE_RX enables receive of CTE(DFE) extension by Bluetooth stack
	* CONFIG_BT_CTLR_DFE_NUMBER_OF_8US sets duration of CTE
	* CONFIG_BT_CTLR_DFE_SWITCH_SPACING_2US set antenna switching time to 2us (other values are possible)
	* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_1US set 1us for samples spacing when antenna switching started
	* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_REF_1US set 1us for samples spacing in reference period

Other possible configurations for sample spacing:
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_4US
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_2US
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_1US
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_500NS
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_250NS
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_125NS

Other possbile configurations for reference samples spacing:
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_REF_4US
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_REF_2US
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_REF_1US
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_REF_500NS
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_REF_250NS
* CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_REF_125NS

To enable oversampling one may use following configuarion entries:
CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_250NS=y
CONFIG_BT_CTLR_DFE_SAMPLE_SPACING_REF_250NS=y


Bluetooth initialization
========================

The application uses Bluetooth scanning to receive and sample CTE.

The stack is configured to use a fixed MAC address.
That is required to avoid corrupted IQ samples gathered when radio receives an advertising packet from a device that does not broadcast CTE.
The use of a fixed MAC address means that if you use more than one beacon in the same environment, then they will interfere with one another.

Scanning timings are set to the following values:

	* Scanning interval: 0x20, which equals to 20 ms.
	* Scanning window: 0x20, which equals to 20 ms.

Direction Finding Extension
===========================

The Direction Finding Extension (DFE) is responsible for receiving and sampling of Constant Tone Extension (CTE).
DFE is a functionality implemented in Nordic's radio and provided by MCUs that have Bluetooth 5.1 implemented.
To enable DFE functionality, you must enable the direction finding subsystem in Bluetooth Controller: ``CONFIG_BT_CTLR_DF_SUBSYSTEM=y``.
To enable receiving and sampling of CTE at the end of an incoming advertising packet, set the following configuration: ``CONFIG_BT_CTLR_DFE_RX=y``.

The sample receives and samples CTE in a connectionless configuration.
That means, the application uses broadcaster advertising packets that have added CTE after CRC.
The use of connectionless configuration also implies that the received CTE has a 250 kHz constant tone wave.
This is caused by the use of Bluetooth 1 Mbps PHY in the connectionless transmission.

Radio configuration
-------------------

To start a CTE transmission, the radio must be correctly configured.
There is a number of registers that control DFE in the radio.
In case of the locator, which is a CTE receiver, the following registers are in use:

   * ``CTEINLINECONF`` controls if CTE inline configuration is enabled (not supported by the Bluetooth stack yet).
   * ``DFEMODE`` controls the mode of the DFE.
   * ``DFECTRL1`` provides various configuration for direction finding.
   * ``DFECTRL2`` provides the capability to set offsets for direction finding.

CTE inline configuration
~~~~~~~~~~~~~~~~~~~~~~~~
Since there is no support for CTE inline functionality in the Bluetooth Controller, this functionality is disabled implicitly: ``CTEINLINECONF.CTEINLINECTRLEN`` is set to zero (disabled).

DFE Mode
~~~~~~~~
The only supported mode for direction finding is Angle of Arrival (AoA) and because of that, ``DFEMODE.DFEOPMODE`` is set to 3 (direction finding mode set to AoA).
To set the appropriate mode, use the :cpp:func:`dfe_set_mode` function.

DFE Duration
~~~~~~~~~~~~
To be able to transmit CTE, you must set its length, which is provided to ``DFECTRL1.NUMBEROF8US``.
A valid range of the number of 8 us is 2-20.
Currently, due to a known issue, the max value is 10 (the issue is under investigation).
To set CTE length, use the :cpp:func:`dfe_set_duration` function.

CTE start point
~~~~~~~~~~~~~~~
CTE may be added to a Bluetooth packet in two places:
   * after the CRC,
   * during packet payload.

The start point of a CTE broadcast must be set to the same value in both the beacon and the locator.

Currently, the Bluetooth implementation supports a transmission or a reception of CTE after the CRC end.
This value should remain set as ``RADIO_DFECTRL1_DFEINEXTENSION_CRC`` and should not be changed.
To set the CTE start point, use the :cpp:func:`dfe_set_start_point` function.

Sampling with a CRC error
~~~~~~~~~~~~~~~~~~~~~~~~~
IQ sampling can be processed even if a CRC error is detected.
However, in such case, IQ samples might also be corrupted.
Because of that this setting is set to false.
It is strongly advised to not change that setting.
To set the sampling on CRC error, use the :cpp:func:`dfe_set_sample_on_crc_error` function.

AoA/AoD trigger source
~~~~~~~~~~~~~~~~~~~~~~
The current implementation of direction finding in the Bluetooth stack supports the start of AoA procedure by ``TASKS_DFESTART`` only.
When this feature is implemented, it will be possible to use some other signal to start the procedure.
That means that right now this value should not be changed.
To set the trigger source, use the :cpp:func:`dfe_set_trig_dfe_start_task_only` function.

Sampling type
~~~~~~~~~~~~~
The radio is able to provide two kinds of samples:
   * complex samples (rectangural) I/Q,
   * complex samples (polar) as magnitude and phase.

I/Q samples are 12 bits in size, including the sign bit.
The sign is extended to 16 bits.

Polar samples are:
	* magnitude - 13-bit unsigned value given as magnitude=K*sqrt(I^2+Q^2), where K≈1.646756 is the Cordic scaling factor.
	* phase - 9-bit including the sign bit, sign extended to 16 bits.

The application is based on I/Q (rectangular) complex samples.
The setting should not be changed to provide correct values on the output.

To set the type of provided samples, use the :cpp:func:`dfe_set_sampling_type` function.
The values that can be provided to the function are: ``RADIO_DFECTRL1_SAMPLETYPE_IQ`` and ``RADIO_DFECTRL1_SAMPLETYPE_MagPhase``.

Backoff gain
~~~~~~~~~~~~
The radio can change the lower gain when starting to receive the CTE.
The gain is lowered by a number of steps (by 15 maximum).
The application does not change the gain, so the backoff value is set to zero.
To set the backoff gain, use the :cpp:func:`dfe_set_backoff_gain` function.

Antenna GPIOs
~~~~~~~~~~~~~
To run the sampling, an antenna matrix must be attached to the DK board.
The radio can handle up to eight GPIOs to switch the antennas.
The antennas are switched by setting the state of particular GPIOs to ones and zeros.
That means that the radio can switch up to 2^8 different antennas.

The application is implemented to work with an antenna matrix provided by Nordic.
There are 12 antennas available in the matrix.
The application uses only the first four GPIOs (of 8 available).
There is no restriction which GPIO must or must not be used for antenna switching.

The sample uses the following GPIOs to handle the antenna matrix: (P0.03,P0.04,P0.28,P0.29).
To set the antenna GPIOs, use an array of the following structures::

struct dfe_ant_gpio {
	u8_t idx;
	u8_t gpio_num;
};


where:
	* idx is an index of ``PSEL.DFEGPIO``,
	* gpio_num is a port/pin number of the GPIO to be set: bit 0-4 is the pin number (max 32), bit 5 is the port number.

The sample uses the following GPIO array (all GPIOs from port 0)::

const static struct dfe_ant_gpio g_gpio_conf[4] = {
	{0, 3}, {1,4}, {2, 28}, {3,29}
};

To set the antenna GPIO patterns, use the :cpp:func:`dfe_set_ant_gpios` function.

Antenna patterns
~~~~~~~~~~~~~~~~
The antenna switch pattern is a binary number whose each bit is applied to a particular antenna GPIO pin.
For example, the pattern 0x3 means that antenna GPIOs at index 0,1,2 will be set, and the 4th is left unset.

This also means that, for example, when using four GPIOs, the patterns cannot be greater than 15.

The radio can store up to 40 antenna switch patterns.

At least three patterns must be provided:

   * SWITCHPATTERN[0] is used in idle mode,
   * SWITCHPATTERN[1] is used in guard and reference period,
   * SWITCHPATTERN[2...] are used in switch-sampling period (at least one must be provided).

If the number of switch-sample periods is greater than the number of stored switch patterns, then the radio loops back to the pattern used after the reference period (SWITCHPATTERN[2]).

The following table presents the patterns that you can use to switch antennas on the Nordic-provided antenna matrix:

+--------+--------------+
|Antenna | ANT_SEL[3:0] |
+--------+--------------+
| ANT_12 |  0 (0000)    |
| ANT_10 |  1 (0001)    |
| ANT_11 |  2 (0010)    |
| ----   |  3 (0011)    |
+ -------+--------------+
| ANT_3  |  4 (0100)    |
| ANT_1  |  5 (0101)    |
| ANT_2  |  6 (0110)    |
| ----   |  7 (0111)    |
+--------+--------------+
| ANT_6  |  8 (1000)    |
| ANT_4  |  9 (1001)    |
| ANT_5  | 10 (1010)    |
| ----   | 11 (1011)    |
+--------+--------------+
| ANT_9  | 12 (1100)    |
| ANT_7  | 13 (1101)    |
| ANT_8  | 14 (1110)    |
| ----   | 15 (1111)    |
+--------+--------------+

The application uses two arrays to set antennas:
	* ant_gpio_pattern that holds patterns that enable particular antennas (index of pattern is a number of the antenna on the board),
	* antennae_switch_idx that holds indices of antennas to be stored in the SWITCHPATTERN register (those indices correspond to the ant_gpio_pattern indices).

The antennae_switch_idx array stores switch-sampling antennas only.

The SWITCHPATTERN[0] is stored in idle_ant_idx.
The SWITCHPATTERN[1] is stored in ref_ant_idx.

The sequence in which the patterns are applied is the following: idle_ant_idx, ref_ant_idx, antennae_switch_idx.

To set the antenna patterns, use the :cpp:func:`dfe_set_ant_gpio_patterns` function.

Antenna switch spacing
~~~~~~~~~~~~~~~~~~~~~~
After a reference period, the antenna switch period begins.
The duration of every switch-sample period depends on the setting provided.
The allowed values are:

	* RADIO_DFECTRL1_TSWITCHSPACING_4us (1UL)
	* RADIO_DFECTRL1_TSWITCHSPACING_2us (2UL)
	* RADIO_DFECTRL1_TSWITCHSPACING_1us (3UL) (This value is out of Bluetooth specification. It is a Nordic extension and has not been tested with regards to provided samples and their usability).

Every switch-sample period is divided into two parts: swich slot and sample slot.
The number of switch-sample periods depends on DFE duration (number of 8 us).

For example, in the following setup:
* the guard period lasts 4[us],
* the reference period lasts 8[us],
* the DFE duration is 5 -> 5*8[us]=40[us],
the time for antenna switching is 40 - 12 = 28[us].

The, if antenna switch spacing is set to 2[us], then there are 14 antenna switches.

If 11 antennas are set in the SWITCHPATTERN register, then after the 11th antenna, samples from SWITCHPATTERN[2],SWITCHPATTERNS[3],SWITCHPATTERNS[4] will be received (because of loopback).

To set switch spacing, use the :cpp:func:`dfe_set_ant_switch_spacing` function.

Switch spacing offset
~~~~~~~~~~~~~~~~~~~~~
The radio allows for some fine-tuning when the switching of antennas starts.
That offset is applied before the guard period starts (before the first switch from idle state).
The value of the offset is a 12-bit signed number of 16 M cycles (number of 62.5[ns]).
The sample does not use this setting.

To set switch spacing, use the :cpp:func:`dfe_set_switch_offset` function.

Reference samples spacing and switching period sample spacing
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
During the reference period, samples are gathered according to the reference samples spacing value.
The allowed reference sample spacing values are:

   * RADIO_DFECTRL1_TSAMPLESPACINGREF_4us (1UL)
   * RADIO_DFECTRL1_TSAMPLESPACINGREF_2us (2UL)
   * RADIO_DFECTRL1_TSAMPLESPACINGREF_1us (3UL)
   * RADIO_DFECTRL1_TSAMPLESPACINGREF_500ns (4UL)
   * RADIO_DFECTRL1_TSAMPLESPACINGREF_250ns (5UL)
   * RADIO_DFECTRL1_TSAMPLESPACINGREF_125ns (6UL)

Allowed switch period sample spacing values are:

   * RADIO_DFECTRL1_TSAMPLESPACING_4us (1UL)
   * RADIO_DFECTRL1_TSAMPLESPACING_2us (2UL)
   * RADIO_DFECTRL1_TSAMPLESPACING_1us (3UL)
   * RADIO_DFECTRL1_TSAMPLESPACING_500ns (4UL)
   * RADIO_DFECTRL1_TSAMPLESPACING_250ns (5UL)
   * RADIO_DFECTRL1_TSAMPLESPACING_125ns (6UL)

According to Bluetooth specification, there is only one sample spacing allowed - 1[us].
However, Nordic's radio provides additional settings.

One of these settings is the capability to use oversampling - spacing values that are lower than 1[us]:

This is the only difference between the two configurations enabled by configuration options: ``AOA_LOCATOR_REGULAR_CTE`` and ``AOA_LOCATOR_OVERSAMPLING_CTE``:
   * In case of ``AOA_LOCATOR_REGULAR_CTE``, the 1[us] sample spacing is used (for both reference and switch periods).
   * In case of ``AOA_LOCATOR_OVERSAMPLING_CTE`` the 250[ns] sample spacing is used. (for both reference and switch periods).

Note that the radio also allows to set different sample spacing for the reference and switch periods.

To set sample spacing for the reference period, use the :cpp:func:`dfe_set_sampling_spacing_ref` function.
To set sample spacing for the switching period use the :cpp:func:`dfe_set_sample_spacing` function.

Sampling in reference and switching periods
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Keep in mind the following information regarding sampling periods.

Sampling in the reference period starts at the beginning of the period.
This means that the last sample in the reference period is taken "sample spacing time" before the end of the period.
For example, if reference sample spacing is set to 500[ns], then the last sample is taken 500 ns before the end of the reference period (or 7,5[us] after the start of the period).

Sampling in the switching period does not start at the beginning of the period.
It starts after a delay whose value is half of the switch spacing time.
For example, if switch spacing is 2[us], then the first sample arrives after a delay of 1[us].

So the delay between the last reference period sample and the first switch period sample is provided by the formula: TSAMPLESPACINGREF + 1/2 * TSWITCHSPACING.

Examples:

   * For: TSAMPLESPACINGREF=1us and TSWITCHSPACING=4us, the delay equals 1 + 4/2 = 3 us
   * For: TSAMPLESPACINGREF=1us and TSWITCHSPACING=2us, the delay equals 1 + 2/2 = 2 us
   * For: TSAMPLESPACINGREF=0.5us and TSWITCHSPACING=2us, the delay equals 0.5 + 2/2 = 1.5 us

Take this delay into account when evaluating the phase and time difference between samples from the reference period and the switching period.

The radio does not stop sampling in switching slots.
This has a drawback when the time between samples is shorter than switch spacing.
In such case, the samples are taken during the switch period.
These samples might be corruped because the radio might not be in a stable state to gather valid values.

The samples are taken during the switch period because the radio starts sampling and collects samples until the end of DFE (CTE) duration.
For example, if switch spacing is 2[us] (so a switch slot (SW) is 1[us] and a sampling slot (SA) is 1[us]), a sampling slot is 250[ns], then the following table shows when the samples are taken ("X" means a sample).

+-------|-------+-------|-------+-------|-------+-------|-------+
   SW   |  SA   |   SW  |  SA   |   SW  |  SA   |   SW  |  SA   |
+-------|-------+-------|-------+-------|-------+-------|-------+
         X X X X X X X X X X X X X X X X X X X X X X X X X X X X
+-------|-------+-------|-------+-------|-------+-------|-------+

After the end of the first SW slot, sampling starts and continues up to the end of the DFE (CTE) duration.

The conclusion is that sampling during the switch slot has implications.
Samples must be discarded, but a sample does not provide a time when it was taken.
Therefore, software must be able to evaluate timings of samples using the provided settings (switch and sample spacings), taking into account when sampling starts.

In case of the reference period, every sample is valid.
In case of the switching period, it is more complicated.
First of all, the algorithm must check if the spacing between samples is shorter than the antennas' switch spacing.
If that is true, then half of the samples should be discarded.

A similar compilation applies to mapping of samples to antennas.
This must also be done by software because radio does not provide such information.
The solution is based on switch spacing, sample spacing, length of DFE (CTE), and the antennas' switch pattern.
Length of DFE (CTE) with antenna spacing provides a number of effective antennas used.
Sample spacing and switch spacing allows to find out which antenna was used to provide a particular sample.
Note that the first antenna provides only a half of samples taken in a single switch-sample period.

Implementation of samples to antennas mapping (including marking "255" discarded samples) can be found in :cpp:func:`df_map_iq_samples_to_antennas`.

Sampling offset
~~~~~~~~~~~~~~~
Similarly to switching, the start of sampling in the switch-sample period can be also fine tuned by setting sample offset.

The value of the offset is a 12-bit signed number of 16 M cycles (number of 62.5[ns]).

This setting can delay the sampling or make the sampling start faster (for example, if switches on the antennas' board are very slow).
Note that this delay must be added to the mapping of samples to time and antennas.

It has not been added to this evaluation of samples to antennas mapping.

The application sets this value to 1 (62.5ns) to move the start of sampling a little bit.
Bluetooth 5.1 specification states that samples should be taken 125 ns after the start of a sampling slot and 125 ns before the end of a sampling slot.
To set sampling spacing, use the :cpp:func:`dfe_set_sample_offset` function.

The radio is configured in :cpp:func:`dfe_init()`.


UART settings
-------------
	* Baud rate 115200
	* Data bits 8
	* Stop bits 1
	* Parity  None
	* Flow Control Off

UART application protocol
-------------------------

There is a protocol used for transmission of data over UART. Below is a fragment of complete data frame but representing every field it may include.

DF_BEGIN
IQ:0,0,11,114,137
IQ:1,2,11,156,84
.
.
.
IQ:142,292,255,39,161
IQ:143,294,255,99,151
SW:2
RR:5
SS:5
FR:2402
ME:0
MA:0
KE:0
KA:0
DF_END

Each data frame begins with DF_BEGIN and ends with DF_END strings.
If one didn't receive DF_BEGIN then data frame is not complete. The same goes if there is no DF_END.

After DF_BEGIN there is a block of strings that begin of IQ samples. Number of IQ samples provided depends on DFE configuration (duration, reference sample spacing, sample spacing). In the example, there were 144 samples provided. Each row represents single IQ sample. 
Format is following e.g.: IQ:143,294,255,99,151
	* “IQ:” mandatory begin of IQ sample data.
	* “143” is a sample number (indexed from 0).
	* "294” is time as number of 125ns units. The sample was taken 294*125ns=40750ns after beginning of reference period.
	* “255” is an antenna index. This field may have a value in range 1 to 12. It is a antenna index. In case there is value 255, the sample was taken in antenna switching period and should be discarded from further evaluation.
	* “99” is a Q component value.
	* “151” is an I component value.

After IQ samples block there is configuration and angles block:
	* “SW:2” is an antenna switching time constant. "SW:" is mandatory beginnig of the record. Following number is a constant representing configuration used. It may have on of following values:
		* RADIO_DFECTRL1_TSWITCHSPACING_4us (1UL)
		* RADIO_DFECTRL1_TSWITCHSPACING_2us (2UL)
		* RADIO_DFECTRL1_TSWITCHSPACING_1us (3UL)
	* “RR:5” is a spacing of samples in reference period. "RR:" is mandatory beginnig of the record. Following number is a constant representing configuration used. It may have one of following values:
		* RADIO_DFECTRL1_TSAMPLESPACINGREF_4us (1UL)
		* RADIO_DFECTRL1_TSAMPLESPACINGREF_2us (2UL)
		* RADIO_DFECTRL1_TSAMPLESPACINGREF_1us (3UL)
		* RADIO_DFECTRL1_TSAMPLESPACINGREF_500ns (4UL)
		* RADIO_DFECTRL1_TSAMPLESPACINGREF_250ns (5UL)
		* RADIO_DFECTRL1_TSAMPLESPACINGREF_125ns (6UL)
	* “SS:5” is a spacing of samples during antenna swiching period. "SS:" is mandatory beginnig of the record. Following number is a constant representing configuration used. It may have on of following values:
		* RADIO_DFECTRL1_TSAMPLESPACING_4us (1UL)
		* RADIO_DFECTRL1_TSAMPLESPACING_2us (2UL)
		* RADIO_DFECTRL1_TSAMPLESPACING_1us (3UL)
		* RADIO_DFECTRL1_TSAMPLESPACING_500ns (4UL)
		* RADIO_DFECTRL1_TSAMPLESPACING_250ns (5UL)
		* RADIO_DFECTRL1_TSAMPLESPACING_125ns (6UL)
	* "FR:2402"  is a frequency that was used to collect IQ samples. "FR:" is mandatory beginnig of the record. Following number is a frequency value in MHz.
	* “ME:0” this entry if reserved for future use
	* “MA:0” this entry if reserved for future use
	* “KE:0” this entry if reserved for future use
	* “KA:0” this entry if reserved for future use

DFE data frame ends with “DFE_END” string.


