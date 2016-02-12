#include <sstream>
#include <iostream>
#include <stdexcept>

#include "partition-comparison.hxx"

#define TEST(x) \
    if(!(x)) { \
    std::stringstream s; \
    s << #x << " does not hold [line " << __LINE__ << "]"; \
    throw std::logic_error(s.str().c_str()); \
}

// implementation
template<class ITERATOR_0, class ITERATOR_1>
inline size_t
matchingPairsBruteForce
(
    ITERATOR_0 begin0,
    ITERATOR_0 end0,
    ITERATOR_1 begin1,
    const bool ignoreDefaultLabel = false
)
{
    size_t N;
    return matchingPairsBruteForce(begin0, end0, begin1, ignoreDefaultLabel, N);
}

template<class ITERATOR_0, class ITERATOR_1>
size_t
matchingPairsBruteForce
(
    ITERATOR_0 begin0,
    ITERATOR_0 end0,
    ITERATOR_1 begin1,
    const bool ignoreDefaultLabel,
    size_t& N // output: number of elements which have a non-zero label in both partitions
)
{
    typedef typename std::iterator_traits<ITERATOR_0>::value_type Label0;
    typedef typename std::iterator_traits<ITERATOR_1>::value_type Label1;

    size_t AB = 0;
    if(ignoreDefaultLabel) {
        N = 0;
        ITERATOR_1 it1 = begin1;
        for(ITERATOR_0 it0 = begin0; it0 != end0; ++it0, ++it1) {
            if(*it0 != Label0() && *it1 != Label1()) {
                ++N;
                ITERATOR_1 it1b = it1 + 1;
                for(ITERATOR_0 it0b = it0 + 1; it0b != end0; ++it0b, ++it1b) {
                    if(*it0b != Label0() && *it1b != Label1()) {
                        if((*it0 == *it0b && *it1 == *it1b) || (*it0 != *it0b && *it1 != *it1b)) {
                            ++AB;
                        }
                    }
                }
            }
        }
    }
    else {
        N = std::distance(begin0, end0);
        ITERATOR_1 it1 = begin1;
        for(ITERATOR_0 it0 = begin0; it0 != end0; ++it0, ++it1) {
            ITERATOR_1 it1b = it1 + 1;
            for(ITERATOR_0 it0b = it0 + 1; it0b != end0; ++it0b, ++it1b) {
                if( (*it0 == *it0b && *it1 == *it1b) || (*it0 != *it0b && *it1 != *it1b) ) {
                    ++AB;
                }
            }
        }

    }
    return AB;
}

template<class ITERATOR_0, class ITERATOR_1>
inline double
randIndexBruteForce
(
    ITERATOR_0 begin0,
    ITERATOR_0 end0,
    ITERATOR_1 begin1,
    const bool ignoreDefaultLabel = false
)
{
    size_t N;
    const size_t n = matchingPairsBruteForce(begin0, end0, begin1, ignoreDefaultLabel, N);
    if(N == 0) {
        throw std::runtime_error("No element is labeled in both partitions.");
    }
    else {
        return static_cast<double>(n) * 2 / static_cast<double>(N * (N-1));
    }
}

int main() {
    {
        size_t p0[4] = {0, 1, 1, 1};
        size_t p1[4] = {0, 1, 2, 2};

        TEST(andres::RandError<>(p0, p0+4, p1).index() == 2.0 / 3.0);
        TEST(andres::RandError<>(p0, p0+4, p1, true).index() == 1.0 / 3.0);
        TEST(andres::RandError<>(p0, p0+4, p1).index() == randIndexBruteForce(p0, p0+4, p1));
    }
    {
        size_t p0[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        size_t p1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        TEST(andres::RandError<>(p0, p0+10, p1).index() == 0.0);
        TEST(andres::RandError<>(p0, p0+10, p1).index() == randIndexBruteForce(p0, p0+10, p1));
        try {
            andres::RandError<>(p0, p0+10, p1, true).index();
            TEST(false);
        }
        catch(std::runtime_error& e) {
        }

        TEST(andres::VariationOfInformation<>(p0, p0+10, p1, true).value() == 0.0);
    }
    {
        size_t p0[10] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
        size_t p1[10] = {6, 6, 6, 6, 6, 7, 7, 7, 7, 7};

        TEST(andres::RandError<>(p0, p0+10, p1).index() == 1.0);
        TEST(andres::RandError<>(p0, p0+10, p1, true).index() == 1.0);
        TEST(andres::RandError<>(p0, p0+10, p1).index() == randIndexBruteForce(p0, p0+10, p1));
        TEST(andres::RandError<>(p0, p0+10, p1, true).index() == randIndexBruteForce(p0, p0+10, p1, true));

        TEST(andres::VariationOfInformation<>(p0, p0+10, p1).value() == 0.0)
        TEST(andres::VariationOfInformation<>(p0, p0+10, p1, true).value() == 0.0)
    }
    {
        size_t p0[10] = {0, 0, 0, 0, 4, 4, 4, 4, 8, 9};
        size_t p1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        TEST(andres::RandError<>(p0, p0+10, p1).index() == randIndexBruteForce(p0, p0+10, p1));
        TEST(andres::RandError<>(p0, p0+10, p1, true).index() == randIndexBruteForce(p0, p0+10, p1, true));

        TEST(andres::RandError<>(p0, p0+10, p1).index() == andres::RandError<>(p1, p1+10, p0).index());
        TEST(andres::RandError<>(p0, p0+10, p1, true).index() == andres::RandError<>(p1, p1+10, p0, true).index());

        TEST(andres::VariationOfInformation<>(p0, p0+10, p1).value() == andres::VariationOfInformation<>(p1, p1+10, p0).value());
        TEST(andres::VariationOfInformation<>(p0, p0+10, p1, true).value() == andres::VariationOfInformation<>(p1, p1+10, p0, true).value());
    }

    return 0;
}
