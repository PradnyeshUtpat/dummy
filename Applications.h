//Applications of Barnes Hut Algorithm

//Include Libraries
#include <stdio.h>
#include <stdlib.h>

//Functions are declared here:

/*1. sat() :
Runs the satellite system created in txt file as input
and builds the data structures with respect to 3D calculations in program
calculates Newton's Force of a system at a point*/

void sat(char *filename);

/*2. charge() :
Runs the charge system created in txt file as input
and builds the data structures with respect to 2D calculations in program
calculates Coulumbs's Force of a system at a point*/

void charge(char *filename);

/*3. convertlatitude() & convert_longitude() 
Convert Latitude & Longitude to Km*/

//Latitude is y(vertical direction)
float convert_latitude(float y);

//Longitude is x(horizontal direction)
float convert_longitude(float x);