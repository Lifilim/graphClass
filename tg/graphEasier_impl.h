#ifndef GRAPH_IMPL_H
#define GRAPH_IMPL_H

#include "graphEasier.h"

template <typename eMarkT>
bool operator < (const edgeMark<eMarkT>& a, const edgeMark<eMarkT>& b) {
    if ((a.getWMFlag() & 2) && (b.getWMFlag() & 2))
        if (a.getWeight() != b.getWeight())
            return a.getWeight() < b.getWeight();
    if ((a.getWMFlag() & 1) && (b.getWMFlag() & 1))
        return a.getMark() < b.getMark();
    return a.getWMFlag() < b.getWMFlag();
    //return false;
}

template <typename TV, typename TEM>
graph<TV, TEM>::graph(const graph& g) {
    this->vertexCnt = g.vertexCnt;
    this->edgeCnt = g.edgeCnt;
    this->root = g.root;
    this->isOrdered = g.isOrdered;
    this->isWeighted = g.isWeighted;
    this->adjacencyList = g.adjacencyList;
}

template <typename TV, typename TEM>
void graph<TV, TEM>::input(std::istream& in) {
    unsigned int vCnt, eCnt;
    in >> vCnt >> eCnt;
    for (unsigned int i = 0; i < vCnt; ++i) {
        TV vertex;
        in >> vertex;
        add_vertex(vertex);
    }
    for (unsigned int i = 0; i < eCnt; ++i) {
        edge<TV, TEM> e(in, this->isWeighted, this->isMarkedInput);
        add_edge(e);
    }
    in >> this->root;
    if (!this->adjacencyList.count(this->root)) 
        throw std::exception("No such vertex for root\n");
}

template <typename TV, typename TEM>
void graph<TV, TEM>::output(std::ostream& out) {
    out << this->isOrdered << ' ' << this->isWeighted << ' ' << this->isMarkedInput << '\n';
    out << this->vertexCnt << ' ' << this->edgeCnt << '\n';

    for (auto ali : this->adjacencyList)
        out << ali.first << '\n';
    //out << '\n';
    for (auto ali : this->adjacencyList)
        for (auto alij : ali.second)
            if (ali.first <= alij.first) {
                out << ali.first << ' ' << alij.first << ' ';
                alij.second.output(out);
                out << '\n';
            }
            else if (!this->isOrdered) {
                out << ali.first << ' ' << alij.first << ' ';
                alij.second.output(out);
                out << '\n';
            }
    out << this->root << '\n';
}
template <typename TV, typename TEM>
void graph<TV, TEM>::inputAL(std::istream& in) {
    this->adjacencyList.clear();
    in >> this->isWeighted >> this->isMarkedInput;
    in >> this->vertexCnt;
    this->edgeCnt = 0;
    for (unsigned int i = 0; i < this->vertexCnt; ++i) {
        TV v;
        int cnt;
        in >> v >> cnt;
        this->edgeCnt += cnt;
        for (int j = 0; j < cnt; ++j) {
            TV u;
            in >> u;
            this->adjacencyList[v].insert({ u, edgeMark<TEM>(in, this->isWeighted, this->isMarkedInput) });
        }
    }
}
template <typename TV, typename TEM>
void graph<TV, TEM>::outputAL(std::ostream& out) {
    out << this->isWeighted << ' ' << this->isMarkedInput << '\n';
    out << this->adjacencyList.size() << '\n';
    for (auto ali : this->adjacencyList) {
        out << ali.first << ' ' << ali.second.size() << ' ';
        for (auto alisj : ali.second) {
            out << alisj.first << ' ';
            alisj.second.output(out);
            out << ' ';
        }
    }
}


template <typename TV, typename TEM>
bool graph<TV, TEM>::add_vertex(TV v) {
    if (this->adjacencyList.count(v)) return false;
    this->adjacencyList[v];
    ++(this->vertexCnt);
    return true;
}

template <typename TV, typename TEM>
bool graph<TV, TEM>::add_edge(edge<TV, TEM> e) {
    if (!adjacencyList.count(e.from) || !adjacencyList.count(e.to))
        throw std::exception("No such vertex\n");

    bool res = false;
    if (!isOrdered)
        res = adjacencyList[e.to].insert({ e.from, e.marks }).second || res;
    res = adjacencyList[e.from].insert({ e.to, e.marks }).second || res;
    if (res) ++edgeCnt;
    return res;
}

template <typename TV, typename TEM>
bool graph<TV, TEM>::erase_vertex(TV v) {
    if (!adjacencyList.count(v)) return false;
    adjacencyList[v].clear();
    adjacencyList.erase(v);
    for (auto ali : adjacencyList) {
        auto it = ali.second.lower_bound({ v, edgeMark<TEM>()});
        while (it != ali.second.end() && (*it).first == v) 
            it = ali.second.erase(it);
    }
    --vertexCnt;
    return true;
}

template <typename TV, typename TEM>
bool graph<TV, TEM>::erase_edge(edge<TV, TEM> e) {
    bool res = true;
    {
        if (!adjacencyList.count(e.from)) return false;
        std::set<std::pair<TV, edgeMark<TEM>>>* ali = &adjacencyList[e.from];
        auto it = ali->find({ e.to, e.marks });
        if (it == ali->end()) res = res && false; //throw std::exception("No such edge\n");
        ali->erase(it);
    }
    if (!this->isOrdered) {
        if (!adjacencyList.count(e.to)) return false;
        std::set<std::pair<TV, edgeMark<TEM>>>* ali = &adjacencyList[e.to];
        auto it = ali->find({ e.from, e.marks });
        if (it == ali->end()) res = res && false; //throw std::exception("No such edge\n");
        ali->erase(it);
    }
    if (res) --edgeCnt;
    return res;
}

#endif //GRAPH_IMPL_H
