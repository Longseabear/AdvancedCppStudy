#include <iostream>
#include <string>
#include <string_view>
using namespace std;


#if defined(__GNUC__) || defined(__clang__) // GCC 컴파일러에서 정의되는 매크로
#define __MY_PRETTY_FUNCTION_SIGNITURE __PRETTY_FUNCTION__
#define __MY_PRETTY_FUNCTION_START '='
#define __MY_PRETTY_FUNCTION_END ']'
#elif defined(_MSC_VER) // Microsoft Visual C++에서 정의되는 매크로
#define __MY_PRETTY_FUNCTION_SIGNITURE __FUNCSIG__
#define __MY_PRETTY_FUNCTION_START '<'
#define __MY_PRETTY_FUNCTION_END '>'
#endif

class MyTypeName {
    int val;
};
class MyTypeName2 {
    int val;
};


template<typename Type>
[[nodiscard]] constexpr auto stripped_type_name() noexcept {
    std::string_view pretty_function{ __MY_PRETTY_FUNCTION_SIGNITURE };
    auto first = pretty_function.find_first_not_of(' ', pretty_function.find_first_of(__MY_PRETTY_FUNCTION_START) + 1);
    auto value = pretty_function.substr(first, pretty_function.find_last_of(__MY_PRETTY_FUNCTION_END) - first);
    return value;
}


template<typename Type>
constexpr auto sript() noexcept {
    constexpr char sig[] = __MY_PRETTY_FUNCTION_SIGNITURE;
    return;
}

template<typename Type>
constexpr auto get_class_name() noexcept {
    constexpr char sig[] = __MY_PRETTY_FUNCTION_SIGNITURE;
    return sig;
}

template<typename Type, auto = stripped_type_name<Type>().find_first_of('.')>
[[nodiscard]] constexpr std::string_view type_name(int) noexcept {
    constexpr auto value = stripped_type_name<Type>();
    return value;
}

template<typename Type, auto = stripped_type_name<Type>().find_first_of('.')>
[[nodiscard]] constexpr auto get_type_hash(){
    unsigned int h = 0;
    for (auto x : stripped_type_name<Type>()) h = 65599 * h + x;
    return h ^ (h >> 16);
}

int main() {
    cout << __MY_PRETTY_FUNCTION_SIGNITURE <<"\n";

    constexpr auto A = type_name<MyTypeName>(0);
    const auto B = type_name<MyTypeName>(0);
    constexpr auto C = type_name<MyTypeName2>(0);
    auto D = type_name<MyTypeName2>(0);

    constexpr auto a = get_type_hash<MyTypeName>();

    cout << A << " " << B << " " << C << " " << D;
    cout << "\n" << a  << "\n";
    return 0;
}