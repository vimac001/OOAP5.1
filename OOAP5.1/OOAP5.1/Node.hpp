#ifndef NODE_HPP
#define NODE_HPP

#include <string>

#include "Edge"
#include "List.hpp"

using namespace std;

class Node
{

private:
	string node_key;
	int position_x, position_y;
	List<Edge*> edges;

public:
	Node(){
		this->node_key = nullptr;
		this->position_x = 0;
		this->position_y = 0;
	}

	Node(string node_key){
		this->node_key = node_key;
		this->position_x = 0;
		this->position_y = 0;
	}

	Node(string node_key, int x, int y){
		this->node_key = node_key;
		this->position_x = x;
		this->position_y = y;
	}

	string getKey(){
		return this->node_key;
	}

	int getPositionX(){
		return this->position_x;
	}

	int getPositionY(){
		return this->position_y;
	}

	List<Edge*> getEdges(){
		return this->edges;
	}

	Edge *getEdgeTo(Node *dest){
		for(unsigned int i = 0; i < this->edges.size(); i++){
			Edge *e = this->edges.getValueAt(i);
			if(e->getEndNode() == dest) 
				return e;
		}

		return nullptr;
	}

	Edge *getEdgeTo(std::string destKey){
		for(unsigned int i = 0; i < this->edges.size(); i++){
			Edge *e = this->edges.getValueAt(i);
			if(e->getEndNode()->getKey() == destKey) return e;
		}

		return nullptr;
	}

	void setKey(string val){
		this->node_key = val;
	}

	void setPositionX(int val){
		this->position_x = val;
	}

	void setPositionY(int val){
		this->position_y = val;
	}

	void setPosition(int x, int y){
		this->position_x = x;
		this->position_y = y;	
	}

	void setNewEdge(Edge *val){
		this->edges.append(val);
	}

	List<Node*> getNeighbours(){
		List<Node*> ret;
		for(unsigned int i = 0; i < this->edges.size(); i++){
			ret.append(this->edges.getValueAt(i)->getEndNode());
		}

		return ret;
	}
};



#endif