#pragma once

#include "stdafx.h"

namespace myNetwork {

using Index = UInt;
using Node = UInt;
using Count = UInt;

// constexpr double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;

class Graph {
public:
    Graph();
    Graph( const Count );
    ~Graph(){}

    void setNumNodes( const Count );
    void removeNode( const Index );

    void addEdge( const Index, const Index );
    void removeEdge( const Index, const Index );

    bool hasEdge( const Index, const Index ) const;
    bool isRemoved( const Index ) const;

    Count degree( const Node ) const ;
    Count numberOfNodes() const { return numNodes; }
    Count numberOfEdges() const { return numEdges; }

    const vector<bool>& getStatusOfNodes() const;
    const vector<Node>& getNeighborsOf( const Index );

private:
    Count numNodes, numEdges;
    vector<vector<Node>> adjacencyList;
    vector<bool> removedNodes;

};

void testGraph();
}// namespace myNetwork


