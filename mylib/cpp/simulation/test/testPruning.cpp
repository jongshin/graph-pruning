#include "simulation/Pruning.hpp"

#define BOOST_TEST_MODULE TestPruning
#include <boost/test/unit_test.hpp>

namespace Simulation{

BOOST_AUTO_TEST_CASE( test_2_Pruning ) {
    /*
               6 - 7                     6 - 7                  6 - 7 
                \ /                       \ /                    \ /
            3 -- 4--8                 3 -- 4--8              3 -- 4--8
            | \/ | / \                | \/ | /               | \/ | /
            | /\ |/   9       -->     | /\ |/          -->   | /\ |/     
       0 -- 1 -- 5                    1 -- 5                 1 -- 5
            |    |                         |
            |    |                         |
            2    10 -- 11                  10
    */  
    // Test graph
    Graph G(12);

    G.addEdge(0,1); G.addEdge(1,2); G.addEdge(1,3); G.addEdge(1,4);
    G.addEdge(1,5); G.addEdge(3,4); G.addEdge(3,5); G.addEdge(4,5);
    G.addEdge(4,6); G.addEdge(4,7); G.addEdge(4,8); G.addEdge(5,8);
    G.addEdge(5,10); G.addEdge(6,7); G.addEdge(8,9); G.addEdge(10,11);

    BOOST_CHECK( G.numberOfNodes() == 12 );
    BOOST_CHECK( G.numberOfEdges() == 16 );

    kPruning simulator(G,2);
    simulator.run();

    BOOST_CHECK( simulator.getPruningDurationTime() == 3 );

    vector<Count> Pa = simulator.getPruningSizeDynamics();
    BOOST_CHECK( Pa[0] == 4 ); BOOST_CHECK( Pa[1] == 1 ); BOOST_CHECK( Pa[2] == 0 );

    vector<map<Count,Count>> Pd = simulator.getDegreeDistDynamics();
    BOOST_CHECK( Pd[0][1] == 4 ); BOOST_CHECK( Pd[0][2] == 3 ); BOOST_CHECK( Pd[0][3] == 2 ); BOOST_CHECK( Pd[0][5] == 2 ); BOOST_CHECK( Pd[0][6] == 1 );
    BOOST_CHECK( Pd[1][0] == 4 ); BOOST_CHECK( Pd[1][1] == 1 ); BOOST_CHECK( Pd[1][2] == 3 ); BOOST_CHECK( Pd[1][3] == 2 ); BOOST_CHECK( Pd[1][5] == 1 ); BOOST_CHECK( Pd[1][6] == 1 );
    BOOST_CHECK( Pd[2][0] == 5 ); BOOST_CHECK( Pd[2][2] == 3 ); BOOST_CHECK( Pd[2][3] == 2 ); BOOST_CHECK( Pd[2][4] == 1 ); BOOST_CHECK( Pd[2][6] == 1 );

    BOOST_CHECK( G.isRemoved(0) );
    BOOST_CHECK( G.isRemoved(2) );
    BOOST_CHECK( G.isRemoved(9) );
    BOOST_CHECK( G.isRemoved(10) );
    BOOST_CHECK( G.isRemoved(11) );

    BOOST_CHECK( G.degree(1) == 3 );
    BOOST_CHECK( G.degree(3) == 3 );
    BOOST_CHECK( G.degree(4) == 6 );
    BOOST_CHECK( G.degree(5) == 4 );
    BOOST_CHECK( G.degree(6) == 2 );
    BOOST_CHECK( G.degree(7) == 2 );
    BOOST_CHECK( G.degree(8) == 2 );

    BOOST_CHECK( G.numberOfNodes() == 7 );
    BOOST_CHECK( G.numberOfEdges() == 11 );
}

BOOST_AUTO_TEST_CASE( test_3_Pruning ) {
    /*
               6 - 7                     
                \ /                        
            3 -- 4--8                 3 -- 4--8            3 -- 4
            | \/ | / \                | \/ | /             | \/ | 
            | /\ |/   9       -->     | /\ |/      -->     | /\ |
       0 -- 1 -- 5                    1 -- 5               1 -- 5 
            |    |
            |    |
            2    10 -- 11  
    */  
    Graph G(12);

    G.addEdge(0,1); G.addEdge(1,2); G.addEdge(1,3); G.addEdge(1,4);
    G.addEdge(1,5); G.addEdge(3,4); G.addEdge(3,5); G.addEdge(4,5);
    G.addEdge(4,6); G.addEdge(4,7); G.addEdge(4,8); G.addEdge(5,8);
    G.addEdge(5,10); G.addEdge(6,7); G.addEdge(8,9); G.addEdge(10,11);

    BOOST_CHECK( G.numberOfNodes() == 12 );
    BOOST_CHECK( G.numberOfEdges() == 16 );

    kPruning simulator(G,3);
    simulator.run();

    BOOST_CHECK( simulator.getPruningDurationTime() == 3 );

    vector<Count> Pa = simulator.getPruningSizeDynamics();
    BOOST_CHECK( Pa[0] == 7 ); BOOST_CHECK( Pa[1] == 1 ); BOOST_CHECK( Pa[2] == 0 );

    vector<map<Count,Count>> Pd = simulator.getDegreeDistDynamics();
    BOOST_CHECK( Pd[0][1] == 4 ); BOOST_CHECK( Pd[0][2] == 3 ); BOOST_CHECK( Pd[0][3] == 2 ); BOOST_CHECK( Pd[0][5] == 2 ); BOOST_CHECK( Pd[0][6] == 1 );
    BOOST_CHECK( Pd[1][0] == 7 ); BOOST_CHECK( Pd[1][2] == 1 ); BOOST_CHECK( Pd[1][3] == 2 ); BOOST_CHECK( Pd[1][4] == 2 ); 
    BOOST_CHECK( Pd[2][0] == 8 ); BOOST_CHECK( Pd[2][3] == 4 );

    BOOST_CHECK( G.numberOfNodes() == 4 );
    BOOST_CHECK( G.numberOfEdges() == 6 );

    BOOST_CHECK( G.isRemoved(0) );
    BOOST_CHECK( G.isRemoved(2) );
    BOOST_CHECK( G.isRemoved(6) );
    BOOST_CHECK( G.isRemoved(7) );
    BOOST_CHECK( G.isRemoved(8) );
    BOOST_CHECK( G.isRemoved(9) );
    BOOST_CHECK( G.isRemoved(10) );
    BOOST_CHECK( G.isRemoved(11) );

    BOOST_CHECK( G.degree(1) == 3 );
    BOOST_CHECK( G.degree(3) == 3 );
    BOOST_CHECK( G.degree(4) == 3 );
    BOOST_CHECK( G.degree(5) == 3 );
}


BOOST_AUTO_TEST_CASE( test_GLR ) {
    /*            
       0                6           6      
       |               /|          /|    
       2 -- 3 -- 4 -- 5 |   -->   5 |
       |               \|          \|            
       1                7           7               
    */  
    Graph G(8);

    G.addEdge(0,2); G.addEdge(1,2); G.addEdge(2,3); G.addEdge(3,4);
    G.addEdge(4,5); G.addEdge(5,6); G.addEdge(5,7); G.addEdge(6,7);
   
    BOOST_CHECK( G.numberOfNodes() == 8 );
    BOOST_CHECK( G.numberOfEdges() == 8 );

    GreedyLeafRemoval simulator(G);
    simulator.run();

    // BOOST_CHECK( simulator.getPruningDurationTime() == 3 );

    // vector<Count> Pa = simulator.getPruningSizeDynamics();
    // BOOST_CHECK( Pa[0] == 4 ); BOOST_CHECK( Pa[1] == 1 ); BOOST_CHECK( Pa[2] == 0 );

    // vector<map<Count,Count>> Pd = simulator.getDegreeDistDynamics();
    // BOOST_CHECK( Pd[0][1] == 4 ); BOOST_CHECK( Pd[0][2] == 3 ); BOOST_CHECK( Pd[0][3] == 2 ); BOOST_CHECK( Pd[0][5] == 2 ); BOOST_CHECK( Pd[0][6] == 1 );
    // BOOST_CHECK( Pd[1][0] == 4 ); BOOST_CHECK( Pd[1][1] == 1 ); BOOST_CHECK( Pd[1][2] == 3 ); BOOST_CHECK( Pd[1][3] == 2 ); BOOST_CHECK( Pd[1][5] == 1 ); BOOST_CHECK( Pd[1][6] == 1 );
    // BOOST_CHECK( Pd[2][0] == 5 ); BOOST_CHECK( Pd[2][2] == 3 ); BOOST_CHECK( Pd[2][3] == 2 ); BOOST_CHECK( Pd[2][4] == 1 ); BOOST_CHECK( Pd[2][6] == 1 );

    BOOST_CHECK( G.isRemoved(0) );
    BOOST_CHECK( G.isRemoved(1) );
    BOOST_CHECK( G.isRemoved(2) );
    BOOST_CHECK( G.isRemoved(3) );
    BOOST_CHECK( G.isRemoved(4) );

    BOOST_CHECK( G.degree(5) == 2 );
    BOOST_CHECK( G.degree(6) == 2 );
    BOOST_CHECK( G.degree(7) == 2 );

    BOOST_CHECK( G.numberOfNodes() == 3 );
    BOOST_CHECK( G.numberOfEdges() == 3 );
}

} // namespace Simulation


