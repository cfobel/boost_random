#include <iostream>
#include <boost/assign/list_of.hpp>       // for 'list_of()' and 'ref_list_of()'
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include "RouletteWheel.hpp"


using namespace std ;
using namespace roulette_wheel ;

using boost::assign::list_of;
#define _ boost::format


int main( int argc, char* argv[] ) {
    vector<int> values = list_of(1)(2)(3)(4)(5)(6);
    vector<double> probabilities = list_of(0.5)(0.1)(0.1)(0.1)(0.1)(0.1);

    RouletteWheel<int, double> rw(values, probabilities);

    typedef map<int, int> counts_map;

    counts_map counts;

    int spins = (argc == 2) ? atoi(argv[1]) : 10000;

    for(int i = 0; i < spins; i++) {
        counts[rw.spin()]++;
    }

    cout << _("%d spins (vector initialized):") % spins << endl;
    BOOST_FOREACH(counts_map::value_type &item, counts) {
        cout << _("  [%d]: %.2f") 
                % item.first 
                % ((double)item.second / spins) << endl;
    }


    map<int, double> values_map = boost::assign::map_list_of
                                    (1, 0.5)
                                    (2, 0.1)
                                    (3, 0.1)
                                    (4, 0.1)
                                    (5, 0.1)
                                    (6, 0.1);
    RouletteWheel<int, double> rw_map(values_map);

    counts.clear();
    for(int i = 0; i < spins; i++) {
        counts[rw_map.spin()]++;
    }

    cout << _("%d spins (map initialized):") % spins << endl;
    BOOST_FOREACH(counts_map::value_type &item, counts) {
        cout << _("  [%d]: %.2f") 
                % item.first 
                % ((double)item.second / spins) << endl;
    }

    return 0;
}
