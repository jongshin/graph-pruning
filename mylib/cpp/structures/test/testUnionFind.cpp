#include "structures/UnionFind.hpp"

#define BOOST_TEST_MODULE TestUnionFind
#include <boost/test/included/unit_test.hpp> 

namespace myStructure {
namespace UnionFind {
BOOST_AUTO_TEST_CASE( first_test ) { 
  
    UnionFind UF(8);
    UF.merge(1,3);
    BOOST_CHECK ( UF.isSameSet(1,3) );
    BOOST_CHECK ( !UF.isSameSet(1,7) );

    UF.merge(7,6);
    BOOST_CHECK ( UF.isSameSet(1,3) );
    BOOST_CHECK ( !UF.isSameSet(1,6) );
    BOOST_CHECK ( !UF.isSameSet(1,7) );
    BOOST_CHECK ( UF.isSameSet(6,7) );

    UF.merge(3,7);
    UF.merge(4,1);
    UF.merge(1,1);
    BOOST_CHECK ( UF.isSameSet(1,1) );
    BOOST_CHECK ( UF.isSameSet(7,1) );
}


BOOST_AUTO_TEST_CASE( second_test ) { 

    UnionFind UF(5);
    UF.merge(1,2);
    BOOST_CHECK ( UF.getSizeOfSet(1)==2 );
    UF.merge(2,3);
    BOOST_CHECK ( UF.getSizeOfSet(2)==3 );
    UF.merge(3,4);
    BOOST_CHECK ( UF.getSizeOfSet(3)==4 );


    UnionFind UF2(5);
    UF2.merge(1,2);
    BOOST_CHECK ( UF2.getSizeOfSet(1)==2 );
    UF2.merge(3,4);
    BOOST_CHECK ( UF2.getSizeOfSet(3)==2 );
    UF2.merge(2,3);
    BOOST_CHECK ( UF2.getSizeOfSet(2)==4);

}
}
}