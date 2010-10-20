#ifndef ___ROULETTE_WHEEL__HPP___
#define ___ROULETTE_WHEEL__HPP___

#include <map>
#include <vector>
#include <numeric>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/foreach.hpp>

namespace roulette_wheel {

using namespace std;

boost::mt19937 gen;
template <class T, class P>
class RouletteWheel {
    vector<T> values;
    vector<P> probabilities;
    vector<double> cumulative;
    boost::uniform_real<> dist;
public:
    RouletteWheel(vector<T> &values, vector<P> &probabilities) 
            : values(values), probabilities(probabilities) {
        std::partial_sum(probabilities.begin(), probabilities.end(), std::back_inserter(cumulative));
        dist = boost::uniform_real<> (0, cumulative.back());
    }
    RouletteWheel(map<T,P> &values_map) {
        pair<T,P> item;
        BOOST_FOREACH(item, values_map) {
            values.push_back(item.first);
            probabilities.push_back(item.second);
        }
        std::partial_sum(probabilities.begin(), probabilities.end(), std::back_inserter(cumulative));
        dist = boost::uniform_real<> (0, cumulative.back());
    }
    T spin() {
        boost::variate_generator<boost::mt19937&, boost::uniform_real<> > die(gen, dist);
        int idx = std::lower_bound(cumulative.begin(), cumulative.end(), die()) - cumulative.begin();
        return values[idx];
    }
};
}

#endif
