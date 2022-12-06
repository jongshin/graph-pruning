#include "graph/Generator.hpp"


namespace myNetwork{

namespace Generator{

Graph createERNetwork( const Count nNodes, const Count nEdges ) {
    Graph G;
    G.setNumNodes(nNodes);

    RandomUnsignedIntGenerator randUInt(0,nNodes-1);
    Node v1,v2;
    while ( G.numberOfEdges() < nEdges ) {
        v1=randUInt();
        v2=randUInt();
        if( v1!= v2 && !G.hasEdge(v1,v2) )
            G.addEdge(v1,v2);
    }
    return G;
}

Graph createERBipartite( const Count nNodes1, const Count nNodes2, const Count nEdges ) {
    Graph G;
    G.setNumNodes(nNodes1+nNodes2);

    RandomUnsignedIntGenerator randUInt1(0,nNodes1-1);
    RandomUnsignedIntGenerator randUInt2(0,nNodes2-1);

    Node v1,v2;
    while ( G.numberOfEdges() < nEdges ) {
        v1=randUInt1();
        v2=randUInt2() + nNodes1;
        if( !G.hasEdge(v1,v2) )
            G.addEdge(v1,v2);
    }

    return G;
}

Graph createRandomNetworkByStaticWay( const Count nNodes, const Count nEdges, const vector<double>& weightOfNode) {
    Graph G;
    G.setNumNodes(nNodes);

    seed_seq_from<random_device> seedSource;
    pcg32 randIntGenerator(seedSource);

    discrete_distribution<> WeightedSampler(weightOfNode.begin(),weightOfNode.end());

    Node v1, v2;
    while ( G.numberOfEdges() < nEdges ) {
        v1 = WeightedSampler(randIntGenerator);
        v2 = WeightedSampler(randIntGenerator);
        if( G.hasEdge(v1,v2) ) continue;
        G.addEdge(v1,v2);
    }

    return G;
}

vector<double> createWeightListForSFNetwork( const Count nNodes, const double gamma ) {
    vector<double> weightList;
    for(Node i=0;i<nNodes;++i)
        weightList.emplace_back( pow(i+1,-1./(gamma-1)) );
    return weightList;
}

// 최대한 중요한 코드는 Indentationdl ejfgks rhtdp

Graph createSFERBipartiteByStaticWay( const Count nNodes1, const Count nNodes2, const Count nEdges, const vector<double>& weightOfNode) {
    Graph G;
    G.setNumNodes(nNodes1+nNodes2);
    
    seed_seq_from<random_device> seedSource;
    pcg32 randIntGenerator(seedSource);

    discrete_distribution<> WeightedSampler(weightOfNode.begin(),weightOfNode.end());

    RandomUnsignedIntGenerator randUInt2(0,nNodes2-1);
    Node v1,v2;
    while ( G.numberOfEdges() < nEdges ) {
        v1=WeightedSampler(randIntGenerator);
        v2=randUInt2() + nNodes1;
        if( !G.hasEdge(v1,v2) )
            G.addEdge(v1,v2);
    }

    return G;
}

} // namespace Generator
 
} // namespace myNetwork
