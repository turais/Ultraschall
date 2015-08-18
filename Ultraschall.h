/**
 * 
 * 
  Ultraschall.h - This is an small Arduino Library - designed for simple
	and easy use. It has an build-in temperature compensation and several
	functions to read the distance to an object in millimeters, centimeters
	and inches. 
	
  Created by Johannes Kuehnel, August 13, 2015.
  
  Copyright (c) 2015 Johannes Kuehnel

	This software is provided 'as-is', without any express or implied 
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software. Permission is granted to anyone
	to use this software for any purpose, including commercial applications,
	and to alter it and redistribute it freely, subject to the following 
	restrictions:
	
	1. The origin of this software must not be misrepresented; you must 
		not claim that you wrote the original software. If you use this 
		software in a product, an acknowledgment in the product 
		documentation would be appreciated but is not required.
	
	2. Altered source versions must be plainly marked as such, and must 
		not be misrepresented as being the original software.
	
	3. This notice may not be removed or altered from any source distribution.
  
  * 
  * 
*/

#ifndef Ultraschall_h
#define Ultraschall_h

#include <Arduino.h>

#define US_PER_INCH 74.7
#define US_PER_MM 2.94
#define US_PER_CM 29.4

#define SPEED_OF_SOUND_BASE 331.5
#define SPEED_OF_SOUND_FACTOR 0.6
#define INIT_MAXDISTANCE_CM 500


class Ultraschall {
	
	public:
		Ultraschall(uint8_t triggerPin, uint8_t echoPin, 
			unsigned long maxDistanceCM = INIT_MAXDISTANCE_CM );
		double getDistanceInInch();
		double getDistanceInMils();
		double getDistanceTempCInMils(double temp);
		double getDistanceInCM();	
		
	private:
		uint8_t mTriggerPin;		
		uint8_t mEchoPin;
		unsigned long mTimeout;
		double readDuration();
		double calculateSpeedOfSound(double temp);
		double calculateMicroSecondsPerMM(double speedofSound);
			
};

#endif
