#include <tuple>
#include <utility>

template <class T, class U>
constexpr auto &&std_forward_like(U &&x) noexcept {
    constexpr bool is_adding_const = std::is_const_v<std::remove_reference_t<T>>;
    if constexpr (std::is_lvalue_reference_v<T &&>) {
        if constexpr (is_adding_const) {
            return std::as_const(x);
        } else {
            return static_cast<U &>(x);
        }
    } else {
        if constexpr (is_adding_const) {
            return std::move(std::as_const(x));
        } else {
            return std::move(x);
        }
    }
}

template <typename T, typename U>
constexpr auto &&forward_like_tuple(auto &&u) noexcept {
    constexpr auto is_const_this = std::is_const_v<std::remove_reference_t<T>>;
    if constexpr (std::is_lvalue_reference_v<T>) {
        if constexpr (is_const_this) {
            return static_cast<const U &>(u);
        } else {
            return static_cast<U &>(u);
        }
    } else {
        if constexpr (is_const_this) {
            return static_cast<const U &&>(u);
        } else {
            return static_cast<U &&>(u);
        }
    }
}

template <typename T = int>
struct xxx_tuple {
    T m;
};

using m_t = int;

#define TEST(_o_, _m_, _merge_, _tuple_, _language_)                                               \
    static_assert(std::is_same_v<                                                                  \
                  decltype(std_forward_like<xxx_tuple<> _o_>(std::declval<m_t _m_>())),            \
                  m_t _merge_>);                                                                   \
    static_assert(std::is_same_v<                                                                  \
                  decltype(std::get<0>(std::declval<std::tuple<m_t _m_> _o_>())),                  \
                  m_t _tuple_>);                                                                   \
    static_assert(std::is_same_v<                                                                  \
                  decltype(forward_like_tuple<xxx_tuple<> _o_, m_t _m_>(std::declval<m_t _m_>())), \
                  m_t _tuple_>);                                                                   \
    static_assert(                                                                                 \
        std::is_same_v<                                                                            \
            decltype((                                                                             \
                std::forward<xxx_tuple<m_t _m_> _o_>(std::declval<xxx_tuple<m_t _m_> _o_>()).m)),  \
            m_t _language_>);

void test() {
    // clang-format off
    //   Owner   , Member  , Merge   , Tuple   , Language
    TEST(        ,         , &&      , &&      , &&      );
    TEST(&       ,         , &       , &       , &       );
    TEST(&&      ,         , &&      , &&      , &&      );
    TEST(const   ,         , const &&, const &&, const &&);
    TEST(const & ,         , const & , const & , const & );
    TEST(const &&,         , const &&, const &&, const &&);
    TEST(        , const   , const &&, const &&, const &&);
    TEST(&       , const   , const & , const & , const & );
    TEST(&&      , const   , const &&, const &&, const &&);
    TEST(const   , const   , const &&, const &&, const &&);
    TEST(const & , const   , const & , const & , const & );
    TEST(const &&, const   , const &&, const &&, const &&);
    TEST(&       , &       , &       , &       , &       );
    TEST(&       , &&      , &       , &       , &       );
    TEST(&       , const & , const & , const & , const & );
    TEST(&       , const &&, const & , const & , const & );
    TEST(const & , const & , const & , const & , const & );
    TEST(const & , const &&, const & , const & , const & );
    TEST(        , &       , &&      , &       , &       );
    TEST(&&      , &       , &&      , &       , &       );
    TEST(const   , &       , const &&, &       , &       );
    TEST(const & , &       , const & , &       , &       );
    TEST(const &&, &       , const &&, &       , &       );
    TEST(        , &&      , &&      , &&      , &       );
    TEST(&&      , &&      , &&      , &&      , &       );
    TEST(const   , &&      , const &&, &&      , &       );
    TEST(const & , &&      , const & , &       , &       );
    TEST(const &&, &&      , const &&, &&      , &       );
    TEST(        , const & , const &&, const & , const & );
    TEST(&&      , const & , const &&, const & , const & );
    TEST(const   , const & , const &&, const & , const & );
    TEST(const &&, const & , const &&, const & , const & );
    TEST(        , const &&, const &&, const &&, const & );
    TEST(&&      , const &&, const &&, const &&, const & );
    TEST(const   , const &&, const &&, const &&, const & );
    TEST(const &&, const &&, const &&, const &&, const & );
    // clang-format on
}

int main(int argc, char *argv[]) {
    return 0;
}