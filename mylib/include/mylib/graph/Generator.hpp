#pragma once

#include "graph/Graph.hpp"
#include "random/PCG64/pcg_random.hpp"
#include "random/PCG64/pcg_extras.hpp"
#include "random/PCG64/pcg_uint128.hpp"
#include "random/PCG64/RandomNumber.hpp"
// #include "random/XORShift/Random.hpp"


using std::random_device;
using std::discrete_distribution;

using pcg_extras::seed_seq_from;

using SNU::CNRC::RandomUnsignedIntGenerator;

namespace myNetwork{

namespace Generator{

Graph createERNetwork( const Count , const Count );
Graph createRandomNetworkByStaticWay( const Count , const Count , const vector<double>& );

vector<double> createWeightListForSFNetwork( const Count, const double );

Graph createERBipartite( const Count , const Count , const Count ); 
Graph createSFERBipartiteByStaticWay( const Count , const Count , const Count , const vector<double>& );


} // namespace Generator
 
} // namespace myNetwork
