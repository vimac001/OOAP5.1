#ifndef ABBREVIATION_HPP
#define ABBREVIATION_HPP

#include "TrafficSituation.hpp"

class Abbreviation : public TrafficSituation
{
public:
	Abbreviation(Edge& edge) : TrafficSituation(edge){
		this->setAttr("deko", "Abbreviation");
	}

	Abbreviation(Edge *edge) : TrafficSituation(edge){
		this->setAttr("deko", "Abbreviation");
	}

	double getWeight(){
		return this->edge->getWeight() - 5;
	}

	Color getColor(){
		return 0x00ff00;
	}
};

#endif