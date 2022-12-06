#pragma once

#include <stack>

#include "graph/Graph.hpp"

using std::stack;

namespace myNetwork{
namespace Centrality{

void Betweenness( Graph& , vector<double>& );
void Load( Graph& G, vector<double>& );

} // namespace Traversal
} // namespace myNetwork
