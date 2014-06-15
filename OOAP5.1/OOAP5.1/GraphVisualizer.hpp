#ifndef GRAPH_VISUALIZER_HPP
#define GRAPH_VISUALIZER_HPP

#include "DiGraph.hpp"

class GraphVisualizer
{
public:
	virtual void render(DiGraph &g) = 0;
	virtual void show() = 0;
	virtual void highlightPath(List<Edge*> path) = 0;
};

#endif