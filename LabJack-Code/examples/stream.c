//------------------------------------------------------------------------
//  Author: LabJack
//  11/10/2011
//  This example demonstrates how to use the U12 stream functions in the ljacklm
//  library.  4 channels are streamed at a 250 scans per second.
//
//  The functions used are AIStreamStart, AIStreamRead and AIStreamClear, which
//  are documented in sections 4.8, 4.9 and 4.10 in the U12 User's Guide or in
//  the ljacklm.h header file.
//------------------------------------------------------------------------
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include "ljacklm.h"

void handleError(long error, char *functionName, bool noExit)
{
	char errorString[50];

	if(error)
	{
		GetErrorString(error, errorString);
		printf("%s error %ld: %s\n", functionName, error, errorString);
		if(!noExit)
		{
			exit(1);
		}
	}
}

long getTimeInSecs( void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + (tv.tv_usec / 1000000);
}

int main (int argc, char *argv[])
{
	float version = 0.0;
	long idnum = -1;  //Using first found U12
	long errorcode;
	int i,j;
	int numStreamReads = 10;
	long t0, t1;

	//AIStreamStart specific parameters
	long demo = 0;  //Normal operations
	long stateIOin = 0;  //Output states for IO0-3.
	long updateIO = 0;  //Just a read performed, so stateIOin not set.
	long ledOn = 1;  //LED tirned on
	long numChannels = 4;  //Reading 4 channels
	long channels[4] = {0, 1, 10, 11};  //4 channels are AI0, AI1, AIN4-5 Diff, 
									    //AIN6-7 Diff
	long gains[4] = {0, 0, 1, 1};  //Setting all gains +-10 V.  Note that gains
								   //are only available for differential channels.
	float scanRate = 250.0;  //Scans aquired per second
							 //Sample rate = scanRate*numChannels
	long disableCal = 0;  //Apply calibration constants
	long readCount = 0;  //Not reading counter.  readCount only supported in
						 //firmware versions 1.03 and above.

	//AIStreamRead specific paramters
	long numScans = 500;  //Wait for 500 scans, or 500*numChannels samples.
	long timeout = 5;  //Function will timeout in 10 second.
	float voltages[4096][4];  //Returned readings array.
	long stateIOout[4096];  //Retuned IO states array.
	long reserved = 0;
	long ljScanBacklog = 0;  //Returned scan backlog.
	long overVoltage;  //Returned over voltage.


	version = GetDriverVersion();
	printf("Driver version: %.3f\n", version);

	version = GetFirmwareVersion(&idnum);
	printf("U12 Firmware version: %.3f\n\n", version);


	errorcode = AIStreamStart(&idnum, demo, stateIOin, updateIO, ledOn,
				numChannels, channels, gains, &scanRate, disableCal,
				0, readCount);
	handleError(errorcode, "AIStreamStart", false);
	printf("Stream started.  Set scan rate = %0.3f\n\n", scanRate);

	t0 = getTimeInSecs();

	for(i = 0; i < numStreamReads; i++)
	{
		//Fill voltages and stateIOOut arrays with zero
		for(j = 0;  j < 4096;  j++)
		{
			voltages[j][0] = voltages[j][1] = voltages[j][2] = voltages[j][3] = 0.0;
			stateIOout[j] = 0;
		}

		errorcode = AIStreamRead(idnum, numScans, timeout, voltages, stateIOout,
					&reserved, &ljScanBacklog, &overVoltage);
		handleError(errorcode, "AIStreamRead", true);
		if(errorcode)
		{
			goto error_clear;
		}
		printf("AIStreamRead %d: First scan = %.3f V, %.3f V, %.3f V, %.3f V\n", i+1, voltages[0][0], voltages[0][1], voltages[0][2], voltages[0][3]);
		printf("  Scan backlog: %ld\n\n", ljScanBacklog);
	}

	t1 = getTimeInSecs();

	errorcode = AIStreamClear(idnum);
	handleError(errorcode, "AIStreamClear", false);

	printf("%ld scans took %ld seconds\n", numScans*numStreamReads, t1-t0);
	printf("Scans rate = %.3f scans/seconds\n", (float)(numScans*numStreamReads)/(t1-t0));

	return 0;

error_clear:
	AIStreamClear(idnum);
	return 1;
}
