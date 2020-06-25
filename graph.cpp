#include "graph.h"

using namespace std;

int graph::getNumNodes()
{
	int nLines = 0;
	ifstream data("data\\graph.csv");
	if (!data.fail()) {
		string currentLine;
		while (!data.eof()) {
			getline(data, currentLine);
			nLines++;
		}
	}
	data.close();
	return nLines;
}

void graph::setBase(int nNodes)
{
	base = new int*[nNodes];
	baseSize = nNodes;
}

void graph::fillBase()
{
	ifstream data("data\\graph.csv");
	if (!data.fail()) {
		string currLine;
		while (!data.eof()) {
			int nNode = 0;
			int count = 0;
			int connectedNodes = 0;
			getline(data, currLine);
			for (char c : currLine) {
				if (c != ',' && c != ' ') {
					connectedNodes++;
				}
			}
			base[nNode] = new int(connectedNodes);

			for (char c : currLine) {
				if (count != 0 && c != ',' && c != ' ') {
					base[nNode][count] = c;
				}
			}
		}
	}
	data.close();
}

void graph::printBase()
{
	
}
