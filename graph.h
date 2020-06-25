#pragma once

#include <iostream>
#include <string>
#include <fstream>


class graph
{
public:
	int** base;
	int baseSize;

	int getNumNodes();
	void setBase(int nNodes);
	void fillBase();
	void printBase();
};

