#pragma once

class WeightedSampler{
public:    
    std::size_t operator()(double a, double b, double c, double d) {
        std::array<double, 4> vec{a, b, c, d};
        std::partial_sum(vec.begin(), vec.end(), vec.begin());     
        return std::distance(vec.begin(), std::lower_bound(vec.begin(), vec.end(), vec.back() * ran()));                
    }

    std::size_t operator()(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
        std::array<double, 9> vec{a, b, c, d, e, f, g, h, i};
        std::partial_sum(vec.begin(), vec.end(), vec.begin());     
        return std::distance(vec.begin(), std::lower_bound(vec.begin(), vec.end(), vec.back() * ran()));                
    }
    std::size_t operator()(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j, double k, double l) {
        std::array<double, 12> vec{a, b, c, d, e, f, g, h, i, j, k, l};
        std::partial_sum(vec.begin(), vec.end(), vec.begin());     
        return std::distance(vec.begin(), std::lower_bound(vec.begin(), vec.end(), vec.back() * ran()));                
    }

    template <class T>
    std::size_t operator()(const T& cont){
        T sortedCont;
        std::partial_sum( cont.begin(), cont.end(), sortedCont.begin() );
        return std::distance(sortedCont.begin(), std::lower_bound(sortedCont.begin(), sortedCont.end(), sortedCont.back() * ran() ) );
    }

    template <class T>
    std::size_t pickInSortedCont(const T& sortedCont){
        return std::distance(sortedCont.begin(), std::lower_bound(sortedCont.begin(), sortedCont.end(), sortedCont.back() * ran() ) );
    }

    template <class T>
    T getPartialSummedCont(const T& cont){
        T sortedCont;
        sortedCont.resize( cont.size() );
        std::partial_sum( cont.begin(), cont.end(), sortedCont.begin() );
        return sortedCont;
    }
private:
    RDouble ran;
};