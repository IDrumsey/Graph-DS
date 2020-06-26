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
	base = new BaseNode[nNodes];
	baseSize = nNodes;
}

void graph::fillBase()
{
	ifstream data("data\\graph.csv");
	if (!data.fail()) {
		string currLine;
		int nNode = 0;
		while(!data.eof()){
			getline(data, currLine);
			int nConn = 0;
			for(char c : currLine){
				if(c != ' ' && c != ',' && !isdigit(c)){
					nConn++;
				}
			}
			base[nNode].arr = new node[nConn];
			base[nNode].size = nConn;
			nConn = 0;
			for(char c : currLine){
				
				if(c != ' ' && c != ',' && !isdigit(c)){
					base[nNode].arr[nConn].letter = c;
					nConn++;
				}
				else if(isdigit(c)){
					base[nNode].arr[nConn - 1].weight = int(c) - 48;
				}
			}
			nNode++;
		}
		
	}
	data.close();
	
	for(int i = 0; i < baseSize; i++){
		base[i].arr[0].weight = 0;
	}
}

void graph::printBase()
{
	for(int i = 0; i < baseSize; i++){
		for(int j = 0; j < base[i].size; j++){
			cout << base[i].arr[j].letter << " ";
			if(base[i].arr[j].weight != 0){
				cout << base[i].arr[j].weight << " ";
			}
		}
		cout << endl;
	}
}

void graph::DijkstrasAlg(){
	graph g = *this;
	DSPA alg(g);
	alg.printTable();
	alg.printVisUnvis();
	
	alg.run(g);
}



DSPA::DSPA(graph g){
	cout << "Available Start Nodes - " << endl;
	table = new dspNode[g.baseSize];
	
	for(int i = 0; i < g.baseSize; i++){
		cout << g.base[i].arr[0].letter << " ";
		unvisited.push_back(g.base[i].arr[0].letter);
		table[i].NodeLetter = g.base[i].arr[0].letter;
		table[i].shortestDistance = 2000000000;
		table[i].prevNode = ' ';
	}
	cout << endl;
	
	cout << "Start Node : ";
	cin >> currNode;
	startNode = currNode;
	
	nRowTable = g.baseSize;
}

void DSPA::printTable(){
	cout << "Node | Shortest Distance from " << startNode << " | Previous Node\n";
	for(int i = 0; i < nRowTable; i++){
		cout << "  " << table[i].NodeLetter << "  |       " << table[i].shortestDistance << "         |         " << table[i].prevNode << endl;
		cout << "------------------------------------------------\n";
	}
}

void DSPA::printVisUnvis(){
	
	cout << "Unvisited : ";
	for(int i = 0; i < unvisited.size(); i++){
		cout << unvisited[i];
		if(i != unvisited.size()-1){
			cout << " | ";
		}
	}

	cout << "\n\nVisited : ";
	
	for(int i = 0; i < visited.size(); i++){
		cout << visited[i];
		if(i != visited.size()-1){
			cout << " | ";
		}
	}
}

bool DSPA::inUnvisited(char c){
	for(char a : unvisited){
		if(a == c)return 1;
	}
	return 0;
}

void DSPA::run(graph g){
	cout << "setting\n";
	currNodeInd = getCurrNodeInd(g, startNode);

	//Make sure each node is currNode
	for(int i = 0; i < nRowTable; i++){
		currNodeInd = getCurrNodeInd(g, table[i].NodeLetter);
		vector<node> neighbors = getNeighbors(g, table[i].NodeLetter);
		int neighInd;
		
		cout << "Current node : " << table[currNodeInd].NodeLetter << endl;
		for(int j = 0; j < neighbors.size(); j++){
			
			//Get index of neighbor in table
			cout << "Current neighbor : " << neighbors[j].letter << " " << neighbors[j].weight << endl;
			
			cout << "nrows : " << nRowTable << endl;
			for(int a = 0; a < nRowTable; a++){
				cout << table[a].NodeLetter << " compare " << neighbors[j].letter << endl;
				if(table[a].NodeLetter == neighbors[j].letter){
					neighInd = a;
					break;
				}
			}
			
			cout << "Distance from start : " << neighbors[j].weight << endl;
			
			table[neighInd].shortestDistance = neighbors[j].weight;
			if(table[neighInd].NodeLetter != neighbors[j]){
				table[neighInd].prevNode = table[currNodeInd].NodeLetter;
			}
			printTable();
			cout << "\n\n\n";
		}
	}
}

int DSPA::getCurrNodeInd(graph g, char c){
	for(int i = 0; i < g.baseSize; i++){
		if(g.base[i].arr[0].letter == c){
			return i;
		}
	}
	return -1;
}

std::vector<node> DSPA::getNeighbors(graph g, char c){
	vector<node> neighbors;
	for(int i = 0; i < g.base[currNodeInd].size; i++){
		cout << g.base[currNodeInd].arr[i].letter << "  " << g.base[currNodeInd].arr[i].weight << endl;
		neighbors.push_back(g.base[currNodeInd].arr[i]);
	}
	return neighbors;
}




