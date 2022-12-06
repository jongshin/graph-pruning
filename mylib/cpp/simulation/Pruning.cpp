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


kPruningBipartite::kPruningBipartite( Graph& G, const Count nNodes, const Count k, const Count q )
:   G(&G), nNodes(nNodes), k(k), q(q), t(0) {}

void kPruningBipartite::run() {
    
    Count N = G->numberOfNodes();
    Count numPrunedV1 = 1;
    Count numPrunedV2 = 1;

    while( G->numberOfNodes() && ( numPrunedV1 || numPrunedV2 ) ) {
        map<Count,Count> currentDegreeDist;
        map<Count,Count> currentEdgeSizeDist;
        
        vector<Node> forthcomingRemoval;
        numPrunedV1 = 0;
        for ( Node v=0; v<nNodes; ++v) {
            ++currentDegreeDist[G->degree(v)];
            if ( !(G->isRemoved(v)) && G->degree(v) < k ) {
                forthcomingRemoval.push_back(v);
                ++numPrunedV1;
            }
        }
        degreeDistribution.push_back(currentDegreeDist);
        V1PruningSize.push_back(numPrunedV1);

        numPrunedV2 = 0;
        for ( Node v=nNodes; v<N; ++v) {
            ++currentEdgeSizeDist[G->degree(v)];
            if ( !(G->isRemoved(v)) && G->degree(v) < q ) {
                forthcomingRemoval.push_back(v);
                // G->removeNode(v);
                ++numPrunedV2;
            }
        }
        edgeSizeDistribution.push_back(currentEdgeSizeDist);
        V2PruningSize.push_back(numPrunedV2);

        for( Node v : forthcomingRemoval )
            G->removeNode(v);
        ++t;
    }
}

Timestep kPruningBipartite::getPruningDurationTime() const {
    return t;
}

const vector<Count>& kPruningBipartite::getV1PruningSizeDynamics() const {
    return V1PruningSize;
}

const vector<Count>& kPruningBipartite::getV2PruningSizeDynamics() const {
    return V2PruningSize;
}

const vector<map<Count,Count>>& kPruningBipartite::getDegreeDistDynamics() const {
    return degreeDistribution;
}

const vector<map<Count,Count>>& kPruningBipartite::getEdgeSizeDistDynamics() const {
    return edgeSizeDistribution;
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
