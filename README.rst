.. _Indoor Localization using BLE 5.1:

Indoor Localization in AR view using BLE 5.1
#############################################

Hardware Requirements
************

- At least 2 Nordic boards with Bluetooth LE 5.1 support:
   * nRF52833 Development Kit boards (PCA10100)
   * Use one board as a locator and rest as beacons
- An antenna array:
   * Texas Instrument BoostXL antenna array
   * Connect the antenna array to the locator
   * Read ncs/nrf/applications/direction_finding/aoa_locator_cl_cte/README.rst to know how to connect

Building & Running
************
- Locator:
	* Connect locator device 
	* Change directory to: ncs/nrf/applications/direction_finding/aoa_beacon_cl_cte/
	* Run the build & run command given below
- Beacon:
	* Disconnect locator and connect beacon
	* Change directory to: ncs/nrf/applications/direction_finding/aoa_beacon_cl_cte/
	*  Run the build & run command given below
- Server:
	* Receives IQ sample from the locator once the locator starts receiving packets from beacons
	* Currently user serial port to receive data from the locator 
	* Processes IQ samples using MUSIC algorithm to reduce noise
	* Calculates azimuth and elevation angle of arrival and 2D location in image view
	* Once the locator and beacon are up and running
		* Open jupyter notebook: ``jupyter notebook``
		* Run Server/end_to_end.ipynb
		

Build & run command
~~~~~~~~~~~~~~~~~~~~~~~~

.. code-block:: console

   nrfjprog --family nRF52 -e
   west build -b nrf52833dk_nrf52833 -d build
   west flash

Steps:
************
- Clone the project:
	* Install git if not installed: ``sudo apt install git``
	* Clone: ``git clone https://github.com/masumbillah74/localizationAR``

- Install python and pip: 
	* ``sudo apt install python3``
	* ``sudo apt-get install python3-pip``
- Virtual environment:
	* Before advancing through next steps it is strongly reccomended to use a virtual environment
	* Install virtualenv: ``sudo pip3 install virtualenv``
	* Create virtualenv: ``virtualenv virtualenv_name``
	* Activate virtualenv: ``source virtualenv_name/bin/activate``
	
	* **Tips:** Create a script for recurrent virtual environment activation.
		* Save the script in home directory as <your_script_name>.sh.
		* Set permission: chmod 777 ~/<your_script_name>.sh 
		* Activate your virtual environment: ``source ~/<your_script_name>.sh``

Script for recurrent activation:

.. code-block:: console

	#!/bin/bash
	source <virtualenv_name/bin>/bin/activate

- Installation for beacon and locator: 
	* Install J-Link Software and Documentation Pack: https://www.segger.com/downloads/jlink
	* Install the nRF command line tool: https://www.nordicsemi.com/Products/Development-tools/nrf-command-line-tools/download#infotabs
		* Add nRF command line tool to PATH: ``export PATH="<parent_directory>/nrf-command-line-tools/bin:$PATH"``
	* Install cmake: https://cmake.org/download/
		* Add cmake to PATH: ``export PATH="<cmake_parent_directory>/bin:$PATH"``
	* Install west: ``pip install west``

- Installation for the server code:
	* ``pip install jupyter notebook``
	* ``pip install pyserial``
	* ``pip install pandas``
	* ``pip install pyargus``
	* ``pip install matplotlib``
 	* ``pip install seaborn`

- Once all of the dependencies are installed, deploy the locator code and beacon code to associated devices and launch the server code.
