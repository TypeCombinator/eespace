# eespace(Experimental Exploration Space)

## 简介

这里是[**TypeCombinator**](https://typecombinator.github.io)的eespace！本仓库用于记录一些有意思的C++实验代码，使用C++20、C++23、C++26等现代C++特性。

## 条目

- [**Stateful Metaprogramming**](https://github.com/TypeCombinator/eespace/tree/main/examples/smp)：使用C++20实现有状态元编程，源自[Kris Jusiak](https://github.com/kris-jusiak)的元编程库[mp](https://github.com/qlibs/mp)，摘取了其中的关键代码，即使用二分搜索优化编译时间。
- [**no_unique_address**](https://github.com/TypeCombinator/eespace/tree/main/examples/unique)：使用C++20的`[[no_unique_address]]`实现**判断任意个类型是否有重复**的功能，以及代替**EBO**、实现**条件成员**等基础功能。
- [**forward_like_tuple**](https://github.com/TypeCombinator/eespace/tree/main/examples/forward_like_tuple)：C++23的`forward_like`包括了3种模型，分别为`merge`、`tuple` 和`language`，进入标准库的`std::forward`使用的是适用于主要场景的`merge`模型，对于`tuple`的`get`方法，需要使用`tuple`模型，即`forward_like_tuple`，提案[P2445](https://wg21.link/p2445)给的代码不直观也不现代，本仓库给了一个极简、易懂且现代的实现。

