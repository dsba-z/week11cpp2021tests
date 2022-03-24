////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Contains definitions of union-find data structures.
/// \author     Sergey Shershakov
/// \version    0.1.0
/// \date       29.09.2020
/// \copyright  © Sergey Shershakov 2020.
///             This code is for educational purposes of the course "Algorithms
///             and Data Structures" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///
////////////////////////////////////////////////////////////////////////////////


#ifndef DISJ_SET_HPP_
#define DISJ_SET_HPP_

#include <vector>
//#include <set>
//#include <map>
//#include <stdexcept>


/*! ****************************************************************************
 *  \brief Implements union-find structure for representing a forest of
 *  disjoint sets.
 *
 *  \tparam T defines a data type for elements stored by this DS.
 *
 * Used for efficient implementation of Kruskal algorithm for finding MST for a
 *  graph.
 ******************************************************************************/
template <typename T>
class DisjointSetForest {
public:

    typedef unsigned int UInt;

    //--------------------------------------------------------------------------
    /// \brief Node for storing set elements.
    class Node {
        friend class DisjointSetForest;
    public:
        /// Initializing constructor with 2 parameters.
        Node(T el, Node* par, UInt rank = 0)
            : _el(el)
            , _par(par)
            , _rank(rank)
        {
        }

        /// Initializing constructor with 1 parameter.
        Node(T el)
            : Node(el, this)
        {
        }
    public:
        // setters/getters
        T getEl() const { return _el; }
        Node* getPar() const { return _par; }
        UInt getRank() const { return _rank; }

        /// \returns true if the element is the representative
        bool isRepresentative() const { return (_par == this); }

    protected:
        /// Sets the parent for given node for the \a newPar.
        /// Method is accessible only for trusted friends.
        void setPar(Node* newPar)
        {
            _par = newPar;
        }

        /// Sets the rank of the given node for the \a newRank.
        /// Method is accessible only for trusted friends.
        void setRank(UInt newRank)
        {
            _rank = newRank;
        }

    protected:
        T _el;                          ///< Element.
        Node* _par;                     ///< Parent node. If the parent node is
                                        ///< the element ilself, it means it is
                                        ///< the representative of a set.

        UInt _rank;                     ///< Used for rank-by-union statistics.
    }; // class Node
    //--------------------------------------------------------------------------

    /// Type of storage container collecting nodes.
    typedef std::vector<Node*> NodeStorage;

public:
    // Constructors, destructors and all the guys.
    DisjointSetForest(bool pc = true)
        : _doPathCompress(pc)
    {
    }

    ~DisjointSetForest()
    {
        for (auto node : _storage)
            delete node;
    }


public:
    // ADS operations

    /// For the given element, makes a new set containing the only this element
    /// (singleton).
    Node* makeSet(T x)
    {
        Node* newSet = new Node(x);
        _storage.push_back(newSet);

        return newSet;
    }

    /// Find the representative of the provided node.
    Node* find(Node* x)
    {
        if(x->isRepresentative())           // base case
            return x;

        // recursive call (here we have to apply path compression heuristic)
        Node* repr = find(x->getPar());

        if (_doPathCompress)
            x->setPar(repr);                // set new parent


        return repr;
    }

    /// Applies Union by Rank
    Node* merge(Node* x, Node* y)
    {
        Node* rx = find(x);
        Node* ry = find(y);

        if(rx->getRank() <= ry->getRank())
            return mergeIntrn(rx, ry);
        //else
            return mergeIntrn(ry, rx);
    }

    /// Sets path compression flag.
    void setPathCompression(bool pc) { _doPathCompress = pc; }

    /// Returns path compression flag.
    bool doesPathCompression() const { return _doPathCompress; }

protected:

    /// Performs actual union-by-rank, where \a s has smaller rank and \a l has
    /// larger rank
    Node* mergeIntrn(Node* s, Node* l)
    {
        s->setPar(l);

        // if the only ranks are equal, we have to increase the largest tree rank
        UInt lRank = l->getRank();
        if (s->getRank() == lRank)
            l->setRank(lRank + 1);

        return l;
    }

protected:


    /// Storage for nodes. Repository items are automatically deleted by
    /// DisjointSetForest.
    NodeStorage _storage;

    /// true if need do path compression.
    bool _doPathCompress;

}; // class DisjointSetForest


#endif // DISJ_SET_HPP_
