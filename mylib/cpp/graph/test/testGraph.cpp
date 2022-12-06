#include "graph/Graph.hpp"

#define BOOST_TEST_MODULE TestGraph
#include <boost/test/unit_test.hpp>

namespace myNetwork{

BOOST_AUTO_TEST_CASE( test_edge_additions ) {
    /*
         0
        / \
       /   \
      1 --- 2
      | \  /|
      |  \/ |
      | / \ |
      |/   \|
      3 --- 4
    */

    Graph G(5);
    
    G.addEdge(0,1); G.addEdge(0,2); G.addEdge(1,2); G.addEdge(1,3);
    G.addEdge(1,4); G.addEdge(2,3); G.addEdge(2,4); G.addEdge(3,4);

    BOOST_CHECK( G.numberOfEdges() == 8 );

    BOOST_CHECK( G.hasEdge(0,1) ); BOOST_CHECK( G.hasEdge(0,2) );
    BOOST_CHECK( G.hasEdge(1,2) ); BOOST_CHECK( G.hasEdge(1,3) );
    BOOST_CHECK( G.hasEdge(1,4) ); BOOST_CHECK( G.hasEdge(2,3) );
    BOOST_CHECK( G.hasEdge(2,4) ); BOOST_CHECK( G.hasEdge(3,4) );

    BOOST_CHECK( G.degree(0) == 2);
    BOOST_CHECK( G.degree(1) == 4);
    BOOST_CHECK( G.degree(2) == 4);
    BOOST_CHECK( G.degree(3) == 3);
    BOOST_CHECK( G.degree(4) == 3);
}

BOOST_AUTO_TEST_CASE( test_edge_removals ) {
    /* 
         0                 0
        / \                 \
       /   \                 \
      1 --- 2           1 --- 2
      | \  /|   ---->   | \
      |  \/ |           |  \
      | / \ |           |   \
      |/   \|           |    \
      3 --- 4           3     4 
    */
    Graph G(5);
    
    G.addEdge(0,1); G.addEdge(0,2); G.addEdge(1,2); G.addEdge(1,3);
    G.addEdge(1,4); G.addEdge(2,3); G.addEdge(2,4); G.addEdge(3,4);

    G.removeEdge(0,1); G.removeEdge(2,3); G.removeEdge(2,4); G.removeEdge(3,4); 
    
    BOOST_CHECK( G.numberOfEdges() == 4 );

    BOOST_CHECK( G.hasEdge(0,2) ); BOOST_CHECK( !G.hasEdge(0,1) ); 
    BOOST_CHECK( G.hasEdge(1,2) ); BOOST_CHECK( !G.hasEdge(2,4) );
    BOOST_CHECK( G.hasEdge(1,4) ); BOOST_CHECK( !G.hasEdge(2,3) );
    BOOST_CHECK( G.hasEdge(1,3) ); BOOST_CHECK( !G.hasEdge(3,4) );
}

BOOST_AUTO_TEST_CASE( test_remove_nodes ) {
    /*  By removal of node 1 and node 4,               
         0                 0
        / \                 \
       /   \                 \
      1 --- 2                 2
      | \  /|   ---->        /
      |  \/ |               / 
      | / \ |              / 
      |/   \|             /  
      3 --- 4            3      
     
    */
    
    Graph G(5);
    
    G.addEdge(0,1); G.addEdge(0,2); G.addEdge(1,2); G.addEdge(1,3);
    G.addEdge(1,4); G.addEdge(2,3); G.addEdge(2,4); G.addEdge(3,4);

    G.removeNode(1); G.removeNode(4); 

    BOOST_CHECK( G.hasEdge(0,2) ); BOOST_CHECK( G.hasEdge(2,3) ); 

    BOOST_CHECK( !G.hasEdge(1,2) ); BOOST_CHECK( !G.hasEdge(2,4) );
    BOOST_CHECK( !G.hasEdge(1,4) ); BOOST_CHECK( !G.hasEdge(0,1) );
    BOOST_CHECK( !G.hasEdge(1,3) ); BOOST_CHECK( !G.hasEdge(3,4) );
    
    BOOST_CHECK( G.numberOfNodes() == 3 );
    BOOST_CHECK( G.numberOfEdges() == 2 );

    BOOST_CHECK( G.degree(0) == 1);
    BOOST_CHECK( G.degree(1) == 0);
    BOOST_CHECK( G.degree(2) == 2);
    BOOST_CHECK( G.degree(3) == 1);
    BOOST_CHECK( G.degree(4) == 0);
}

} // namespace myNetwork

