#ifndef TRAFFIC_SITUATION_HPP
#define TRAFFIC_SITUATION_HPP

#include "Edge.hpp"

class TrafficSituation : public Edge
{
protected:
	Edge *edge;

public:
	TrafficSituation(Edge &edge) : Edge(edge.getWeight()){
		this->edge = &edge;
	}

	TrafficSituation(Edge *edge) : Edge(edge->getWeight()){
		this->edge = edge;
	}

	list<string> getDecos(){
		list<string> lst = edge->getDecos();
		lst.push_front(this->getAttr("deko"));
		return lst;
	}

	Node *getStartNode(){
		return edge->getStartNode();
	}

	Node *getEndNode(){
		return edge->getEndNode();
	}

	void setStartNode(Node *n){
		edge->setStartNode(n);
	}

	void setEndNode(Node *n){
		edge->setEndNode(n);
	}
};

#endif