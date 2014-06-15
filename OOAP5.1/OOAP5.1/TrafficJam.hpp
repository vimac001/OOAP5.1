#ifndef TRAFFIC_JAM_HPP
#define TRAFFIC_JAM_HPP

#include "TrafficSituation.hpp"

class TrafficJam : public TrafficSituation
{
public:
	TrafficJam(Edge& edge) : TrafficSituation(edge){
		this->setAttr("deko", "TrafficJam");
	}

	TrafficJam(Edge *edge) : TrafficSituation(edge){
		this->setAttr("deko", "TrafficJam");
	}

	double getWeight(){
		return this->edge->getWeight() + 10;
	}

	Color getColor(){
		return 0xff9900;
	}
};

#endif