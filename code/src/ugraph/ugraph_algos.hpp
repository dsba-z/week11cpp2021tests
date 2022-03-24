////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Contains implementations of some algorithms for undirected graph.
/// \author     Sergey Shershakov
/// \version    0.1.0
/// \date       21.09.2020
/// \copyright  © Sergey Shershakov 2020.
///             This code is for educational purposes of the course "Algorithms
///             and Data Structures" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///
////////////////////////////////////////////////////////////////////////////////


#ifndef UGRAPH_ALGOS_HPP
#define UGRAPH_ALGOS_HPP

#include <set>
#include <map>
#include <stdexcept>

#include <vector>
#include <algorithm>

#include "lbl_ugraph.hpp"
#include "disj_set.hpp"


/*! ****************************************************************************
 *  \brief Implements priority queue storing Vertex elements together with
 *  associated weights.
 *
 *  \tparam Vertex represents a type for vertices.
 ******************************************************************************/
template<typename Vertex>
class VertexPriorityQueue {
public:
    typedef unsigned int UInt;
    //typedef std::pair<UInt, Vertex> WeightedVertex;
    typedef std::pair<Vertex, UInt> VertexWeight;
    //typedef std::set<WeightedVertex> PQSet;
    typedef std::set<std::pair<UInt, Vertex>> PQSet;
    typedef std::map<Vertex, UInt> PQMap;

public:

    /// For the given vertex \a v sets new weight to \a weight.
    /// If no vertex exists, inserts a new pair (v, weight).
    void set(Vertex v, UInt weight)
    {
        auto it = _pqmap.find(v);
//        if (it == _pqmap.end())
//        {
//            insert(v, weight);
//            return;
//        }

        // erases a corresponding pair in the set and in the map
        if (it != _pqmap.end())
        {
            _pqset.erase({it->second, v});
            _pqmap.erase(it);
        }

        insert(v, weight);
        return;



//        auto it = _pqset.find({oldW, v});
//        if (it != _pqset.end())
//        {
//            _pqset.erase(it);
//        }

//        _pqset.insert({newW, v});
    }

    /// Inserts a new vertex-weight pair w/o checking a presence the same vertex
    /// in a queue. Usefull for initialization.
    void insert(Vertex v, UInt weight)
    {
        _pqset.insert({weight, v});
        _pqmap.insert({v, weight});
    }

    /// Return a pair of vertex-weight for the minimum element. Method does not
    /// remove it from the set.
    ///
    /// If a queue is empty, throws an exception.
    //
    VertexWeight getMin() const
    //WeightedVertex extractMin()
    //VertexWeight extractMin()
    {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");

        auto wv = *(_pqset.begin());
        //_pqset.erase(_pqset.begin());
        //_pqmap.erase(wv.second);

        return { wv.second, wv.first };
    }

//    /// Pops the minimum element of the pq.
//    /// If a queue is empty, throws an exception.
//    void popMin()
//    {
//        if (isEmpty())
//            throw std::out_of_range("Queue is empty");

//        auto wv = *(_pqset.begin());
//        _pqset.erase(_pqset.begin());
//        _pqmap.erase(wv.second);
//    }


    /// Removes the given vertex \a v.
    /// In no such a vertex, throws an exception.
    void remove(Vertex v)
    {
        auto it = _pqmap.find(v);
        if (it == _pqmap.end())
            throw std::invalid_argument("No such vertex in PQ");

        auto wv = *(_pqset.begin());
        _pqset.erase({it->second, v});
        _pqmap.erase(it);
    }

    /// For the given vertex \a v returns associated weight.
    /// In no such a vertex, return false, otherwise true and set \a weight.
    bool getWeight(Vertex v, UInt& weight) const
    {
        auto it = _pqmap.find(v);
        if (it == _pqmap.end())
            return false;
            //throw std::invalid_argument("No such vertex in PQ");

        //return it->second;
        weight = it->second;

        return true;
    }

    //void removeVertex(Vertex v, UInt oldW)

    /// Returns true if the queue is empty.
    bool isEmpty() const
    {
        return (_pqset.size() == 0);
    }

protected:
    PQSet _pqset;
    PQMap _pqmap;
};


