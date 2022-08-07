#include <iostream>
//#include <math.h>

template<typename U>
static constexpr U gcd(const U a) 
{
	return a;
}

template<typename U>
static constexpr U gcd(U a, U b)
{
    U c;
	while (b) 
	{
		c = b;
		b = a % b;
		a = c;
	}
	return a;
}

template<typename U, typename... Args>
static constexpr U gcd(const U a, const Args... args)
{
    return gcd(a, gcd(args...));
}

template<typename U>
static constexpr U mcm(const U u, const U a)
{
    return u * a / gcd(u, gcd(a));
}

template<typename U, typename... Args>
static constexpr U mcm(const U a, const Args... args)
{
    return a * mcm(args...) / gcd(mcm(args...), a);
}