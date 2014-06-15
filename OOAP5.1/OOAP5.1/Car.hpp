#ifndef CAR_HPP
#define CAR_HPP

#include "Vehicle.hpp"

class Car : public Vehicle
{
public:
	Car(double speed) : Vehicle(speed){

	}

	double neededTimeForDistance(double dist){
		return dist / this->speed;
	}
};


#endif