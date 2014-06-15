#ifndef STOPPAGE_HPP
#define STOPPAGE_HPP

#include "TrafficSituation.hpp"

class Stoppage : public TrafficSituation
{
public:
	Stoppage(Edge& edge) : TrafficSituation(edge){
		this->setAttr("deko", "Stoppage");
	}

	Stoppage(Edge *edge) : TrafficSituation(edge){
		this->setAttr("deko", "Stoppage");
	}

	double getWeight(){
		return this->edge->getWeight() + 50;
	}

	Color getColor(){
		return 0xff0000;
	}
};

#endif