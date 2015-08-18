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

#include "Ultraschall.h"

Ultraschall::Ultraschall(uint8_t triggerPin, uint8_t echoPin, unsigned long maxDistanceCM) {
	this->mTriggerPin = triggerPin;
	this->mEchoPin = echoPin;
	this->mTimeout = US_PER_CM * maxDistanceCM;
	pinMode(mTriggerPin, OUTPUT);
    pinMode(mEchoPin, INPUT);
}

double Ultraschall::getDistanceInInch() {
	return Ultraschall::readDuration() / US_PER_INCH / 2;
}

double Ultraschall::getDistanceInMils() {
	return (Ultraschall::readDuration() / US_PER_MM / 2);
}

double Ultraschall::getDistanceInCM() {
	return Ultraschall::readDuration() / US_PER_CM / 2;
}

double Ultraschall::getDistanceTempCInMils(double temp) {	
	double speedofSound = Ultraschall::calculateSpeedOfSound(temp);
	double mps = Ultraschall::calculateMicroSecondsPerMM(speedofSound);	
	return Ultraschall::readDuration() / mps / 2;	
}

double Ultraschall::calculateSpeedOfSound(double temp) {
	return (SPEED_OF_SOUND_BASE + SPEED_OF_SOUND_FACTOR*temp);	
}

double Ultraschall::calculateMicroSecondsPerMM(double speedofSound) {
	return 1000.0/speedofSound;
}

double Ultraschall::readDuration() {	
	
	digitalWrite(mTriggerPin, LOW);
	delayMicroseconds(2);
	digitalWrite(mTriggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(mTriggerPin, LOW);
	float pulse = pulseIn(mEchoPin, HIGH, mTimeout);
	return pulse;
	
}
