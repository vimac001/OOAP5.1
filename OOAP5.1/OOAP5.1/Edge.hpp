#ifndef EDGE_HPP
#define EDGE_HPP

#include <map>
#include <list>

#include "Color.hpp"

using namespace std;

class Node;

class Edge
{
protected:
	Node *startnode;
	Node *endnode;
	double weight;
	map<string, string> edge_attributes;

public:
	Edge(){
		this->startnode = nullptr;
		this->endnode = nullptr;
		this->weight = 0.0;
	}

	Edge(double weight){
		this->startnode = nullptr;
		this->endnode = nullptr;
		this->weight = weight;
	}

	virtual double getWeight(){
		return this->weight;
	}

	virtual Node *getStartNode(){
		return this->startnode;
	}

	virtual Node *getEndNode(){
		return this->endnode;
	}

	virtual void setStartNode(Node *n){
		this->startnode = n;
	}

	virtual void setEndNode(Node *n){
		this->endnode = n;
	}

	virtual void setAttr(string key, string val){
		this->edge_attributes[key] = val;
	}

	virtual string getAttr(string key){
		map<string, string>::iterator it;
		if((it = this->edge_attributes.find(key)) != this->edge_attributes.end()){
			return (*it).second;
		}

		return "";
	}

	virtual list<string> getDecos(){
		list<string> lst;
		lst.push_back(this->getAttr("deko"));
		return lst;
	}

	virtual Color getColor(){
		return 0x222222;
	}
};
#endif