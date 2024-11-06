// Please refer to https://github.com/qlibs/mp
#include <cstddef>
#include <type_traits>

#define MP_SIZE 16u

enum class id_t : size_t {
};

template <id_t>
struct info {
    constexpr auto friend get(info);
};

template <class T>
struct meta_impl {
    using value_type = T;

#if 1
    template <size_t n = MP_SIZE - 1u>
    static constexpr auto gen() -> size_t {
        if constexpr (n == 0) {
            return 0;
        } else if constexpr (requires { get(info<id_t{n - 1}>{}); }) {
            return n + requires { get(info<id_t{n}>{}); };
        } else {
            return gen<n - 1u>();
        }
    }
#else
    template <size_t left = 0u, size_t right = MP_SIZE - 1u>
    static constexpr auto gen() -> size_t {
        if constexpr (left >= right) {
            return left + requires { get(info<id_t{left}>{}); };
        } else if constexpr (constexpr auto mid = left + (right - left) / 2u;
                             requires { get(info<id_t{mid}>{}); }) {
            return gen<mid + 1u, right>();
        } else {
            return gen<left, mid - 1u>();
        }
    }
#endif

    static constexpr auto id = id_t{gen()};

    constexpr auto friend get(info<id>) {
        return meta_impl{};
    }
};

template <class T>
inline constexpr id_t meta = meta_impl<T>::id;

template <id_t meta>
using type_of = typename decltype(get(info<meta>{}))::value_type;

int main(int argc, char *argv[]) {
    static_assert(static_cast<std::size_t>(meta_impl<char>::id) == 0);

    static_assert(static_cast<std::size_t>(meta_impl<unsigned char>::id) == 1);

    static_assert(static_cast<std::size_t>(meta_impl<short>::id) == 2);

    static_assert(static_cast<std::size_t>(meta_impl<unsigned short>::id) == 3);


    static_assert(std::is_same_v<type_of<static_cast<id_t>(0)>, char>);

    static_assert(std::is_same_v<type_of<static_cast<id_t>(1)>, unsigned char>);

    static_assert(std::is_same_v<type_of<static_cast<id_t>(2)>, short>);

    static_assert(std::is_same_v<type_of<static_cast<id_t>(3)>, unsigned short>);
    return 0;
}