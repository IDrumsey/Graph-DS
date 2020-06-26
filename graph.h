#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct node{
	char letter;
	int weight;
};

struct dspNode{
	char NodeLetter;
	long shortestDistance;
	char prevNode;
};


struct BaseNode{
	node* arr;
	int size;
};

class graph
{
public:
	BaseNode* base;
	int baseSize;

	int getNumNodes();
	void setBase(int nNodes);
	void fillBase();
	void printBase();
	
	void DijkstrasAlg();
	
	
};

class DSPA{
	public:
		dspNode * table;
		int nRowTable;
		std::vector<char> unvisited;
		std::vector<char> visited;
		char currNode;
		int currNodeInd;
		char startNode;
		
		DSPA(graph g);
		void printTable();
		void printVisUnvis();
		bool inUnvisited(char c);
		void run(graph g);
		int getCurrNodeInd(graph g, char c);
		std::vector<node> getNeighbors(graph g, char c);
};

