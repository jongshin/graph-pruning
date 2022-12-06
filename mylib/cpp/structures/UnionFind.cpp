#include "structures/UnionFind.hpp"

namespace myStructure {
namespace UnionFind {


UnionFind::UnionFind ( 
    const Count N )
:   nSets(N),
    parent(N),
    rank(N,1),
    setsize(N,1) {
    for( auto i=0; i<N; ++i)
        parent[i]=i;
}

Index UnionFind::findRoot (
    const Index u ) {

    if( u==parent[u] ) 
        return u;

    return parent[u] = findRoot(parent[u]);
}

bool UnionFind::isSameSet ( 
    const Index i, 
    const Index j ) {

    return findRoot(i) == findRoot(j);
}

void UnionFind::merge(int u, int v){
    u=findRoot(u); v=findRoot(v);

    if ( u == v ) 
        return;
    --nSets; 

    int tempsize = setsize[u]+setsize[v];
    setsize[u] = tempsize;
    setsize[v] = tempsize;

    if (rank[u]>rank[v]) 
        parent[v]=parent[u];
    else {
        parent[u]=v;
        if(rank[u] == rank[v]) 
            ++rank[v];
    }
}

} // namespace UnionFind
} // namespace myStructure