BeagleRover
===========

This is an implemention of a semi-intelligent rover for a BeagleBone. The intelligence of the system comes from interfaces to a GPS sensor, a digital compass, and a USB WiFi adapter for communication with a base station.

This project includes software for interfacing with the GPS, compass, and the motors of an RC car. Python scripts are also included to communicate with the RC car over the network, giving it commands to turn and go forward as well as query the GPS and compass sensors.

The code is structured for two types of interaction

1. Stand-alone control and navigation
 * main code located in movement.c
2. Remote operation via Python
 * communications layer in Python located in networkPython folder, and shared libraries compiled into sharedLibs folder

```
make		# compiles movement binary and shared libraries
make clean	# removes all compiled objects and binaries
```

## Stand-Alone Operation

The rover can be operated with pre-defined movements in the file *movement.c*. Movement can be accomplished by calling the functions *moveForward(int useconds)* and *turn(float heading)*, to move forward for a specified duration and turn to a specified heading, respectively. Movement code should be added to the main function in *movement.c*, and can be executed after compilation with make. The standalone operation executable is called *movement*. 

Waypoint functionality is currently in development in the function *waypointManager(void)*. As of 11/12/2012, the waypoint manager can successfully queue and dequeue waypoints, calculate a new heading, and turn to the desired waypoint. Currently, code to determine the distance to the target waypoint and stop the motors is being debugged.

## Remote Operation via Python

The rover can also be operated over a WiFi network via two included Python scripts that setup a server/client relationship with the BeagleBone.

*boneMovementServer.py* is Python code designed to be run on the Bone, and will setup a server to listen for movement commands from a client. It can be started with the command

    python boneMovementServer.py <IP-ADDRESS> <PORT>

where <IP-ADDRESS> is the IP Address of the BeagleBone and <PORT> is the TCP port to listen on. For example,

    python boneMovementServer.py 192.168.2.2 5005

will start the code listening for connections on port 5005.

*cpMovementClient.py* is Python code designed to run on the controlling base station - any computer that is connected over the network to the Bone and can run python. t can be started with the command

    python cpMovementClient.py <IP-ADDRESS> <PORT>

where <IP-ADDRESS> is the IP Address of the BeagleBone that you want to connect to and <PORT> is the TCP port that the BeagleBone is listening on. For example,

    python cpMovementClient.py 192.168.2.2 5005

will attempt to connect to a BeagleBone at 192.168.2.2 through port 5005.

This code relies on compilation of shared libraries for interfacing to the motors and sensors via C, so the shared libraries must be compiled with make

	make	# compile the shared libraries into sharedLibs/

## Libraries (Sensor Interfaces, Waypointing)

### Compass

The main compass code is located in *compass.c*. This file includes routines for initialization, calibrating the compass, and reading the heading. Two sample code files are included, *calibrate.c* runs the calibration routine of the compass for 10 seconds, during which time the user should rotate the compass axially twice for calibration. *main.c* will initiaze the compass and print the compass reading at a frequency of 5 Hz. 

These can be complied with gcc, or using make from the project directory

    make CompassExample

### GPS

The main GPS code is located in *gps.c*, and the dataGPS structure for passing around GPS data is located in *gps.h*. An example program that prints the current GPS location is shown in main.c, and can be compiled with gcc or make

    make GPSExample

### Waypoints

Although not fully functional as of 11/12/2012, prototype helper code for waypoint navigation is located in Waypoints.

More details about the project can be found on the project wiki:
http://elinux.org/ECE497_Project_Rover
