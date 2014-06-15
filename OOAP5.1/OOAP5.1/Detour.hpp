#ifndef DETOUR_HPP
#define DETOUR_HPP

#include "TrafficSituation.hpp"

class Detour : public TrafficSituation
{
public:
	Detour(Edge& edge) : TrafficSituation(edge){
		this->setAttr("deko", "Detour");
	}

	Detour(Edge *edge) : TrafficSituation(edge){
		this->setAttr("deko", "Detour");
	}

	double getWeight(){
		return this->edge->getWeight() + 5;
	}

	Color getColor(){
		return 0xcfcc00;
	}
};

#endif