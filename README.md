# Ultraschall
Easy to use Arduino Ultrasonic Library with or without temperature compensation
![Ultraschall Logo](https://www.turais.de/content/images/2015/08/ultraschall_logo_small.png)

Eine HC-SR04 Beschreibung: [HC-SR04](https://www.turais.de/hcsr04-ultraschall-modul)

Use:

```cpp
#include "Ultraschall.h"

Ultraschall ultra(7,8);

void setup() {
	Serial.begin(9600);
	while (!Serial) {;}  
	Serial.println("Ultraschall Test");
	Serial.println("distance in cm:");   
}

void loop() {	
	
	///for uncompensated distance in cm
	Serial.print(ultra.getDistanceInCM());
	Serial.print("\r");
	delay(500);	
	
	///for temperature compensated distance in mm
	Serial.print(ultra.getDistanceTempCInMils(26.5); ///temperature in degree celsius
	Serial.print("\r");
	delay(500);	
	
}
```


