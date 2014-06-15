#ifndef BICYCLE_HPP
#define BICYCLE_HPP

#include "Vehicle.hpp"

class Bicycle : public Vehicle
{
public:
	Bicycle(double speed) : Vehicle(speed){

	}

	double neededTimeForDistance(double dist){
		return dist / this->speed;
	}
};


#endif