#ifndef STATIC_ASSERT_HPP
#define STATIC_ASSERT_HPP

template <bool assertion> struct StaticAssert { };
template<> struct StaticAssert<true> { typedef char assersion_type; };

#define static_assert_concat_(a, b) a##b
#define static_assert_concat(a, b) static_assert_concat_(a, b)
#define static_assert(p) \
    typedef StaticAssert<(p)>::assersion_type \
    static_assert_concat(static_assert_at_line_,__LINE__)


#endif // STATIC_ASSERT_HPP
