#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <set>

//enum order { UNORDERED, ORDERED };
//enum weight { UNWEIGHTED, WEIGHTED };


class graphBase {
public:
	virtual void input(std::istream& in) {}
	virtual void input() { input(std::cin); }
	virtual void inputAL(std::istream& in) {}
	virtual void inputAL() { input(std::cin); }

	virtual void output(std::ostream& out) {}
	virtual void output() { output(std::cout); }
	virtual void outputAL(std::ostream& out) {}
	virtual void outputAL() { output(std::cout); }

	virtual unsigned int size() { return 0;		}
	virtual bool   getOrdered() { return false; }
	virtual bool  getWeighted() { return false; }
	/*
	bool add_vertex(vertexT v);
	bool add_edge(edge<vertexT, eMarkT> e);

	bool erase_vertex(vertexT v);
	bool erase_edge(edge<vertexT, eMarkT> e);
	*/
	virtual ~graphBase() = default;
};



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
class graph : public graphBase {
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
	void input(std::istream& in) override;
	void input() override { input(std::cin); }
	void inputAL(std::istream& in) override;
	void inputAL() override { input(std::cin); }

	graph(std::istream& in) {
		in >> this->isOrdered >> this->isWeighted >> this->isMarkedInput;
		input(in);
	}
	graph(bool isOrdered, bool isWeighted, bool isMarkedInput = false) {
		this->isOrdered = isOrdered;
		this->isWeighted = isWeighted;
		this->isMarkedInput = isMarkedInput;
	}
	graph(const graph& g);

	void output(std::ostream& out) override;
	void output() override { output(std::cout); }
	void outputAL(std::ostream& out) override;
	void outputAL() override { output(std::cout); }

	unsigned int size() override { return this->vertexCnt;  }
	bool   getOrdered() override { return this->isOrdered;  }
	bool  getWeighted() override { return this->isWeighted; }

	//void scanC();
	//void printC();

	virtual bool add_vertex(vertexT v);
	virtual bool add_edge(edge<vertexT, eMarkT> e);

	virtual bool erase_vertex(vertexT v);
	virtual bool erase_edge(edge<vertexT, eMarkT> e);

	~graph() override = default;
};



#include "graphEasier_impl.h"

#endif // GRAPH_H