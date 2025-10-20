#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>


class graphBase {
public:
	virtual void inputF(std::istream& in) {} //

	virtual void input(std::istream& in) {}
	virtual void input() { input(std::cin); }
	virtual void inputAL(std::istream& in) {}
	virtual void inputAL() { input(std::cin); }

	virtual void output(std::ostream& out) {}
	virtual void output() { output(std::cout); }
	virtual void outputAL(std::ostream& out) {}
	virtual void outputAL() { output(std::cout); }

	//virtual unsigned int size() { return 0;		}
	virtual bool   getOrdered() { return false; }
	virtual bool  getWeighted() { return false; }
	virtual unsigned int  getEdgeCnt()    { return -1; }
	virtual unsigned int  getVertextCnt() { return -1; }


	virtual bool add_vertex(std::istream& in) { return false; }
	virtual bool add_edge(std::istream& in) { return false; }
	virtual bool erase_vertex(std::istream& in) { return false; }
	virtual bool erase_edge(std::istream& in) { return false; }

	virtual graphBase* copy() { return this; } // nice  B)
	/*
	* да-да, это кринж, g0vноcode и т.д.,
	* но я уже и не знаю как иначе добить template
	* 
	* если есть способ лучше, буду рада узнать о нем
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
	edgeMark(int weight_, eMarkT mark_, bool isWeighted, bool isMarked) {
		if (isWeighted) this->weight = weight_;
		if (isMarked)   this->mark = mark_;
		WM = int(isWeighted) * 2 + int(isMarked);
	}
	char   getWMFlag() const { return this->WM;     }
	int    getWeight() const { return this->weight; }
	eMarkT getMark()   const { return this->mark;   }

	void output(std::ostream& out) const {
		if (WM & 2)	 out << weight;
		if (WM == 3) out << ' ';
		if (WM & 1)	 out << mark;
	}
	~edgeMark() = default;
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
	edge(vertexT from_, vertexT to_, edgeMark<eMarkT> marks_) {
		this->from = from_;
		this->to = to_;
		this->marks = marks_;
	}
	~edge() = default;
};


template <typename vertexT, typename eMarkT>
class graph : public graphBase {
private:
	unsigned int vertexCnt = 0;
	unsigned int edgeCnt = 0;
	bool isOrdered = true;
	bool isWeighted = false;
	bool isMarkedInput = false;
	//vertexT root;

	std::map<vertexT,
		std::set<std::pair<vertexT,
				 edgeMark<eMarkT>>>> adjacencyList;
	std::map<vertexT, int> degIn;

public:

	void input(std::istream& in) override;
	void input() override { input(std::cin); }
	void inputAL(std::istream& in) override;
	void inputAL() override { input(std::cin); }

	void inputF(std::istream& in) override {
		in >> this->isOrdered >> this->isWeighted >> this->isMarkedInput;
		input(in);
	} 

	graph(std::istream& in) {
		inputF(in);
	}
	graph(bool isOrdered, bool isWeighted, bool isMarkedInput = false) {
		this->isOrdered = isOrdered;
		this->isWeighted = isWeighted;
		this->isMarkedInput = isMarkedInput;
	}
	graph(const graph<vertexT, eMarkT>&g);
	graph(const graph<vertexT, eMarkT>* g) : graph(*g) {}

	graphBase* copy() override { return new graph<vertexT, eMarkT>(*this); }

	void output(std::ostream& out) override;
	void output() override { output(std::cout); }
	void outputAL(std::ostream& out) override;
	void outputAL() override { outputAL(std::cout); }

	//unsigned int size() override { return this->vertexCnt;  }
	bool   getOrdered() override { return this->isOrdered;  }
	bool  getWeighted() override { return this->isWeighted; }
	unsigned int getEdgeCnt()    override { return this->edgeCnt;   }
	unsigned int getVertextCnt() override { return this->vertexCnt; }
	std::map<vertexT,
		std::set<std::pair<vertexT,
			     edgeMark<eMarkT>>>> getAdjacencyList() { return adjacencyList; }
	//void scanC();
	//void printC();

	virtual bool add_vertex(vertexT v);
	virtual bool add_edge(edge<vertexT, eMarkT> e);
	virtual bool erase_vertex(vertexT v);
	virtual bool erase_edge(edge<vertexT, eMarkT> e);


	bool add_vertex(std::istream& in) override;
	bool add_edge(std::istream& in) override;
	bool erase_vertex(std::istream& in) override;
	bool erase_edge(std::istream& in) override;



	std::vector<vertexT> getVTotalDegN(int deg);
	void getSimDif(graph<vertexT, eMarkT>& g, bool force = false);
	void getSimDif(graph<vertexT, eMarkT>* g, bool force = false) { getSimDif(*g, force); }
	int getСyclomaticСomplexity();
	graph<vertexT, eMarkT>* MSTPrim();

	~graph() override = default;
};



#include "graphEasier_impl.h"

#endif // GRAPH_H