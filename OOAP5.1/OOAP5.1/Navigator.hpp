#ifndef NAVIGATOR_HPP
#define NAVIGATOR_HPP

#include "DiGraph.hpp"
#include "Vehicle.hpp"
#include "GraphVisualizer.hpp"
#include <vector>

using namespace std;

class Navigator
{
private:
	DiGraph *graph;
	Vehicle *vehicle;

public:
	Navigator(DiGraph *graph){
		this->graph = graph;
		this->vehicle = nullptr;
	}

	void setGraph(DiGraph *graph){
		this->graph = graph;
	}

	void setVehicle(Vehicle *v){
		this->vehicle = v;
	}

	double planRoute(string from, string to){
		double pthlen = 0.0;
		List<Edge*> pth = this->graph->dijkstraShortestPath(from, to);

		this->graph->getVisualizer()->highlightPath(pth);

		for(unsigned int i = 0; i < pth.size(); i++){
			pthlen += pth.getValueAt(i)->getWeight();
		}

		return this->vehicle->neededTimeForDistance(pthlen);
	}

	void planTour(vector<string> wayp){
		vector<string>::iterator it, fit, tmp_end;
	
		List<Edge*> lst;
		tmp_end = wayp.end()--;


		for(fit = wayp.begin(); fit != tmp_end; fit++)
			for(it = wayp.begin(); it != wayp.end(); ++it){
			
			List<Edge*> tlist = this->graph->dijkstraShortestPath(*fit, *it);
			for(int i = 0; i < tlist.size(); i++){
				lst.append(tlist.getValueAt(i));
				}
			}

			this->graph->getVisualizer()->highlightPath(lst);
		}

};


#endif