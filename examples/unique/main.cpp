#include <cstdint>
#include <type_traits>

struct empty { };

template <bool C>
struct apple {
    [[no_unique_address]] std::conditional_t<C, int, empty> sn;
    std::uint64_t weight;
};

static_assert(sizeof(apple<true>) == 16);
static_assert(sizeof(apple<false>) == 8);

//.................................................................................................
struct one_empty {
    [[no_unique_address]] empty e;
};

static_assert(sizeof(one_empty) == 1);

struct all_empty {
    [[no_unique_address]] empty e0, e1;
};

static_assert(sizeof(all_empty) == 2);

//.................................................................................................
// Select which you like below:
// template <auto = []() {}>
// template <auto = [] {}>
// template <typename = decltype([] {})>
template <typename = decltype([]() {})>
struct unique_empty { };

struct all_unique_empty {
    [[no_unique_address]] unique_empty<> e0;
    [[no_unique_address]] unique_empty<> e1;
};

static_assert(sizeof(all_unique_empty) == 1);

//.................................................................................................
#if 0
template <typename T>
struct empty_wrap { };

template <typename... Ts>
struct empty_box;

template <>
struct empty_box<> { };

template <typename T, typename... Ts>
struct empty_box<T, Ts...> : public empty_box<Ts...> {
    [[no_unique_address]] empty_wrap<T> e;
};

template <class... Ts>
constexpr bool is_type_pack_set_v = (sizeof(empty_box<Ts...>) == 1);

template <class... Ts>
constexpr bool is_type_pack_multiset_v = !is_type_pack_set_v<Ts...>;
#else
/*
You can use lambda and parameter pack expansion to avoid recursion, please refer to the PR:
https://github.com/tip-of-the-week/cpp/pull/160
*/
template <typename T>
struct empty_wrap { };

template <typename T, typename = decltype([]() -> void {})>
struct unique_empty_box {
    [[no_unique_address]] empty_wrap<T> e;
};

template <typename... Ts>
struct empty_type_pack : public unique_empty_box<Ts>... { };

template <typename... Ts>
constexpr bool is_type_pack_set_v = sizeof(empty_type_pack<Ts...>) == 1;

template <typename... Ts>
constexpr bool is_type_pack_multiset_v = !is_type_pack_set_v<Ts...>;
/*
You can also use std::index_sequence and parameter pack expansion to implement it. 
The following code is from a comment of the user named 'loop', please refer to the URL:
https://godbolt.org/z/nvGrxEznb
*/
#endif

static_assert(is_type_pack_set_v<>);
static_assert(is_type_pack_set_v<char>);
static_assert(is_type_pack_set_v<char, unsigned char>);
static_assert(is_type_pack_multiset_v<char, unsigned char, unsigned char>);
static_assert(is_type_pack_multiset_v<char, unsigned char, char>);

int main(int argc, char *argv[]) {
    return 0;
}