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
    int edgeCnt;
    in >> this->vertexCnt >> edgeCnt;
    for (int i = 0; i < edgeCnt; ++i) {
        edge e(in);
        //this->add_edge(e); //e.first, e.second);
        if (!this->isOrdered) {
            std::swap(e.from, e.to);
            //this->add_edge(e);
        }
    }
};

#endif //GRAPH_IMPL_H
