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
    //this->root = g.root;
    this->isOrdered = g.isOrdered;
    this->isWeighted = g.isWeighted;
    this->adjacencyList = g.adjacencyList;
    this->degIn = g.degIn;
}

template <typename TV, typename TEM>
void graph<TV, TEM>::input(std::istream& in) {
    this->adjacencyList.clear();
    this->degIn.clear();

    unsigned int vCnt, eCnt;
    in >> vCnt >> eCnt;
    for (unsigned int i = 0; i < vCnt; ++i) add_vertex(in);
    for (unsigned int i = 0; i < eCnt; ++i) add_edge(in);
}

template <typename TV, typename TEM>
void graph<TV, TEM>::output(std::ostream& out) {
    out << this->isOrdered << ' ' << this->isWeighted << ' ' << this->isMarkedInput << '\n';
    out << this->vertexCnt << ' ' << this->edgeCnt << '\n';

    for (auto &ali : this->adjacencyList)
        out << ali.first << '\n';
    //out << '\n';
    for (auto &ali : this->adjacencyList)
        for (auto &alij : ali.second)
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
    //out << this->root << '\n';
}
template <typename TV, typename TEM>
void graph<TV, TEM>::inputAL(std::istream& in) {
    this->adjacencyList.clear();
    this->degIn.clear(); //!!!!!!!!!!

    in >> this->vertexCnt;
    this->edgeCnt = 0;
    for (unsigned int i = 0; i < this->vertexCnt; ++i) {
        TV v;
        int cnt;
        in >> v >> cnt;
        this->adjacencyList[v];
        this->edgeCnt += cnt;
        for (int j = 0; j < cnt; ++j) {
            TV u;
            in >> u;
            this->adjacencyList[v].insert({ u, edgeMark<TEM>(in, this->isWeighted, this->isMarkedInput) });
            ++degIn[u];
        }
    }
    if (!this->isOrdered) this->edgeCnt = this->edgeCnt / 2;
}
template <typename TV, typename TEM>
void graph<TV, TEM>::outputAL(std::ostream& out) {
    out << this->isOrdered << ' '  << this->isWeighted << ' ' << this->isMarkedInput << '\n';
    out << this->adjacencyList.size();
    for (auto &ali : this->adjacencyList) {
        out << "\n" << ali.first << "  " << ali.second.size() << '\n';
        for (auto &alisj : ali.second) {
            out << "    " << alisj.first << ' ';
            alisj.second.output(out);
            out << "\n";
        }
    }
}


template <typename TV, typename TEM>
bool graph<TV, TEM>::add_vertex(TV v) {
    if (this->adjacencyList.count(v)) return false;
    this->adjacencyList[v];
    ++(this->vertexCnt);
    this->degIn[v] = 0;
    return true;
}

template <typename TV, typename TEM>
bool graph<TV, TEM>::add_edge(edge<TV, TEM> e) {
    if (!adjacencyList.count(e.from) || !adjacencyList.count(e.to))
        throw std::exception("Нет такой вершины"); //("No such vertex");

    bool res = false;
    if (!isOrdered) {
        res = adjacencyList[e.to].insert({ e.from, e.marks }).second || res;
        if (res) ++degIn[e.from];
    }
    if (adjacencyList[e.from].insert({ e.to, e.marks }).second) {
        ++degIn[e.to];
    }
    if (res) ++edgeCnt;
    return res;
}

template <typename TV, typename TEM>
bool graph<TV, TEM>::erase_vertex(TV v) {
    if (!adjacencyList.count(v)) return false;
    for (auto& alvi : adjacencyList[v]) --degIn[alvi.first];
    for (auto &ali : adjacencyList) {
        auto it = ali.second.lower_bound({ v, edgeMark<TEM>()});
        while (it != ali.second.end() && (*it).first == v) {
            //--degIn[it->first];
            it = ali.second.erase(it);
            if (isOrdered) --edgeCnt;
        }
    }
    edgeCnt -= adjacencyList[v].size();
    adjacencyList[v].clear();
    adjacencyList.erase(v);
    degIn.erase(v);
    --vertexCnt;
    return true;
}

