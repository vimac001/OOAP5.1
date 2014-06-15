#ifndef MOTORCYCLE_HPP
#define MOTORCYCLE_HPP

#include "Vehicle.hpp"

class Motorcycle : public Vehicle
{
public:
	Motorcycle(double speed) : Vehicle(speed){

	}

	double neededTimeForDistance(double dist){
		return dist / this->speed;
	}
};


#endif