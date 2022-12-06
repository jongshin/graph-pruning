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


void testkPruning();


} // namespace Simulation