/// Finds a MST for the given graph \a g using Prim's algorithm.
template<typename Vertex, typename EdgeLbl>
std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge>
    findMSTPrim(const EdgeLblUGraph<Vertex, EdgeLbl>& g)
{
    // Implement using fast Prim approach
    // For each vertex, need to store the distance from itself to the growing spanning
    // tree, and how to get there

    // some type aliases
    typedef unsigned int UInt;
    //typedef std::pair<UInt, Vertex> WeightedVertex;
    typedef typename VertexPriorityQueue<Vertex>::VertexWeight VertexWeight;
    typedef EdgeLblUGraph<Vertex, EdgeLbl> Graph;
    typedef typename Graph::AdjListCIterPair AdjListCIterPair;
    typedef std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge> SetOfEdges;

    typedef DisjointSetForest<Vertex> DisjointSetForestOfVertices;

    std::map<Vertex, Vertex> previous;      // stores previous vertex in the way
                                            // to the current

    auto vs = g.getVertices();              // gets vertices
    Vertex initVert = (*vs.first);          // initial vertex

    // initialize PQ with vertices
    VertexPriorityQueue<Vertex> pqVertices;
    pqVertices.insert(initVert, 0);

    // now skip the very first
    for(auto it = ++(vs.first); it != vs.second; ++it)
    {
        pqVertices.insert(*it, UInt(-1));
    }

    SetOfEdges res;         // resulting set

    // iterates all over the vertices with lowest marks
    while(!pqVertices.isEmpty())
    {
        VertexWeight vw = pqVertices.getMin();
        Vertex activeVertex = vw.first;
        AdjListCIterPair neighbors = g.getAdjEdges(activeVertex);

        for(auto it = neighbors.first; it != neighbors.second; ++it)
        {
            auto edge = *it;
            //UInt curWeight = pqVertices.getWeight(edge.second);
            UInt curWeight;
            if (pqVertices.getWeight(edge.second, curWeight))   // if not reached
            {
                int newWeight;
                g.getLabel(edge.first, edge.second, newWeight);
                if (curWeight > newWeight)
                {
                    pqVertices.set(edge.second, newWeight);
                    previous[edge.second] = edge.first;
                }
            }

            int b = 0;
        }

        // extract current minimum from PQ and add a edge
        pqVertices.remove(activeVertex);

        auto prevIt = previous.find(activeVertex);
        if (prevIt != previous.end())
            res.insert(Graph::makeNormalizedEdge(prevIt->second, activeVertex));
            //res.insert({*prevIt, vw.first});
            //


        int a = 0;
    }

    return res;
}


///*! ****************************************************************************
// *  \brief Implements union-find structure for representing a forest of
// *  disjoint sets.
// *
// *  Used for efficient implementation of Kruskal algorithm for finding MST for a
// *  graph.
// ******************************************************************************/
////template<>
////class DisjointSetForest {


////};



/// Finds a MST for the given graph \a g using Kruskal's algorithm.
/// Here we consider an efficient implementation with using find-union DS.
template<typename Vertex, typename EdgeLbl>
std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge>
    findMSTKruskal(const EdgeLblUGraph<Vertex, EdgeLbl>& g)
{
    // type aliases for convenience
    typedef EdgeLblUGraph<Vertex, EdgeLbl> Graph;
    typedef typename Graph::Edge Edge;
    typedef std::set<Edge> SetOfEdges;

    typedef typename Graph::VertexIterPair VertexIterPair;
    typedef typename Graph::VertexIter VertexIter;

    typedef std::pair<EdgeLbl, Edge> WeightedEdge;
    typedef std::vector<WeightedEdge> WEdgeVector;

    typedef DisjointSetForest<Vertex> DSFVertices;
    typedef typename DSFVertices::Node DSFNode;
    typedef std::map<Vertex, DSFNode*> Vertex2DSFNode;



    WEdgeVector wedges;

    // enumerate all edges from initial graph
    //auto gedes = g.getEdges();
    typename Graph::EdgeIterPair gedes = g.getEdges();
    for (; gedes.first != gedes.second; ++gedes.first)
    {
        //auto e = *gedes.first;  // edge
        auto e = *gedes.first;  // edge
        EdgeLbl ew;             // edge label
        if (!g.getLabel(e.first, e.second, ew))
            throw std::invalid_argument("Unlabeled edge found");

        wedges.push_back({ew, {e.first, e.second}});
    }

    std::sort(wedges.begin(), wedges.end());

    // create singltones for vertices
    DSFVertices dsf;                    // disjoint-sets        forest
    Vertex2DSFNode verts2nodes;         // map vertex to a node in ^^^

    //g.getVertices()
    VertexIterPair vs = g.getVertices();
    for (VertexIter it = vs.first; it != vs.second; ++it)
    {
        Vertex v = *it;
        DSFNode* vn = dsf.makeSet(v);
        verts2nodes.insert({v, vn});
    }

    SetOfEdges res;

    // iterate over edges in increasing order of their weights
    for (const WeightedEdge& we : wedges)
    {
        Vertex u = we.second.first;
        Vertex v = we.second.second;
        DSFNode* un = dsf.find(verts2nodes[u]);
        DSFNode* vn = dsf.find(verts2nodes[v]);
        if (un != vn)                    // both ends aren't in the same set
        {
            res.insert(Graph::makeNormalizedEdge(u, v));
            dsf.merge(un, vn);
        }
    }

    return res; //EdgeSet();
}


#endif // UGRAPH_ALGOS_HPP
