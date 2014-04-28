//------------------------------------------------------------------------
//  Author: LabJack
//  11/10/2011
//  This example demonstrates how to use some of the the U12 analog functions
//  in the ljacklm library.
//
//  The functions used are AISample and AOUpdate which are documented in
//  sections 4.6, and 4.11 in the U12 User's Guide or in the ljacklm.h header
//  file.  For EAnalogIn and EAnalogOut examples look at the easyFunctions.c
//  example.
//------------------------------------------------------------------------
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "ljacklm.h"


void handleError(long error, char *functionName)
{
	char errorString[50];

	if(error)
	{
		GetErrorString(error, errorString);
		printf("%s error %ld: %s\n", functionName, error, errorString);
		exit(1);
	}
}


int main (int argc, char *argv[])
{
	float version = 0.0;
	long errorcode = 0;

	long idnum = -1;  //Using first found U12
	long demo = 0;  //Normal operations
	long stateIO = 0;  //Output states for IO0-IO3

	//AOUpdate specific paramters
	long trisD = 0;  //Directions for D0-D15
	long trisIO = 0;  //Directions for IO0-IO3
	long stateD = 0;  //Output states for D0-D15
	long updateDigital = 0;  //Tris and state values are only being read
	long resetCounter = 0;  //Not resetting counter
	unsigned long count = 0;  //Returned current count value
	float analogOut0 = 0.8;  //Voltage for AO0
	float analogOut1 = 3.2;  //Voltage for AO1

	//AISample specific parameters
	long updateIO = 0;  //State values are only being read
	long ledOn = 0;  //Turning LED on
	long numChannels = 2;  //Reading 2 channels
	long channels[2] = {2, 3};  //Reading AI2 and AI3
	long gains[2] = {0, 0};  //Gains.  Does not matter in this case since we are
							 //performing single ended readings.
	long disableCal = 0;  //Will apply calibration constants
	long overVoltage = 0;  //Returns if overvoltage was detected (>1)
	float voltages[4] = {0};  //Returned voltage readings.  Pass an array of all zeros.

	version = GetDriverVersion();
	printf("Driver version: %.3f\n", version);

	version = GetFirmwareVersion(&idnum);
	printf("U12 Firmware version: %.3f\n\n", version);

	printf("Setting AO0 to %.3f V and AO1 to %.3f V\n", analogOut0, analogOut1);

	errorcode = AOUpdate(&idnum, demo, trisD, trisIO, &stateD,
					&stateIO, updateDigital, resetCounter, &count, analogOut0,
					analogOut1);
	handleError(errorcode, "AOUpdate");

	errorcode = AISample(&idnum, demo, &stateIO, updateIO, ledOn, 
					numChannels, channels, gains, disableCal, &overVoltage,
					voltages);
	handleError(errorcode, "AISample");

	printf("AI%ld = %.3fV\nAI%ld = %.3fV\n", channels[0], voltages[0], channels[1], voltages[1]);

	return 0;
}
