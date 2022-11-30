# City Network

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

## Purpose
Create a city network that can transmit messages to a choosen received city. Each city in the network will keep track of the city's name, it's neighboring cities, the messages it receives, and the number of messages that passed through the city when transmitting messages.

### User Selection

1. rebuildNetwork
    * Inputs:
        - None
    * Outputs:
        - None

2. printPath
    * Inputs:
        - None
    * Outputs:
        - Print the current city network

3.  transmitMessage
    * Inputs:
        - City to receive message
        - Message to send to receiving city
    * Outputs:
         - Prints the cities traversed to transmit msg and the msg
    
4.  addCity
    * Inputs:
        - New city's name
        - Previous city if not first city (else 'First')
    * Outputs:
        - None

5. deleteCity   
    * Inputs:
        - Existing city's name to delete
    * Outputs:
        - None

6. deleteNetwork
    * Inputs:
        - None
    * Outputs:
        - None

7.  quit
    * Inputs:
        - None
    * Outputs:
        - None

## CMAKE Build:

### For Mac: 
```sh
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"
make all
```

### Run:
```sh
./src/CityNetwork_run 
```
