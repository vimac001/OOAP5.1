#ifndef _OPENCV_GRAPH_VISUALIZER_H
#define _OPENCV_GRAPH_VISUALIZER_H

#include <cv.h>
#include <highgui.h>
#include <math.h>
#include <sstream>

#ifndef M_PI 
#define M_PI    3.14159265358979323846f 
#endif

#include "GraphVisualizer.hpp"

#define NODERADIUS 30

class OpenCVGraphVisualizer : public GraphVisualizer
{

private:
	cv::Mat img;
	int zx, zy;

	void drawEdges(List<Edge*> le, cv::Scalar color, int thickness = 1, int arrowMagnitude = 20){
		for(unsigned int c = 0; c < le.size(); c++){
			Edge *e = le.getValueAt(c);
			this->drawEdge(*e, color, e->getWeight(), thickness, arrowMagnitude);
		}
	}

public:
	 OpenCVGraphVisualizer(){
		 int w = 1024, h = 768;
		this->img = cv::Mat::zeros(h, w, CV_8UC3);
		this->zx = w/2;
		this->zy = h/2;
	 }
	 
	 void render(DiGraph &g){
		 this->img.setTo(cv::Scalar(255,255,255));
	
		for(unsigned int i = 0; i < g.getLength(); i++){
			Node *n = g.getNodeAt(i);

			this->drawEdges(n->getEdges(), cv::Scalar(40, 40, 40));

			this->drawNode(*n, cv::Scalar(40, 40, 40));
		}
	 }
	 
	 void show(){
		cvStartWindowThread();
		cv::namedWindow("Graph");
		cv::imshow("Graph", this->img);
		cv::waitKey();
		cvDestroyAllWindows();
	 }

	 void highlightPath(List<Edge*> path){
		 this->drawEdges(path, cv::Scalar(255, 200, 5), 2);
	 }
	 
	 void drawNode(Node &node, cv::Scalar nodeColor){
		cv::Point center(node.getPositionX(), node.getPositionY());
		cv::circle(this->img, center, NODERADIUS, nodeColor, 1, CV_AA);
		 
		int baseline = 0;
		cv::Size textSize = getTextSize(node.getKey(), cv::FONT_HERSHEY_TRIPLEX, 0.5, 1, &baseline);
		 
		cv::Point centerText(node.getPositionX() - (textSize.width/2), node.getPositionY() - (textSize.height/2) + baseline*2);
		 
		cv::putText(this->img, node.getKey(), centerText, cv::FONT_HERSHEY_TRIPLEX, 0.5, cv::Scalar(0,0,0), 1, CV_AA);
	 }
	 
	 void drawEdge(Edge &edge, cv::Scalar color, double weight, int thickness = 1, int arrowMagnitude = 20){
		cv::Point p(edge.getStartNode()->getPositionX(), edge.getStartNode()->getPositionY());
		 
		cv::Point q(edge.getEndNode()->getPositionX(), edge.getEndNode()->getPositionY());
		 
		// Berechne den Winkel
		const double PI = 3.141592653;
		double angle = atan2((double)p.y-q.y, (double)p.x-q.x);
		 
		// Berechne verk\protect \unhbox \voidb@x \bgroup \U@D 1ex{\setbox \z@ \hbox {\char 63 
		q.x = (int) ( q.x + NODERADIUS * cos(angle));
		q.y = (int) ( q.y + NODERADIUS * sin(angle));
		p.x = (int) ( p.x - NODERADIUS * cos(angle));
		p.y = (int) ( p.y - NODERADIUS * sin(angle));
		 
		//Zeichne Hauptlinie
		cv::line(img, p, q, color, thickness, CV_AA);
		 
		int size = sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
		cv::Point weightpoint( p.x - (size / 2)* cos(angle) + 10 * sin(angle), p.y - (size / 2)* sin(angle) + 10 * cos(angle));
		std::stringstream weightstring; weightstring << weight;
		cv::putText(this->img, weightstring.str(), weightpoint,
			cv::FONT_HERSHEY_TRIPLEX, 0.5, edge.getColor(), 1, CV_AA);


		unsigned int x = p.x - (size / 2)* cos(angle) + 10 * sin(angle), 
					 y = p.y - (size / 2)* sin(angle) + 10 * cos(angle);
		cv::Point *wp;
		list<string> lst = edge.getDecos();
		list<string>::iterator it = lst.begin();
		for(;it != lst.end(); it++){
			wp = new cv::Point(x - (3 * (*it).size() / 2), y += 12);
			cv::putText(this->img, *it, *wp, cv::FONT_HERSHEY_TRIPLEX, 0.30, edge.getColor(), 0.5, 10);
			delete wp;
		}
		
		 
		//Erstes Segment
		p.x = (int) ( q.x + arrowMagnitude * cos(angle + PI/8));
		p.y = (int) ( q.y + arrowMagnitude * sin(angle + PI/8));
		cv::line(img, p, q, color, thickness, CV_AA);
		 
		//Zweites Segment
		p.x = (int) ( q.x + arrowMagnitude * cos(angle - PI/8));
		p.y = (int) ( q.y + arrowMagnitude * sin(angle - PI/8));
		cv::line(img, p, q, color, thickness, CV_AA);
	}
};

#endif