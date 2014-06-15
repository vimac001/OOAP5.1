#ifndef VEHICLE_HPP
#define VEHICLE_HPP

class Vehicle
{
protected:
	double speed;
public:
	Vehicle(double speed){
		this->speed = speed;
	}

	virtual double neededTimeForDistance(double dist) = 0;
};

#endif