#include "graph/Graph.hpp"

namespace myNetwork{


Graph::Graph()
:   numNodes(0), numEdges(0) {
}

Graph::Graph( const Count N )
:   numNodes(N), numEdges(0), adjacencyList(N), removedNodes(N,false) {
}

void Graph::setNumNodes( const Count N ) {
    numNodes = N;
    adjacencyList.resize( N );
    removedNodes.clear();
    removedNodes.assign(N,false);
}

void Graph::removeNode( const Index v ) {
    for( Node n : adjacencyList[v]) {
        adjacencyList[n].erase( find(adjacencyList[n].begin() , adjacencyList[n].end() , v ) );
    }
    numEdges -= adjacencyList[v].size();
    adjacencyList[v].clear();
    // vector<int>().swap(adjacencyList[v]);
    removedNodes[v]=true;
    --numNodes;
}

void Graph::addEdge( const Index v1, const Index v2 ) {
    // assert(v1!=v2);
    // assert(!hasEdge(v1,v2));
    // if( v1!=v2 && !hasEdge(v1,v2)) {
    adjacencyList[v1].push_back(v2);
    adjacencyList[v2].push_back(v1);
    ++numEdges;
    // }
}

void Graph::removeEdge( const Index v1, const Index v2 ) {
    // assert(v1!=v2);
    // assert(hasEdge(v1,v2));
    adjacencyList[v1].erase( find(adjacencyList[v1].begin() , adjacencyList[v1].end() , v2 ) );
    adjacencyList[v2].erase( find(adjacencyList[v2].begin() , adjacencyList[v2].end() , v1 ) );
    --numEdges;
}

bool Graph::hasEdge( const Index v1, const Index v2 ) const {
    if(v1<v2)
        return ( find(adjacencyList[v1].begin(), 
                adjacencyList[v1].end(),  
                v2) != adjacencyList[v1].end() );
    
    else
        return ( find(adjacencyList[v2].begin(), adjacencyList[v2].end(),  v1) != adjacencyList[v2].end() );
}

bool Graph::isRemoved( const Index v ) const {
    return removedNodes[v];
}

Count Graph::degree( const Index v ) const {
    return adjacencyList[v].size();
}

const vector<bool>& Graph::getStatusOfNodes() const {
    return this->removedNodes;
}

const vector<Node>& Graph::getNeighborsOf( const Node v ) {
    return this->adjacencyList[v];
}

} // namespace myNetwork