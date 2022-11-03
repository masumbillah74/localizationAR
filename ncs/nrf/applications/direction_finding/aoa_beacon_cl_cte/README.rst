.. _bluetooth-aoa-beacon-connectionless-cte:

Bluetooth: AoA beacon with connectionless CTE
#############################################

The Angle of Arrival (AoA) beacon with connectionless Constant Tone Extension (CTE) sample provides a reference implementation of an AoA beacon.

Overview
********

The beacon uses Constant Tone Extension (CTE) in addition to regular advertising packets.
It does not allow to establish a connection.
The application uses a fixed MAC address that is expected by :ref:`AoA locator samples <bluetooth-aoa-Locator-conectionless-cte>`.

Requirements
************

A Nordic board with Bluetooth LE 5.1 support:

   * nRF52833 Development Kit board (PCA10100)

Building and running
********************

.. code-block:: console

   mkdir build
   cd build
   cmake -DBOARD=nrf52811_pca10068 ..
   make
   make flash

KConfig
=======

The KConfig of the sample application consists of two parts:

 * General Bluetooth configuration to enable advertising.
 * Direction finding configuration that enables the direction finding subsystem and enables transmission of CTE.


Bluetooth initialization
========================

The application uses Bluetooth advertising to broadcast CTE.
The stack is configured to use a fixed MAC address.
This means that if you use more than one beacon in the same environment, then they are going to interfere with each other.
You can configure the advertising interval using the :c:macro:`BT_ADV_INTERVAL` macro.

Direction Finding Extension
===========================

The Direction Finding Extension (DFE) is responsible for broadcasting of Constant Tone Extension.
DFE is a functionality implemented in Nordic's radio and provided by MCUs that have Bluetooth 5.1 implemented.
To enable the DFE functionality, you must enable the direction finding subsystem in the Zephyr's Bluetooth Controller: ``CONFIG_BT_CTLR_DF_SUBSYSTEM=y``.
To enable transmission of CTE at the end of an advertising packet, set the following configuration: ``CONFIG_BT_CTLR_DFE_TX=y``.

The sample runs CTE in a connectionless configuration.
That means, the application uses advertising packets to broadcast CTE.
The use of connectionless configuration also implies a transmission of 250 kHz constant tone wave.
This is caused by the use of Bluetooth 1 Mbps PHY in the connectionless transmission.

Radio configuration
-------------------

To start a CTE transmission, the radio must be correctly configured.
There is a number of registers that control DFE in the radio.
In case of the beacon, which is a CTE broadcaster, the following registers are in use:

	* ``CTEINLINECONF`` controls if CTE inline configuration is enabled (not supported by the Bluetooth stack yet).
	* ``DFEMODE`` controls the mode of the DFE.
	* ``DFECTRL1`` provides various configuration for direction finding.

Since there is no support for CTE inline functionality in the Bluetooth Controller, the functionality is disabled implicitly: ``CTEINLINECONF.CTEINLINECTRLEN`` is set to zero (disabled).

The only supported mode for direction finding is Angle of Arrival (AoA) and because of that, ``DFEMODE.DFEOPMODE`` is set to 3 (direction finding mode set to AoA).
To set the appropriate mode, use the :cpp:func:`dfe_set_mode` function.

To be able to transmit CTE, you must set its length, which is provided to ``DFECTRL1.NUMBEROF8US``.
A valid range of the number of 8 us is 2-20.
Currently, due to a known issue, the max value is 10 (the issue is under investigation).
To set CTE length, use the :cpp:func:`dfe_set_duration` function.
The radio is configured in :cpp:func:`dfe_init()` function.

UART Output transmission
========================

Sample software uses UART port as a console output.
User can check if application is running there or see information about error if occurs.

UART settings
-------------
	* Baud rate 115200
	* Data bits 8
	* Stop bits 1
	* Parity  None
	* Flow Control Off

