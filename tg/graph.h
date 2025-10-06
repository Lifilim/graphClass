#pragma once
#include <iostream>
#include <fstream>

#include<map>
#include<set>
//#include<>

//using namespace std;

/*
struct vertex {
    int number;

    vertex() {}
    vertex(int v) : vertex() { this->number = v; }
    vertex(std::istream& in) { in >> number; }
    vertex(vertex* v) { this->number = v->number; }

    void output(std::ostream& out) { out << this->number; }
};
bool operator < (const vertex& a, const vertex& b) {
    return a.number < b.number || a.number;
}
struct markedVertex : vertex {
    std::string mark;

    markedVertex() : vertex() {}
    markedVertex(int v, std::string mark) : vertex(v){ this->mark = mark; }
    markedVertex(std::istream& in) : vertex(in) { in >> mark; }

    void output(std::ostream& out) { out << this->number << ' ' << this->mark; }
};
bool operator < (const markedVertex& a, const markedVertex& b) {
    return a.number < b.number || a.number == b.number && a.mark < b.mark;
}
*/

using vertex = int;

struct edge {
    int key;            //????????????????
    vertex vertexNum;

    edge() {
        static int cnt = 0;
        this->key = cnt++;
        //vertexNum = new vertex(-1);
    }
    edge(vertex v) : edge() { this->vertexNum = v; }

    virtual edge* copy(bool copyVertex = true) {
        edge* res = new edge();
        if (copyVertex)
            res->vertexNum = this->vertexNum; //new vertex(this->vertexNum);
        return res;
    }

    virtual void output(std::ostream& out) { out << this->vertexNum; }


    virtual ~edge() { }
};
bool operator < (const edge& a, const edge& b) {
    return a.vertexNum < b.vertexNum || a.vertexNum;
}

struct weightedEdge : edge {
    int weight;

    weightedEdge() : edge() { }
    //weightedEdge(int w) : edge() { this->weight = w; }
    weightedEdge(vertex v, int w) : edge(v) { this->weight = w; }
    
    edge* copy(bool copyVertex = true) override {       // пересмотреть когда-нибудь
        if (copyVertex) {
            return new weightedEdge(this->vertexNum, this->weight);
        }
        weightedEdge* res = new weightedEdge();
        res->weight = this->weight;
        return res;
    }

    void output(std::ostream& out) override { out << this->vertexNum << ' ' << this->weight; }

    ~weightedEdge() override { }
};
bool operator < (const weightedEdge& a, const weightedEdge& b) {
    return a.vertexNum < b.vertexNum || a.vertexNum == b.vertexNum && a.weight < b.weight;
}

std::pair<vertex, edge*> inputEdge(std::istream& in, bool isWeighted) {
    if (isWeighted) {
        int v, u, w;
        in >> v >> u >> w;
        return { v /* new vertex(v) */, new weightedEdge(u, w)};
    }
    int v, u;
    in >> v >> u;
    return { v /* new vertex(v) */, new edge(u) };
}



class baseGraph {
private:
    unsigned int vertexCnt = 0;
    unsigned int vertexId = 0;
    bool isUnordered = false;
    int root = -1;
    std::map<vertex, std::set<edge*>> adjacencyList;
    //std::map<int, std::string> vertexMark;

public:
    unsigned int size() { return this->vertexCnt; }

    virtual void input(std::istream& in, bool isWeighted = false);
    virtual void input() { input(std::cin); }

    virtual void output(std::ostream& out);
    virtual void output() { output(std::cout); }

    //void scanC();
    //void printC();

    virtual vertex add_vertex(vertex v);
    virtual bool add_edge(vertex v, edge* e);
    
    virtual bool erease_vertex(vertex v);
    virtual bool erease_edge(vertex v, edge* e);
};

class weightedGraph : baseGraph {
public:

    void input(std::istream& in);
    void input() { input(std::cin); }

    void output(std::ostream& out);
    void output() { output(std::cout); }

    //void scanC();
    //void printC();

    vertex add_vertex(vertex  v);
    edge* add_edge(vertex v, edge* e);
    
    void erease_vertex(vertex  v);
    void erease_edge(vertex v, edge* e);
};
class unweightedGraph : baseGraph {
public:

    void input(std::istream& in);
    void input() { input(std::cin); }

    void output(std::ostream& out);
    void output() { output(std::cout); }

    //void scanC();
    //void printC();

    vertex add_vertex(vertex v);
    edge* add_edge(vertex v, edge* e);
    
    void erease_vertex(vertex v);
    void erease_edge(vertex v, edge* e);
};



baseGraph* graphFactory(bool isUnordered, bool isWeighted) {

    return new baseGraph();
};
baseGraph* inputGraphFactory(std::istream& fin) {
    bool isUnordered;
    bool isWeighted = false;
    fin >> isUnordered >> isWeighted;
    return graphFactory(isUnordered, isWeighted);
}






/*
class graph {
private:
    unsigned int cntOfVertices = 0;
    unsigned int vertexId = 0;       //да лааадно, и таааак сойдет
    int root = -1;
    bool isUnordered = false;
    bool isWeighted = false;
    map<int, set<edge>> adjacencyList;
    map<int, string> vertexMark;




private:
    void input(istream& fin);
    
    //   n fu fw           - количество вершин, флаг "неориентированный?", флаг "взвешенный?"
    //   u v {w}           - ребро и {вес} (вершины в 1-индексации)
    

public:
    unsigned int size() {
        return cntOfVertices;
    }

    graph() {}

    graph(istream& fin) {
        input(fin);
    }

    graph(const string& file) {
        ifstream fin(file);
        input(fin);
    }

    graph(const graph& tr) {
        cntOfVertices = tr.cntOfVertices;
        root = tr.root;
        isUnordered = tr.isUnordered;
        isWeighted = tr.isWeighted;
        adjacencyList = tr.adjacencyList;
    }


    int add_vertex(string mark = "") {
        adjacencyList[vertexId];
        vertexMark[vertexId] = mark;
        return vertexId++;
    }
    int add_edge(int u, int v);

};


*/