template <typename TV, typename TEM>
bool graph<TV, TEM>::erase_edge(edge<TV, TEM> e) {
    bool res = true;
    if (!adjacencyList.count(e.from)) return false;
    std::set<std::pair<TV, edgeMark<TEM>>>* ali = &adjacencyList[e.from];
    auto it = ali->find({ e.to, e.marks });
    if (it == ali->end()) res = res && false; //throw std::exception("No such edge\n");
    else {
        --this->degIn[it->first];
        ali->erase(it);
    }
    if (!this->isOrdered) {
        if (!adjacencyList.count(e.to)) return false;
        std::set<std::pair<TV, edgeMark<TEM>>>* ali = &adjacencyList[e.to];
        auto it = ali->find({ e.from, e.marks });
        if (it == ali->end()) res = res && false; //throw std::exception("No such edge\n");
        else {
            --this->degIn[it->first];
            ali->erase(it);
        }
    }
    if (res) --edgeCnt;
    return res;
}








template <typename TV, typename TEM>
bool graph<TV, TEM>::add_vertex(std::istream& in)  {
    TV v;
    in >> v;
    return this->add_vertex(v);
}
template <typename TV, typename TEM>
bool graph<TV, TEM>::add_edge(std::istream& in) {
    edge<TV, TEM> e(in, this->isWeighted, this->isMarkedInput);
    return this->add_edge(e);
}
template <typename TV, typename TEM>
bool graph<TV, TEM>::erase_vertex(std::istream& in) {
    TV v;
    in >> v;
    return this->erase_vertex(v);
}
template <typename TV, typename TEM>
bool graph<TV, TEM>::erase_edge(std::istream& in) {
    edge<TV, TEM> e(in, this->isWeighted, this->isMarkedInput);
    return this->erase_edge(e);
}



//template <typename TV, typename TEM>
//vector<TV> graph<TV, TEM>::getVTotalDegN(int deg) {
//
//}



template <typename TV, typename TEM>
std::vector<TV> graph<TV, TEM>::getVTotalDegN(int deg) {
    std::vector<TV> res;
    if (!isOrdered) deg = 2ll * deg;
    for (auto vs : adjacencyList) {
        if (vs.second.size() + degIn[vs.first] == deg)
            res.push_back(vs.first);
    }
    return res;
}

template <typename TV, typename TEM>
void graph<TV, TEM>::getSimDif(graph<TV, TEM>& g, bool force) { //I understand, 
    if (this->isOrdered != g.isOrdered && !force)
        throw std::exception("Для симметрической разности графы должны быть ориентированы одинаково"); //("No such vertex");
    else if (force) this->isOrdered = this->isOrdered || g.isOrdered;

    auto ital = this->adjacencyList.begin();
    while (ital != this->adjacencyList.end()) {
        if (g.adjacencyList.count(ital->first) == 0) {
            ital = this->adjacencyList.erase(ital);
            continue;
        }
        auto& gal = g.adjacencyList[ital->first];
        auto its = ital->second.begin();
        while (its != ital->second.end())
            if (gal.find(*its) == gal.end())
                its = ital->second.erase(its);
            else ++its;
        ++ital;
    }
    this->vertexCnt = this->adjacencyList.size();
    this->edgeCnt = 0;
    for (auto& ali : this->adjacencyList) 
        this->edgeCnt += ali.second.size();
}

template <typename TV, typename TEM>
int graph<TV, TEM>::getСyclomaticСomplexity() {
    if (this->isOrdered)
        throw std::exception("Метод реализован только для неориентированных графов");
    std::map<TV, char> used;
    int compCnt = 0;
    for (auto& ali : this->adjacencyList)
        if (!used[ali.first]) {
            ++compCnt;
            std::vector<TV> st;
            st.push_back(ali.first);
            used[st.back()] = 1;
            while (!st.empty()) {
                TV v = st.back();
                st.pop_back();
                for (auto& u : this->adjacencyList[v])
                    if (!used[u.first]) {
                        used[u.first] = 1;
                        st.push_back(u.first);
                    }
            }
        }
        return compCnt + this->edgeCnt - this->vertexCnt;
}


