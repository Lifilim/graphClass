#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <set>

enum order { UNORDERED, ORDERED };
enum weight { UNWEIGHTED, WEIGHTED };



template <typename typeVertex, typename typeEdgeMark>
class graph {
private:
	unsigned int vertexCnt = 0;
	bool isOrdered = true;
	bool isWeighted = false;
	bool isMarked = false;
	int root = -1;
private:
	struct edgeMark {
	private: int weight;
	public:	typeEdgeMark mark;

	public: //graph<typeVertex, typeEdgeMark>::
		edgeMark() {}
		edgeMark(std::istream& in) {
			if (isWeighted) in >> this->weight;
			if (isMarked)   in >> this->mark;
		}
		int getWeight() { return weight; }
	};
	friend bool operator < (const edgeMark& a, const edgeMark& b) {
		return a.weight < b.weight || a.weight == b.weight && a.mark < b.mark;
	}

	struct edge {
		typeVertex from;
		typeVertex to;
		edgeMark marks;

		//edge() {}
		edge(std::istream& in) {
			in >> this->from >> this->to;
			marks = edgeMark(in);
		}
	};

private:
	std::map<typeVertex,
		std::set<std::pair<typeVertex,
		edgeMark>>> adjacencyList;

public:
	//graph(order isOrdered, weight isWeighted) {
	graph(bool isOrdered, bool isWeighted) {
		this->isOrdered = isOrdered;
		this->isWeighted = isWeighted;
	}
	graph(const graph& g) {
		this->vertexCnt = g.vertexCnt;
		this->root = g.root;
		this->isOrdered = g.isOrdered;
		this->isWeighted = g.isWeighted;
		this->adjacencyList = g.adjacencyList;
	}

	unsigned int size() { return this->vertexCnt; }

	order getOrdered() { return this->isOrdered; }
	weight getWeighted() { return this->isWeighted; }

	void input(std::istream& in);
	void input() { input(std::cin); }
	
	/*
	virtual void output(std::ostream& out);
	virtual void output() { output(std::cout); }

	//void scanC();
	//void printC();

	edge inputEdge(std::istream& in);
	edge inputEdge() { return inputEdge(std::cin); }

	virtual typeVertex add_vertex(typeVertex v);
	virtual bool add_edge(edge e);

	virtual bool erase_vertex(typeVertex v);
	virtual bool erase_edge(edge e);
	*/
};



#include "graphEasier_impl.h"

#endif // GRAPH_H