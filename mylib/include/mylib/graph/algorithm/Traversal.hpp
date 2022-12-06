#pragma once

#include "graph/Graph.hpp"

namespace myNetwork{
namespace Traversal{

void BFSFrom( Graph&, const Node );
void DFSFrom( Graph&, const Node );

vector<Count> getClusterSizes( Graph& );
vector<Count> getClusterSizesOfBipartite( Graph&, const Count );


} // namespace Traversal
} // namespace myNetwork