template <typename TV, typename TEM>
graph<TV, TEM>* graph<TV, TEM>::MSTPrim() {
    graph<TV, TEM>* mst = new graph<TV, TEM>(isOrdered, isWeighted, isMarkedInput);
    for (auto& ali : adjacencyList)
        if (mst->adjacencyList.count(ali.first) == 0) {
            mst->add_vertex(ali.first);

            std::set<std::pair<edgeMark<TEM>, std::pair<TV, TV>>> edgesAround;
            for (auto& alij : ali.second)
                edgesAround.insert({ alij.second, {ali.first, alij.first} });

            while (!edgesAround.empty()) {
                while (!edgesAround.empty() && mst->adjacencyList.count(edgesAround.begin()->second.second))
                    edgesAround.erase(edgesAround.begin());
                if (edgesAround.empty()) break;

                mst->add_vertex(edgesAround.begin()->second.second);
                mst->add_edge(edge<TV, TEM>{ edgesAround.begin()->second.first, edgesAround.begin()->second.second, edgesAround.begin()->first});

                TV vert = edgesAround.begin()->second.second;
                edgesAround.erase(edgesAround.begin());
                for (auto alij : adjacencyList[vert])
                    if (mst->adjacencyList.count(alij.first) == 0)
                        edgesAround.insert({ alij.second, {vert, alij.first} });
            }
        }
    return mst;
}

template <typename TV, typename TEM>
std::map<TV, std::pair<weightT, TV>> graph<TV, TEM>::algDijkstra(TV u) {
    std::map<TV, std::pair<weightT, TV>> res;
    std::priority_queue<std::pair<weightT, TV>> pq;
    res[u] = { 0, u };
    pq.push({ 0, u });
    while (!pq.empty()) {
        TV v = pq.top().second;
        weightT d_v = pq.top().first;
        pq.pop();
        if (d_v != res[v].first) continue;

        for (auto edge : adjacencyList[v]) {
            TV to = edge.first;
            weightT w = edge.second.getWeight();
            if (res.count(to) == 0 || res[v].first + w < res[to].first) {
                res[to] = { res[v].first + w, v };
                pq.push({ res[to].first, to });
            }
        }
    }
    return res;
}

template <typename TV, typename TEM>
std::map<TV, std::map<TV, weightT>> graph<TV, TEM>::algFloydWarshall() {
    std::map<TV, std::map<TV, weightT>> res;
    for (auto v : adjacencyList)
        for (auto u : adjacencyList)
            res[v.first][u.first] = INF;
    for (auto v : adjacencyList)
        for (auto vu : v.second)
            res[v.first][vu.first] = vu.second.getWeight();
    for (auto v : adjacencyList)
        res[v.first][v.first] = 0;
    for (auto w : adjacencyList)
        for (auto v : adjacencyList)
            for (auto u : adjacencyList)
                if (res[v.first][w.first] < INF && res[w.first][u.first] < INF)
                    if (res[v.first][u.first] > res[v.first][w.first] + res[w.first][u.first])
                        res[v.first][u.first] = res[v.first][w.first] + res[w.first][u.first];
    return res;
}

template <typename TV, typename TEM>
std::pair<std::map<TV, std::pair<weightT, TV>>, std::pair<TV, bool>> graph<TV, TEM>::algFordBellman(TV s) {
    std::map<TV, std::pair<weightT, TV>> d;
    d[s] = { 0, s };
    std::pair<TV, bool> last;
    for (int i = 0; i < vertexCnt; ++i) {
        last.second = false;
        for (auto v : adjacencyList)
            if (d.count(v.first))
                for (auto u : v.second)
                    if (d.count(u.first) == 0
                        || d[u.first].first > d[v.first].first + u.second.getWeight()) {
                            d[u.first] = { std::max(-INF, d[v.first].first + u.second.getWeight())
                                         , v.first };
                            last = { u.first, true };
                         }
    }
    return { d, last };
}

/*
template <typename TV, typename TEM>
std::pair<std::map<TV, std::pair<weightT, TV>>, std::pair<TV, bool>> graph<TV, TEM>::maxFlow(TV s, TV t) {
    std::vector<edge<TV, weightT>> edges;
    //std::vector<weightT> edgesF;
    std::map<TV, std::vector<unsigned int>> g_;
    std::map<TV, char> used;

    for (auto v : getAdjacencyList)
        for (auto u : v.second) {
            g_[v.first].push_back(edges.size());
            edges.push_back
              ( edge ( v.first, u.first
                     , edgeMark<weightT> (u.second.getWeight(), 0, true, true) );
            
            g_[u.first].push_back(edges.size());
            edges.push_back
              ( edge ( u.first, v.first
                     , edgeMark<weightT> (0, 0, true, true) );
        }


    weightT dfs(TV v, weightT f) {
        if (used[v]) return 0;
        used[v] = 1;
        if (v == t) return f;
        for (auto e : g_[v]) {
            weightT r = edges[e].marks.getWeight() - edges[e].marks.getMark();
            if (abs(r) < eps) continue;
            weightT p = dfs(
        }
    }

}
*/
#endif //GRAPH_IMPL_H
