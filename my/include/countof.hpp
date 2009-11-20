#ifndef COUNTOF_HPP
#define COUNTOF_HPP

// countof.hpp

template <typename T, std::size_t N> char (&countof_helper(T(&)[N]))[N];
#define countof(a) (sizeof(countof_helper(a)))

#endif
