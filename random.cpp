#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

#include <boost/iterator/counting_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/foreach.hpp>


using namespace std ;

boost::mt19937 gen;
typedef boost::counting_iterator<int> _i;
typedef boost::iterator_range<_i> int_range;
#define range boost::make_iterator_range

int main( int argc, char* argv[] ) {
    boost::uniform_int<> dist(0, 100);
    boost::variate_generator<boost::mt19937&, boost::uniform_int<> > die(gen, dist);

    BOOST_FOREACH(int i, range(_i(0), _i(10))) {
        cout << i << ": " << die() << endl;
    }

    return 0;
}
