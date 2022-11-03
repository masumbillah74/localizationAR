# localizationAR

- CD to directory
- If git not installed: sudo apt install git
- Clone: git clone https://github.com/masumbillah74/localizationAR
- Install python: Sudo apt install python3
- Install pip: sudo apt-get install python3-pip
- Install virtualenv: sudo pip3 install virtualenv
- Create virtualenv: virtualenv virtualenv_name
- Activate virtualenv: <br/>
	source virtualenv_name/bin/activate <br/>
	Tips: Create a script to activate easily. Save the script in home directory as <your_script_name>.sh. <br/>
	-- Inside script put following lines:<br/>
	#!/bin/bash<br/>
	source <virtualenv_name/bin>/bin/activate<br/>
	-- Set permission: chmod 777 ~/<your_script_name>.sh <br/>
	-- From next time, in terminal just run the following command to activate your virtual environment <br/>
	source ~/<your_script_name>.sh

- Install jupyter notebook: <br/>
	pip install jupyter notebook <br/>
- Open jupyter notebook:<br/>
	jupyter notebook

- Install dependencies:<br/>
	pip install pyserial <br/>
	pip install pandas <br/>
	pip install pyargus <br/>
	pip install matplotlib <br/>
 	pip install seaborn <br/>

- Install J-Link Software and Documentation Pack  <br/>

	https://www.segger.com/downloads/jlink

- Download the nRF command line tool:<br/>
	https://infocenter.nordicsemi.com/index.jsp?topic=%2Fug_nrf_cltools%2FUG%2Fcltools%2Fnrf_installation.html
	<br/>
	
	Add to PATH: <br/>
	export PATH="<parent_directory>/nrf-command-line-tools/bin:$PATH"
- Install cmake <br/>
https://cmake.org/download/
<br/>
Add to PATH: <br/>
export PATH="<cmake_parent_directory>/bin:$PATH"

- Install west <br/>
	pip install west
