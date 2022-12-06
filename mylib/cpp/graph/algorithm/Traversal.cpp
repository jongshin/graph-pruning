#include "graph/algorithm/Traversal.hpp"

namespace myNetwork{
namespace Traversal{


void BFSFrom( Graph& G, const Node s) {
    vector<bool> visit(G.numberOfNodes(),false);
    queue<Node> Q;
    Q.push(s);
    visit[s]=true;
    while(!Q.empty()){
        Node current=Q.front();
        Q.pop();
        for(auto next : G.getNeighborsOf(current) ){
            if(!visit[next]) {
                visit[next]=true;
                Q.push(next);
            }
        }
    }
}

void DFSFrom( Graph& G, const Node s) {
    vector<bool> visit(G.numberOfNodes(),false);
    visit[s]=true;
    // for(Node v=0;v<G.numberOfNodes();++i){
    //     Node next=G[v][i];
    //     if(!visit[next])
    //         DFSFrom(G,next);
    // }
}

vector<Count> getClusterSizes( Graph& G ) {
    Count originalNetworkSize = G.getStatusOfNodes().size();
    vector<Count> clusterSize;
    vector<bool> visit(originalNetworkSize,false);
    queue<Node> Q;

    for (Node start=0; start<originalNetworkSize; ++start) {
        if (!visit[start] && !G.getStatusOfNodes().at(start)) {
            Count size = 0;
            Q.push(start);
            visit[start]=true;
            while(!Q.empty()){
                Node current=Q.front();
                Q.pop();
                ++size;
                for(auto next : G.getNeighborsOf(current)){
                    if(!visit[next] && !G.getStatusOfNodes().at(next)) {
                        visit[next]=true;
                        Q.push(next);
                    }
                }
            }
            clusterSize.push_back(size);
        }
    }

    return clusterSize;
}

vector<Count> getClusterSizesOfBipartite( Graph& G, const Count nNodes ) {
    vector<Count> clusterSize;
    vector<bool> visit(G.numberOfNodes(),false);
    queue<Node> Q;

    for (Node start=0; start<G.numberOfNodes(); ++start) {
        Count size = 0;
        Q.push(start);
        visit[start]=true;
        while(!Q.empty()){
            Node current=Q.front();
            Q.pop();
            if(current<nNodes)
                ++size;
            for(auto next : G.getNeighborsOf(current)){
                if(!visit[next]) {
                    visit[next]=true;
                    Q.push(next);
                }
            }
        }
        clusterSize.push_back(size);
    }

    return clusterSize;
}

} // namespace Traversal
} // namespace myNetwork
