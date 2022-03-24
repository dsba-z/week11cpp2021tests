///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Testing module for DisjointSet classes.
///
/// © Sergey Shershakov 2020.
///
/// This code is for educational purposes of the course "Algorithms and Data 
/// Structures" provided by the School of Software Engineering of the Faculty 
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////


#include <gtest/gtest.h>

#include "ugraph/disj_set.hpp"


TEST(DisjointSetForest, simplest)
{
}

typedef DisjointSetForest<char> DisjointSetForestOfChar;


TEST(DisjointSetForest, makeSet1)
{
    DisjointSetForestOfChar dsf;

    DisjointSetForestOfChar::Node* n_a = dsf.makeSet('a');
    EXPECT_EQ('a', n_a->getEl());
    EXPECT_TRUE(n_a->getPar() == n_a);
    EXPECT_EQ(0, n_a->getRank());
}


TEST(DisjointSetForest, find1)
{
    DisjointSetForestOfChar dsf;

    DisjointSetForestOfChar::Node* n_a = dsf.makeSet('a');
    DisjointSetForestOfChar::Node* n_a_ = dsf.find(n_a);
    EXPECT_TRUE(n_a == n_a_);
}


TEST(DisjointSetForest, union1)
{
    DisjointSetForestOfChar dsf;

    DisjointSetForestOfChar::Node* na = dsf.makeSet('a');
    DisjointSetForestOfChar::Node* nb = dsf.makeSet('b');
    DisjointSetForestOfChar::Node* nc = dsf.makeSet('c');
    DisjointSetForestOfChar::Node* nd = dsf.makeSet('d');
    DisjointSetForestOfChar::Node* ne = dsf.makeSet('e');
    DisjointSetForestOfChar::Node* nf = dsf.makeSet('f');
    DisjointSetForestOfChar::Node* ng = dsf.makeSet('g');
    DisjointSetForestOfChar::Node* nh = dsf.makeSet('h');

    dsf.merge(nb, nf);
    EXPECT_EQ(0, nb->getRank());
    EXPECT_EQ(1, nf->getRank());
    EXPECT_TRUE(dsf.find(nb) == nf);
    EXPECT_TRUE(dsf.find(nf) == nf);
    EXPECT_FALSE(nb->isRepresentative());
    EXPECT_TRUE(nf->isRepresentative());

    dsf.merge(ng, nc);
    EXPECT_EQ(1, nc->getRank());
    EXPECT_EQ(0, ng->getRank());
    EXPECT_TRUE(dsf.find(ng) == nc);
    EXPECT_TRUE(dsf.find(nc) == nc);

    dsf.merge(nc, nd);
    EXPECT_EQ(1, nc->getRank());
    EXPECT_EQ(0, nd->getRank());
    EXPECT_TRUE(dsf.find(nd) == nc);
    EXPECT_TRUE(dsf.find(nc) == nc);

    dsf.merge(nc, nh);
    EXPECT_EQ(1, nc->getRank());
    EXPECT_EQ(0, nh->getRank());
    EXPECT_TRUE(dsf.find(nh) == nc);
    EXPECT_TRUE(dsf.find(nc) == nc);

    dsf.merge(na, ne);
    EXPECT_EQ(1, ne->getRank());
    EXPECT_EQ(0, na->getRank());
    EXPECT_TRUE(dsf.find(ne) == ne);
    EXPECT_TRUE(dsf.find(na) == ne);

    dsf.merge(na, nf);
    EXPECT_EQ(2, nf->getRank());
    EXPECT_EQ(0, na->getRank());
    EXPECT_TRUE(dsf.find(na) == nf);
    EXPECT_TRUE(dsf.find(nf) == nf);

    dsf.merge(na, ng);
    EXPECT_EQ(2, nf->getRank());
    EXPECT_EQ(0, na->getRank());
    EXPECT_EQ(1, nc->getRank());
    EXPECT_EQ(0, ng->getRank());
    EXPECT_TRUE(nc->getPar() == nf);
    EXPECT_TRUE(dsf.find(na) == nf);
    EXPECT_TRUE(dsf.find(ng) == nf);
}

TEST(DisjointSetForest, pathCompression1)
{
    DisjointSetForestOfChar dsf;

    DisjointSetForestOfChar::Node* na = dsf.makeSet('a');
    DisjointSetForestOfChar::Node* nb = dsf.makeSet('b');
    DisjointSetForestOfChar::Node* nc = dsf.makeSet('c');
    DisjointSetForestOfChar::Node* nd = dsf.makeSet('d');

    // switch pc temporarely off
    dsf.setPathCompression(false);

    EXPECT_TRUE(na->getPar() == na);
    EXPECT_TRUE(nb->getPar() == nb);
    dsf.merge(nb, na);
    EXPECT_TRUE(na->getPar() == na);
    EXPECT_TRUE(nb->getPar() == na);

    dsf.merge(nd, nc);
    EXPECT_TRUE(nc->getPar() == nc);
    EXPECT_TRUE(nd->getPar() == nc);

    dsf.merge(nd, nb);
    EXPECT_TRUE(na->getPar() == na);
    EXPECT_TRUE(nb->getPar() == na);
    EXPECT_TRUE(nc->getPar() == na);
    EXPECT_TRUE(nd->getPar() == nc);

    // switch pc back on
    dsf.setPathCompression(true);
    dsf.find(nd);
    EXPECT_TRUE(na->getPar() == na);
    EXPECT_TRUE(nb->getPar() == na);
    EXPECT_TRUE(nc->getPar() == na);
    EXPECT_TRUE(nd->getPar() == na);
}
