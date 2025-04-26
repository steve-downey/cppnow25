#include <iostream>
#include <smd/streams/maybe.hpp>

auto fmapMaybe = [](auto f) {
        return [f](auto m) {
                return m([]() { return smd::streams::nothing(); })(
                        [f](auto j) { return smd::streams::just(f(j)); });
        };
};

int main() {
        auto t1 = fmapMaybe([](auto k) { return k + 1; });
        auto t2 = fmapMaybe([](auto k) { return k * 3; });

        constexpr auto m1 = smd::streams::nothing();
        constexpr auto m2 = smd::streams::just(5);

        auto r1 = t1(m1);
        auto r2 = t2(m1);
        auto r3 = t1(m2);
        auto r4 = t2(m2);

        std::cout << std::boolalpha << "r1: " << smd::streams::isJust(r1)
                  << '\n';
        std::cout << std::boolalpha << "r2: " << smd::streams::isJust(r2)
                  << '\n';
        std::cout << std::boolalpha << "r3: " << smd::streams::isJust(r3)
                  << '\n';
        std::cout << std::boolalpha << "r4: " << smd::streams::isJust(r4)
                  << '\n';

        std::cout << std::boolalpha << "r3: " << smd::streams::fromJust(r3)
                  << '\n';
        std::cout << std::boolalpha << "r4: " << smd::streams::fromJust(r4)
                  << '\n';

        return 0;
}
