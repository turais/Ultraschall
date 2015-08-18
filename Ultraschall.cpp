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

/**
 * @brief Ultraschall Constructor 
 * @param triggerPin Arduino Pin Number - where Trigger Pin from the HCSR04 is connected
 * @param echoPin Arduino Pin Number - where Echo Pin from the HCSR04 is connected
 * @param maxDistanceCM - max distance you like to measure  
 * */

Ultraschall::Ultraschall(uint8_t triggerPin, uint8_t echoPin, unsigned long maxDistanceCM) {
	this->mTriggerPin = triggerPin;
	this->mEchoPin = echoPin;
	this->mTimeout = US_PER_CM * maxDistanceCM;
	pinMode(mTriggerPin, OUTPUT);
    pinMode(mEchoPin, INPUT);
}

/**
 * @brief Returns the measured distance in inches. 
 * @return double - distance in inches 
 * */

double Ultraschall::getDistanceInInch() {
	return Ultraschall::readDuration() / US_PER_INCH / 2;
}

/**
 * @brief Returns the measured distance in millimeters. 
 * @return double - distance in millimeters 
 * */

double Ultraschall::getDistanceInMils() {
	return (Ultraschall::readDuration() / US_PER_MM / 2);
}

/**
 * @brief Returns the measured distance in centimeters. 
 * @return double - distance in centimeters 
 * */

double Ultraschall::getDistanceInCM() {
	return Ultraschall::readDuration() / US_PER_CM / 2;
}

/**
 * @brief Returns the measured distance in centimeters - temperature
 * compensated.
 * @param temp Temperature in degree celsius
 * @return double - distance in millimeters 
 * */

double Ultraschall::getDistanceTempCInMils(double temp) {	
	double speedofSound = Ultraschall::calculateSpeedOfSound(temp);
	double mps = Ultraschall::calculateMicroSecondsPerMM(speedofSound);	
	return Ultraschall::readDuration() / mps / 2;	
}

/**
 * @brief Calculates the speed of sound - temperature compensated
 * more: https://en.wikipedia.org/wiki/Speed_of_sound#Practical_formula_for_dry_air 
 * @param Temperature in degree celsius
 * @return double - speed of sound 
 * */

double Ultraschall::calculateSpeedOfSound(double temp) {
	return (SPEED_OF_SOUND_BASE + SPEED_OF_SOUND_FACTOR*temp);	
}

/**
 * @brief Calculates the speed of sound in microseconds per millimeter
 * @param speed of sound 
 * @return Speed of sound in microseconds per millimeter 
 * */

double Ultraschall::calculateMicroSecondsPerMM(double speedofSound) {
	return 1000.0/speedofSound;
}

/**
 * @brief Reads the duration in microseconds which the sound travels 
 * @returns duration in microseconds 
 * */

double Ultraschall::readDuration() {	
	
	digitalWrite(mTriggerPin, LOW);
	delayMicroseconds(2);
	digitalWrite(mTriggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(mTriggerPin, LOW);
	float pulse = pulseIn(mEchoPin, HIGH, mTimeout);
	return pulse;	
}
