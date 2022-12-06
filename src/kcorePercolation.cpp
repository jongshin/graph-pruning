#include "graph/Graph.hpp"
#include "graph/Generator.hpp"
#include "graph/algorithm/Traversal.hpp"
#include "simulation/Pruning.hpp"

using myNetwork::Count;
using myNetwork::Graph;
using myNetwork::Generator::createERNetwork;
using myNetwork::Traversal::getClusterSizesOfBipartite;
using Simulation::kPruning;

int main (int argc, const char* argv[]) {
    const Count nNodes = std::stoi(argv[1]);
    const double meanDegree = std::stod(argv[2]);
    const Count nEns = std::stoi(argv[3]);
    const Count k = std::stoi(argv[4]);

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(NULL); std::cin.tie(NULL);

    std::cout << std::scientific;
    std::cout.precision(12);

    const Count nEdges = static_cast<Count>(meanDegree*nNodes/2.0);

    double orderParam = 0, susceptibility = 0;
    double orderParamPruned = 0, susceptibilityPruned = 0;

    for(Count i=0; i<nEns; ++i) {
        
        Graph G = createERNetwork( nNodes, nEdges );

        vector<Count> clusterSizes = getClusterSizesOfBipartite(G,nNodes);

        double maxClusterSize = *(std::max_element(std::begin(clusterSizes),std::end(clusterSizes)));
        double currentM = static_cast<double>(maxClusterSize) / nNodes;
        orderParam += currentM;
        susceptibility += currentM*currentM;

        kPruning simulator(G,k);
        simulator.run();

        vector<Count> prunedClusterSizes = getClusterSizesOfBipartite(G,nNodes);
        // cout << prunedClusterSizes.size() << '\n';
        if(prunedClusterSizes.size()>0) {
            double maxPrunedClusterSize = *(std::max_element(std::begin(prunedClusterSizes),std::end(prunedClusterSizes)));
            currentM = static_cast<double>(maxPrunedClusterSize) / nNodes;
            orderParamPruned += currentM;
            susceptibilityPruned += currentM*currentM;
        }
    }
    orderParam /= nEns; susceptibility /= nEns;
    orderParamPruned /= nEns; susceptibilityPruned /= nEns;

    std::cout << meanDegree << '\t' 
    << nEns << '\t' 
    << orderParam << '\t' 
    << (susceptibility - (orderParam*orderParam))*nNodes << '\t' 
    << orderParamPruned << '\t' 
    << (susceptibilityPruned - (orderParamPruned*orderParamPruned))*nNodes << '\n';
    
    return 0;
}