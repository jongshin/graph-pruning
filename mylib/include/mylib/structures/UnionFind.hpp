#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

namespace myStructure {
namespace UnionFind {

using Index = int;
using Count = int;

struct UnionFind{
public:
    UnionFind( const Count );
    ~UnionFind(){};
    
    Index findRoot( const Index );
    void merge( const Index , const Index );
    bool isSameSet( const Index , const Index );

    const Count numDisjointSets() const { return nSets; }
    int getSizeOfSet ( const Index i) { return setsize[findRoot(i)];}

public:
    int nSets;
    vector<int> parent, rank, setsize;
};

} // namespace UnionFind
} // namespace myStructure
