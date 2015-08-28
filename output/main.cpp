/**
 * code generated by JHelper
 * More info: https://github.com/AlexeyDmitriev/JHelper
 * @author Duc
 */

#include <iostream>
#include <fstream>

#define C11

#ifdef SUBMIT
#define LOGLEVEL 0
#define NDEBUG
#else
#endif

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <stack>
#include <functional>
#include <sstream>
#include <deque>
#include <climits>
#include <cfloat>
#include <bitset>

#ifdef C11

#include <array>
#include <type_traits>
#include <random>
#include <unordered_set>
#include <unordered_map>

#endif

#define for_inc_range(i, x, y) for (auto i = x; i <= y; ++i)

using namespace std;


template<class T>
bool isPalindromic(T x) {
    int n = x;
    int rev = 0;
    while (n > 0) {
        int d = n % 10;
        rev = rev * 10 + d;
        n /= 10;
    }
    return x == rev;
}


class PrimeGenerator {
    vector<bool> prime;
    vector<int> primeList;
    int upper;
public:
    // Generate all primes between 2 and upper
    PrimeGenerator(int upper) {
        assert(upper >= 2);
        this->upper = upper;

        prime.resize(upper + 1);
        for_inc_range(i, 0, upper) {
            prime[i] = true;
        }
        prime[0] = prime[1] = false;
        for (int i = 2; i * i <= upper; ++i) {
            if (prime[i]) {
                for (int j = i * i; j <= upper; j += i) {
                    prime[j] = false;
                }
            }
        }

        for_inc_range(i, 2, upper) {
            if (prime[i]) {
                primeList.push_back(i);
            }
        }
    }

    // O(1)
    bool isPrime(int n) const {
        assert(n <= upper);
        if (n < 2) {
            return false;
        }
        return prime[n];
    }

};

class TaskA {
public:
    void solve(std::istream &in, std::ostream &out) {
        const int BOUND = 2000000;
        PrimeGenerator pg(BOUND);

        int p, q;
        in >> p >> q;

        int nPrime = 0;
        int nPalin = 0;
        vector<double> ratio(BOUND + 1);
        for (int x = 1; x <= BOUND; x++) {
            if (pg.isPrime(x)) {
                nPrime++;
            }
            if (isPalindromic(x)) {
                nPalin++;
            }
            ratio[x] = (double) (nPrime * 1.0) / nPalin;
        }
        for (int x = BOUND; x >= 1; x--) {
            if (ratio[x] * q <= p) {
                out << x << endl;
                return;
            }
        }
        return;
    }
};


int main() {
    TaskA solver;
    std::istream &in(std::cin);
    std::ostream &out(std::cout);
    solver.solve(in, out);
    return 0;
}