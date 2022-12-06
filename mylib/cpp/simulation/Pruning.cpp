#include "simulation/Pruning.hpp"

namespace Simulation {

kPruning::kPruning( Graph& G, const Count k )
:   G(&G), k(k), t(0) {}

void kPruning::run() {
    
    Count N = G->numberOfNodes();
    Count numPrunedVertices = 1;

    while( G->numberOfNodes() && numPrunedVertices ) {
        map<Count,Count> currentDegreeDist;
        vector<Node> forthcomingRemoval;

        numPrunedVertices = 0;
        for ( Node v=0; v<N; ++v) {
            ++currentDegreeDist[G->degree(v)];

            if ( !(G->isRemoved(v)) && G->degree(v) < k ) {
                forthcomingRemoval.push_back(v);
                ++numPrunedVertices;
            }
        }
        degreeDistribution.push_back(currentDegreeDist);
        pruningSize.push_back(numPrunedVertices);

        for( Node v : forthcomingRemoval )
            G->removeNode(v);
        ++t;
    }
}


Timestep kPruning::getPruningDurationTime() const {
    return t;
}

const vector<Count>& kPruning::getPruningSizeDynamics() const {
    return pruningSize;
}

const vector<map<Count,Count>>& kPruning::getDegreeDistDynamics() const {
    return degreeDistribution;
}



GreedyLeafRemoval::GreedyLeafRemoval( Graph& G )
:   G(&G), t(0) {}

void GreedyLeafRemoval::run() {
    
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


Timestep GreedyLeafRemoval::getPruningDurationTime() const {
    return t;
}

const vector<Count>& GreedyLeafRemoval::getPruningSizeDynamics() const {
    return pruningSize;
}

const vector<map<Count,Count>>& GreedyLeafRemoval::getDegreeDistDynamics() const {
    return degreeDistribution;
}


} // namespace Simulation
