#ifndef STATIC_IF_HPP
#define STATIC_IF_HPP

template <bool condition, typename Then, typename Else>
struct static_if 
{ 
typedef Then Type;
};

template <typename Then, typename Else>
struct static_if <false, Then, Else>
{ 
typedef Else Type;
};

#endif
