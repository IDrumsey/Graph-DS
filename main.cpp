#include "graph.h"

int main() {
	std::cout << "Starting\n";
	graph mygraph;
	mygraph.setBase(mygraph.getNumNodes());
	mygraph.fillBase();
	mygraph.printBase();
	
	mygraph.DijkstrasAlg();
	
	return 0;
}