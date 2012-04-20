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

int main() {
    {
        size_t p0[4] = {0, 1, 1, 1};
        size_t p1[4] = {0, 1, 2, 2};

        TEST(andres::matchingPairs(p0, p0+4, p1) == 4);
        TEST(andres::matchingPairs(p0, p0+4, p1, true) == 1);

        TEST(andres::randIndex(p0, p0+4, p1) == 2.0 / 3.0);
        TEST(andres::randIndex(p0, p0+4, p1, true) == 1.0 / 3.0);
        TEST(andres::randIndex(p0, p0+4, p1) == andres::randIndexBruteForce(p0, p0+4, p1));
    }
    {
        size_t p0[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        size_t p1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        TEST(andres::matchingPairs(p0, p0+10, p1) == 0);
        TEST(andres::matchingPairs(p0, p0+10, p1, true) == 0);
        TEST(andres::matchingPairs(p0, p0+10, p1) == andres::matchingPairsBruteForce(p0, p0+10, p1));
        TEST(andres::matchingPairs(p0, p0+10, p1, true) == andres::matchingPairsBruteForce(p0, p0+10, p1, true));

        TEST(andres::randIndex(p0, p0+10, p1) == 0.0);
        TEST(andres::randIndex(p0, p0+10, p1) == andres::randIndexBruteForce(p0, p0+10, p1));
        try {
            andres::randIndex(p0, p0+10, p1, true);
            TEST(false);
        }
        catch(std::runtime_error& e) {
        }

        TEST(andres::variationOfInformation(p0, p0+10, p1, true) == 0.0);
    }
    {
        size_t p0[10] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
        size_t p1[10] = {6, 6, 6, 6, 6, 7, 7, 7, 7, 7};

        TEST(andres::matchingPairs(p0, p0+10, p1) == 45);
        TEST(andres::matchingPairs(p0, p0+10, p1, true) == 10);
        TEST(andres::matchingPairs(p0, p0+10, p1) == andres::matchingPairsBruteForce(p0, p0+10, p1));
        TEST(andres::matchingPairs(p0, p0+10, p1, true) == andres::matchingPairsBruteForce(p0, p0+10, p1, true));

        TEST(andres::randIndex(p0, p0+10, p1) == 1.0);
        TEST(andres::randIndex(p0, p0+10, p1, true) == 1.0);
        TEST(andres::randIndex(p0, p0+10, p1) == andres::randIndexBruteForce(p0, p0+10, p1));
        TEST(andres::randIndex(p0, p0+10, p1, true) == andres::randIndexBruteForce(p0, p0+10, p1, true));

        TEST(andres::variationOfInformation(p0, p0+10, p1) == 0.0)
        TEST(andres::variationOfInformation(p0, p0+10, p1, true) == 0.0)
    }
    {
        size_t p0[10] = {0, 0, 0, 0, 4, 4, 4, 4, 8, 9};
        size_t p1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        TEST(andres::matchingPairs(p0, p0+10, p1) == 33);
        TEST(andres::matchingPairs(p0, p0+10, p1, true) == 9);
        TEST(andres::matchingPairs(p0, p0+10, p1) == andres::matchingPairsBruteForce(p0, p0+10, p1));
        TEST(andres::matchingPairs(p0, p0+10, p1, true) == andres::matchingPairsBruteForce(p0, p0+10, p1, true));

        TEST(andres::randIndex(p0, p0+10, p1) == andres::randIndexBruteForce(p0, p0+10, p1));
        TEST(andres::randIndex(p0, p0+10, p1, true) == andres::randIndexBruteForce(p0, p0+10, p1, true));
    }

    return 0;
}
