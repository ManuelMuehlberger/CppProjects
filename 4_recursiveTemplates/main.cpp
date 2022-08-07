#include "fibonacci.h"
#include "primes.h"
#include <iostream>

int main() {
    fibonacci<80> fib80;
    fibonacci<42> fib42;
    fibonacci<20, int> fib20;

    //greatest common divisor(gcd) of n numbers
    auto gcdEqualNumbers = gcd(999, 999, 999);
    auto gcdBigNumbers = gcd(6 * 23349822, 6 * 4538972);
    auto gcdManyNumbers = gcd(2349, 285040, 34802, 9573279, 8838, 32367);

    //minimum common multiple (mcm) of n numbers
    auto mcmEqualNumbers = mcm(999, 999, 999);
    auto mcmBigNumbers = mcm(6 * 23349822, 6 * 4538972);
    auto mcmManyNumbers = mcm(2349, 285040, 34802, 9573279, 8838, 32367);

    using namespace std;
    
    cout << "fib(80) is: " << fib80.value << ".\n"
    << "fib(42) is: " << fib42.value << ".\n"
    << "fib(20) is: " << fib20.value << ".\n" << endl;

    cout << "gcd of 999, 999, 999 is: " << gcdEqualNumbers << ".\n"
    << "gcd of 6 * 2349822 (14098932), 6 * 45972 (275832) is: " << gcdBigNumbers << ".\n"
    << "gcd of 2349, 285040, 34802, 9573279, 8838, 32367 is: " << gcdManyNumbers << ".\n" << endl;

    cout << "mcm of 999, 999, 999 is: " << mcmEqualNumbers << ".\n"
    << "mcm of 14098932, 275832 is: " << mcmBigNumbers << ".\n"
    << "mcm of 2349, 285040, 34802, 9573279, 8838, 32367 is: " << mcmManyNumbers << ".\n" << endl;
}