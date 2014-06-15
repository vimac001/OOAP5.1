#include <string>
#include <iostream>
#include <vector>

#include "DiGraph.hpp"
#include "OpenCVGraphVisualizer.hpp"
#include "Vehicles"
#include "Navigator.hpp"

using namespace std;

void createDummyGraph(DiGraph &g){
	Node *Aachen	= new Node("Aachen"		, 100	, 600),
		 *Berlin	= new Node("Berlin"		, 300	, 650),
		 *Koeln		= new Node("Koeln"		, 300	, 300),
		 *Essen		= new Node("Essen"		, 900	, 300),
		 *Bonn		= new Node("Bonn"		, 300	, 150),
		 *Krefeld	= new Node("Krefeld"	, 100	, 160);

	g.addNode(Aachen);
	g.addNode(Berlin);
	g.addNode(Koeln);
	g.addNode(Essen);
	g.addNode(Bonn);
	g.addNode(Krefeld);
/*
	if(g.getLength() == 6) {
		cout << "Die Methode addNode\t  hat funktioniert" << endl;

	}
	else {
		cout << "ERROR addNode ist fehlerhaft" << endl;
	}
	*/

	Edge *Aachen_Berlin = new Edge(7);
	Aachen_Berlin = new TrafficJam(Aachen_Berlin);
	g.addEdge(Aachen_Berlin, Aachen, Berlin);

	//g.addEdge("Aachen"	, "Berlin"	, 7 );
	g.addEdge("Koeln"	, "Aachen"	, 9	);
	//g.addEdge("Aachen"	, "Krefeld"	, 7	);
	Edge *Aachen_Krefeld = new Edge(7);
	Aachen_Krefeld = new Detour(Aachen_Krefeld);
	Aachen_Krefeld = new Stoppage(Aachen_Krefeld);
	g.addEdge(Aachen_Krefeld, Aachen, Krefeld);

	//g.addEdge("Berlin"	, "Essen"	, 40);
	Edge *Berlin_Essen = new Edge(40);
	Berlin_Essen = new Detour(Berlin_Essen);
	g.addEdge(Berlin_Essen, Berlin, Essen);

	g.addEdge("Berlin"	, "Koeln"	, 3	);
	g.addEdge("Koeln"	, "Essen"	, 31);
	//g.addEdge("Bonn"	, "Essen"	, 8	);
	Edge *Bonn_Essen = new Edge(8);
	Bonn_Essen = new Abbreviation(Bonn_Essen);
	g.addEdge(Bonn_Essen, Bonn, Essen);

	g.addEdge("Krefeld"	, "Bonn"	, 8	);
	/*
	if(g.getEdges("Aachen").size() == 2) {
		cout << "Die Methode addEdge\t  hat funktioniert" << endl;
	}
	else {
		cout << "ERROR addEdge hat einen Fehler" << endl;
	}

	if(g.getNeighbours("Aachen").size() == 2) {
		cout << "Die Methode getNeighbours hat funktioniert" << endl;
	}
	else {
		cout << "ERROR getNeighbours ist fehlerhaft" << endl;
	}
	*/
}

int main(int argc, const char *argv[]){
	DiGraph myGraph;
	OpenCVGraphVisualizer graphviz;
	int i;
	int pathZahl = 0;

	myGraph.setVisualizer(&graphviz);

	createDummyGraph(myGraph);

	Navigator navi(&myGraph);

	int speed = 120;
	navi.setVehicle(new Car(speed));


	myGraph.getVisualizer()->render(myGraph);
	/*
	List<Edge *> tmp = myGraph.dijkstraShortestPath("Aachen", "Essen"); 
	for(i = 0; i < tmp.size(); i++) {
		pathZahl += tmp.getValueAt(i)->getWeight();
	}

	if(pathZahl == 23) {
		cout << "Der DikstraShortestPath funktioniert" << endl;
	}
	else {
		cout << "ERROR der Dikstra ist fehlerhaft" << endl;
	}

	cout << "\nFahrzeit: " << navi.planRoute("Aachen", "Essen") << endl;
	*/

	vector<string> tour;
	tour.push_back("Aachen");
	tour.push_back("Berlin");
	tour.push_back("Bonn");

	navi.planTour(tour);
	
	myGraph.getVisualizer()->show();

	system("PAUSE");

	return 0;
}


//addedge addnote getneighbour testen


int main_small(int argc, const char argv[]){

	Edge *edg = new Edge(10);
	cout << edg->getWeight() << endl;
	edg = new Abbreviation(edg);
	cout << edg->getWeight() << endl;
	
	edg = new Stoppage(edg);
	cout << edg->getWeight() << endl;

	list<string> lst = edg->getDecos();
	list<string>::iterator it = lst.begin();

	for(; it != lst.end(); it++){
		cout << *it << endl;
	}

	

	char str;
	cin >> str;
	return 0;
}