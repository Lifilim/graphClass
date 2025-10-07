#ifndef GRAPH_IMPL_H
#define GRAPH_IMPL_H

#include "graphEasier.h"
/*
template <typename TV, typename TEM>
edge<TV, TEM> graph<TV, TEM>::inputEdge(std::istream& in) {
    return edgeMark<typeEdgeMark>(in, this->)
}
*/
template <typename TV, typename TEM>
void graph<TV, TEM>::input(std::istream& in) {
    int vCnt, eCnt;
    in >> vCnt >> eCnt;
    for (int i = 0; i < vCnt; ++i) {
        TV vertex;
        in >> vertex;
        add_vertex(vertex);
    }
    for (int i = 0; i < eCnt; ++i) {
        edge<TV, TEM> e(in, this->isWeighted, this->isMarkedInput);
        add_edge(e);
    }
    in >> this->root;
    if (!adjacencyList.count(this->root)) throw std::exception("No such vertex for root\n");
}

template <typename TV, typename TEM>
void graph<TV, TEM>::output(std::ostream& out) {
    out << this->isOrdered << ' ' << this->isWeighted << ' ' << this->isMarkedInput << '\n';
    out << this->vertexCnt << ' ' << this->edgeCnt << '\n';

    for (auto ali : adjacencyList)
        out << ali.first << '\n';
    //out << '\n';
    for (auto ali : adjacencyList)
        for (auto alij : ali.second)
            if (ali.first <= alij.first) {
                out << ali.first << ' ' << alij.first << ' ';
                alij.second.output(out);
                out << '\n';
            }
            else if (!this - isOrdered) {
                out << ali.first << ' ' << alij.first << ' ';
                alij.second.output(out);
                out << '\n';
            }
    out << this->root << '\n';
}
template <typename TV, typename TEM>
void graph<TV, TEM>::inputAL(std::istream& in) {
    adjacencyList.clear();
    in >> isWeighted >> isMarkedInput;
    in >> this->vertexCnt;
    this->edgeCnt = 0;
    for (int i = 0; i < vertexCnt; ++i) {
        TV v;
        int cnt;
        in >> v >> cnt;
        this->edgeCnt += cnt;
        for (int j = 0; j < cnt; ++j) {
            TV u;
            in >> u;
            adjacencyList[v].insert({ u, edgeMark(in, isWeighted, isMarkedInput) });
        }
    }
}
template <typename TV, typename TEM>
void graph<TV, TEM>::outputAL(std::ostream& out) {
    out << isWeighted << ' ' << isMarkedInput << '\n';
    out << adjacencyList.size() << '\n';
    for (auto ali : adjacencyList) {
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
    if (adjacencyList.count(v)) return false;
    adjacencyList[v];
    ++vertexCnt;
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
        auto it = ali.lower_bound({ v, edgeMark<TEM> });
        while (it != ali.end() && (*it).first == v) 
            it = ali.erase(it);
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
