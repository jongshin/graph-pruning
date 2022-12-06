#pragma once

#include "graph/Graph.hpp"

using namespace myNetwork;

namespace Simulation {

class kPruning final {
public:
    kPruning( Graph&, const Count ); 
    ~kPruning(){}; 
    void run();

    Timestep getPruningDurationTime() const;
    const vector<Count>& getPruningSizeDynamics() const;
    const vector<map<Count,Count>>& getDegreeDistDynamics() const;
private:
    Graph *G;
    Count k;
    Timestep t;
    vector<Count> pruningSize;
    vector<map<Count,Count>> degreeDistribution;
};

class kPruningBipartite final {
public:
    kPruningBipartite( Graph&, const Count, const Count, const Count); 
    ~kPruningBipartite(){}; 
    void run();

    Timestep getPruningDurationTime() const;
    const vector<Count>& getV1PruningSizeDynamics() const;
    const vector<Count>& getV2PruningSizeDynamics() const;
    const vector<map<Count,Count>>& getDegreeDistDynamics() const;
    const vector<map<Count,Count>>& getEdgeSizeDistDynamics() const;

private:
    Graph *G;
    Count nNodes, k,q;
    Timestep t;
    vector<Count> V1PruningSize,V2PruningSize;
    vector<map<Count,Count>> degreeDistribution,edgeSizeDistribution;
};

class GreedyLeafRemoval final {
public:
    GreedyLeafRemoval( Graph& ); 
    ~GreedyLeafRemoval(){}; 
    void run();

    Timestep getPruningDurationTime() const;
    const vector<Count>& getPruningSizeDynamics() const;
    const vector<map<Count,Count>>& getDegreeDistDynamics() const;
private:
    Graph *G;
    Timestep t;
    vector<Count> pruningSize;
    vector<map<Count,Count>> degreeDistribution;
};


class BipartiteGLR final {
public:
    BipartiteGLR( Graph& ); 
    ~BipartiteGLR(){}; 
    void run();

    Timestep getPruningDurationTime() const;
    const vector<Count>& getPruningSizeDynamics() const;
    const vector<map<Count,Count>>& getDegreeDistDynamics() const;
private:
    Graph *G;
    Timestep t;
    vector<Count> pruningSize;
    vector<map<Count,Count>> degreeDistribution;
};


BipartiteGLR::GreedyLeafRemoval( Graph& G )
:   G(&G), t(0) {}

void BipartiteGLR::run() {
    
    Count N = G->numberOfNodes();
    Count numPrunedVertices = 1;

    while( G->numberOfNodes() && numPrunedVertices ) {
        map<Count,Count> currentDegreeDist;
        set<Node> forthcomingRemoval;

        numPrunedVertices = 0;
        for ( Node v=0; v<N; ++v) {
            ++currentDegreeDist[G->degree(v)];

            if ( !(G->isRemoved(v)) && G->degree(v) == 1 ) {
                forthcomingRemoval.insert(v);
                for ( Node n : G->getNeighborsOf(v) )
                     forthcomingRemoval.insert(n);
                numPrunedVertices+=forthcomingRemoval.size();
            }
        }
        degreeDistribution.push_back(currentDegreeDist);
        pruningSize.push_back(numPrunedVertices);

        for( Node v : forthcomingRemoval )
            G->removeNode(v);
        ++t;
    }
}


Timestep BipartiteGLR::getPruningDurationTime() const {
    return t;
}

const vector<Count>& BipartiteGLR::getPruningSizeDynamics() const {
    return pruningSize;
}

const vector<map<Count,Count>>& BipartiteGLR::getDegreeDistDynamics() const {
    return degreeDistribution;
}


void testkPruning();


} // namespace Simulation

