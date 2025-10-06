#include "graph.h"

void baseGraph::input(std::istream& in, bool isWeighted = false){
    int edgeCnt;
    in >> this->vertexCnt >> edgeCnt;
    for (int i = 0; i < edgeCnt; ++i) {
        std::pair<vertex, edge*> e = inputEdge(in, isWeighted);
        add_edge(e.first, e.second);
        if (this->isUnordered) {
            edge* invE = e.second->copy(false);
            invE->vertexNum = e.first;
            add_edge(e.second->vertexNum, invE);
        }
    }
}
void output(std::ostream& out) {
    //!!!!!!!!!!!!!!!!!!
}

vertex baseGraph::add_vertex(vertex v) {
    adjacencyList[v];
    //vertexMark[v] = mark;
    //return vertexId++;
}
bool baseGraph::add_edge(vertex v, edge* e) {
    if (adjacencyList[v].find(e) != adjacencyList[v].end()) 
        return false;
    adjacencyList[v].insert(e);
    return true;
}

bool baseGraph::erease_vertex(vertex v) {
    if (adjacencyList[v].find(e) != adjacencyList[v].end())

    for (auto alvi : adjacencyList[v])
        delete alvi;
    adjacencyList.erase(v);

    for (auto ali : adjacencyList) {
        auto it = adjacencyList[v].begin();
        while (it != adjacencyList[v].end()) {
            if ((*it)->vertexNum == v)
                it = adjacencyList[v].erase(it);
            else ++it;
        }
    }
}
bool baseGraph::erease_edge(vertex v, edge* e) {

}


