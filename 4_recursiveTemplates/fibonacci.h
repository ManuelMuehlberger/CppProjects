// calculate the fibonacci number for the non-type template parameter N that is passed
template<long N, typename T = long>
struct fibonacci 
{
    static constexpr T value = fibonacci<N-1,T>::value + fibonacci<N-2,T>::value;
};

template<typename T>
struct fibonacci<1,T> 
{
    static constexpr T value = 1;
};

template<typename T>
struct fibonacci<0,T> 
{
    static constexpr T value = 0;
};