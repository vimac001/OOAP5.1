#ifndef DI_GRAPH_HPP
#define DI_GRAPH_HPP

#include "Node.hpp"
#include "PriorityQueue.hpp"

class GraphVisualizer;

class DiGraph
{

private:
	///<summary>
	/// Array von Knoten mit dem Bezeichner nodes, in dem alle Knoten des Graphen gespeichert sind.
	///</summary>
	Node **nodes;

	GraphVisualizer *graphviz;
	
	unsigned int sz, ln;
	
	void incr(){
		this->sz *= 2;
		this->sz++;

		Node **tmp = new (Node*[this->sz]);

		for(unsigned int i = 0; i < this->ln; i++){
			tmp[i] = this->nodes[i];
		}

		delete[] this->nodes;
		this->nodes = tmp;
	}

	bool isFull(){
		return this->sz == this->ln + 1;
	}

	unsigned int findIndexByPtr(Node *ptr){
		for(unsigned int i = 0; i < this->ln; i++){
			if(this->nodes[i] == ptr) return i;
		}

		throw "No item at given pointer found!";
	}

	void insertNode(unsigned int pos, Node *n){
		if(this->isFull()) this->incr();

		//Aufrücken
		for(unsigned int i = this->ln; i > pos; i--){
			this->nodes[i] = this->nodes[i - 1];
		}

		this->nodes[pos] = n;

		this->ln++;
	}

public:
	DiGraph(){
		this->sz = 2;
		this->ln = 0;

		this->nodes = new (Node*[this->sz]);
	}

	///<summary>
	/// Fugt die Adresse eines Klassenobjekts vom Typ Node dem Graphen hinzu.
	///</summary>
	void addNode(Node *n){
		this->insertNode(this->ln, n);
	}

	///<summary>
	/// Erstellt ein neues Klassenobjekt vom Typ Edge mit Startknoten key1, Endknoten key2 sowie einem Kantengewicht von weight. Anschlieend wird die Kante der Adjazenzliste des Knotens key1 hinzugefugt.
	///</summary>
	void addEdge(std::string key1, std::string key2, double weight){
		unsigned int i1, i2;

		i1 = this->findIndex(key1);
		i2 = this->findIndex(key2);

		Edge *e = new Edge(weight);
		e->setStartNode(this->nodes[i1]);
		e->setEndNode(this->nodes[i2]);

		this->nodes[i1]->setNewEdge(e);
	}

	void addEdge(Edge *e, Node *startNode, Node *endNode){
		e->setStartNode(startNode);
		e->setEndNode(endNode);

		startNode->setNewEdge(e);
	}

	void addEdge(Edge *e, string startNode, string endNode){
		unsigned int i1, i2;
		i1 = this->findIndex(startNode);
		i2 = this->findIndex(endNode);

		e->setStartNode(this->nodes[i1]);
		e->setEndNode(this->nodes[i2]);

		this->nodes[i1]->setNewEdge(e);
	}

	///<summary>
	/// Gibt eine Liste aller benachbarter Knoten des Knotens mit dem Schlussel key zuruck.
	///</summary>
	List<Node*> getNeighbours(std::string key){
		int ix = this->findIndex(key);
		return this->nodes[ix]->getNeighbours();
	}

	List<Edge*> dijkstraShortestPath(std::string start, std::string end){
		List<Edge*> result;
		PriorityQueue<Node*> nq;
		Node *u;

		unsigned int is = this->findIndex(start), //Index s
					 id = this->findIndex(end); //Index d

		double *dist = new double[this->ln];

		Node* *previous = new Node*[this->ln];

		for(unsigned int i = 0; i < this->ln; i++){
			if(this->nodes[i] == this->nodes[is]){
				dist[i] = 0;
			}else{
				dist[i] = numeric_limits<double>::infinity();
			}

			previous[i] = nullptr;
			nq.insert(this->nodes[i], dist[i]);
		}

		while(!nq.isEmpty()){
			u = nq.extractMin();

			List<Edge*> outEdges = u->getEdges();

			for(unsigned int i = 0; i < outEdges.size(); i++){ //Foreach neighbour of u
				Edge *e = outEdges.getValueAt(i); //Edge to neig.
				Node *v = e->getEndNode(); //Cur Nb.

				unsigned int iu = this->findIndexByPtr(u), //Index u
							 iv = this->findIndexByPtr(v); //Index v

				double alt = dist[iu] + e->getWeight(); //Unendlich + x, echt jetzt? (kommt bei double aber etwas < 0 raus)

				if(alt < dist[iv]){
					dist[iv] = alt;
					previous[iv] = u;
					nq.decreaseKey(v, alt);
				}

			}
		}

		u = this->nodes[id];
		unsigned int iu = id;

		while(previous[iu] != nullptr){
			Node *pu = previous[iu];
			result.append(pu->getEdgeTo(u));
			u = previous[iu];
			iu = this->findIndexByPtr(u);
		}

		delete[] dist;
		delete[] previous;

		return result;
	}

	///<summary>
	/// Gibt eine Liste aller abgehenden Kanten des Knotens mit dem Schlussel key zuruck.
	///</summary>
	List<Edge*> getEdges(std::string key){
		int i = this->findIndex(key);
		return this->nodes[i]->getEdges();
	}

	///<summary>
	/// Gibt eine Liste aller Knoten des Graphen zuruck.
	///</summary>
	List<Node*> getNodes(){
		List<Node*> lst(this->ln);
		for(unsigned int i = 0; i < this->ln; i++){
			lst.append(this->nodes[i]);
		}

		return lst;
	}

	unsigned int findIndex(std::string key){
		for(unsigned int i = 0; i < this->ln; i++){
			if(this->nodes[i]->getKey() == key) return i;
		}

		throw "No item with given key found!";
	}

	unsigned int getLength(){
		return this->ln;
	}

	Node *getNodeAt(unsigned int pos){
		if(pos < this->ln){
			return this->nodes[pos];
		}

		throw "Der Index liegt ausserhalb des Bereiches!";
	}


	void setVisualizer(GraphVisualizer *graphviz){
		this->graphviz = graphviz;
	}

	GraphVisualizer *getVisualizer(){
		return this->graphviz;
	}
};


#endif