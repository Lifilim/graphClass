#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <set>

enum order { UNORDERED, ORDERED };
enum weight { UNWEIGHTED, WEIGHTED };




template <typename eMarkT>
struct edgeMark {
private: 
	char WM = 0;
	int weight;
	eMarkT mark;

public:
	edgeMark() {}
	edgeMark(std::istream& in, bool isWeighted, bool isMarked) {
		if (isWeighted) in >> weight;
		if (isMarked)   in >> mark;
		WM = int(isWeighted) * 2 + int(isMarked);
	}
	char   getWMFlag() const { return this->WM;     }
	int    getWeight() const { return this->weight; }
	eMarkT getMark()   const { return this->mark;   }

	void output(std::ostream& out) {
		if (WM & 2)	 out << weight;
		if (WM == 3) out << ' ';
		if (WM & 1)	 out << mark;
	}
};
template <typename eMarkT>
bool operator < (const edgeMark<eMarkT>& a, const edgeMark<eMarkT>& b) {
	if ((a.getWMFlag() & 2) && (b.getWMFlag() & 2))
		if (a.getWeight() != b.getWeight())
			return a.getWeight() < b.getWeight();
	if ((a.getWMFlag() & 1) && (b.getWMFlag() & 1))
		return a.getMark() < b.getMark();
	return false;
}

template <typename vertexT, typename eMarkT>
struct edge {
	vertexT from;
	vertexT to;
	edgeMark<eMarkT> marks;

	edge(std::istream& in, bool isWeighted, bool isMarked) {
		in >> this->from >> this->to;
		marks = edgeMark<eMarkT>(in, isWeighted, isMarked);
	}
};


template <typename vertexT, typename eMarkT>
class graph {
private:
	unsigned int vertexCnt = 0;
	unsigned int edgeCnt = 0;
	bool isOrdered = true;
	bool isWeighted = false;
	bool isMarkedInput = false;
	vertexT root;

	std::map<vertexT,
		std::set<std::pair<vertexT,
				 edgeMark<eMarkT>>>> adjacencyList;

public:
	void input(std::istream& in);
	void input() { input(std::cin); }
	void inputAL(std::istream& in);
	void inputAL() { input(std::cin); }

	graph(std::istream& in) {
		in >> this->isOrdered >> this->isWeighted >> this->isMarkedInput;
		input(in);
	}
	graph(bool isOrdered, bool isWeighted, bool isMarkedInput = false) {
		this->isOrdered = isOrdered;
		this->isWeighted = isWeighted;
		this->isMarkedInput = isMarkedInput;
	}
	graph(const graph& g) {
		this->vertexCnt = g.vertexCnt;
		this->edgeCnt = g.edgeCnt;
		this->root = g.root;
		this->isOrdered = g.isOrdered;
		this->isWeighted = g.isWeighted;
		this->adjacencyList = g.adjacencyList;
	}

	void output(std::ostream& out);
	void output() { output(std::cout); }
	void outputAL(std::ostream& out);
	void outputAL() { output(std::cout); }

	unsigned int size() { return this->vertexCnt;  }
	bool   getOrdered() { return this->isOrdered;  }
	bool  getWeighted() { return this->isWeighted; }

	//void scanC();
	//void printC();

	bool add_vertex(vertexT v);
	bool add_edge(edge<vertexT, eMarkT> e);

	bool erase_vertex(vertexT v);
	bool erase_edge(edge<vertexT, eMarkT> e);
};



#include "graphEasier_impl.h"

#endif // GRAPH_H