/**
 * @file       test_vec_swizzle.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2024-04-15
 *
 * @brief    Test for vector swizzle.
 *
 * *********************************************************************************
 *
 *
 * *********************************************************************************
 */

#include "../include/vec/vec.h"

using namespace lumi;

int main() {
    Vec3f v0(10, 20, 30);
    std::cout << sizeof(Vec3f) << std::endl;
    std::cout << v0.zyx << std::endl;
    Vec2f c(-5, -5);
    v0.xz = c;
    Vec2f v1(v0.yz);
    std::cout << v0 << std::endl;
    std::cout << v1 << std::endl;
    Vec3f v(50, 60, 70);
    Vec2f d = v.yz;
    std::cout << d << std::endl;
    float f = d.x * d.y;
    std::cout << f << std::endl;
    std::cout << v0.zzy << std::endl;

    return 0;
}