/**
 * @file       BinTree.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2024-04-15
 *
 * @brief    vector swizzle.
 *
 * *********************************************************************************
 *
 *
 * *********************************************************************************
 */

// !!! No QA !!!

#include <cassert>
#include <cstdint>
#include <iostream>
#include <type_traits>

namespace lumi {

template <uint32_t FirstIndex>
constexpr bool AreDifferentIndices() {
    return true;
}

template <uint32_t FirstIndex, uint32_t SecondIndex, uint32_t... Rest>
constexpr bool AreDifferentIndices() {
    if (FirstIndex == SecondIndex) {
        return false;
    }
    constexpr bool found_duplicate = ((FirstIndex == Rest) || ...); // c++17
    if (found_duplicate) {
        return false;
    }
    return AreDifferentIndices<SecondIndex, Rest...>();
}

// https://stackoverflow.com/questions/51641131
// https://stackoverflow.com/questions/7230621
template <typename Type, uint32_t Index>
struct ScalarSwizzle {
    Type data[1];  // placeholder

    ScalarSwizzle(const Type& x) { data[Index] = x; }
    Type& operator=(const Type& x) {
        data[Index] = x;
        return data[Index];
    }
    operator Type() const { return data[Index]; }
    Type operator++(int) { return data[Index]++; }
    Type operator++() { return ++data[Index]; }
    Type operator--(int) { return data[Index]--; }
    Type operator--() { return --data[Index]; }
};

template <typename VecType, uint32_t N, uint32_t... Indices>
struct VectorSwizzle {
    float data[N];  // placeholder

    VecType operator=(const VecType& vec) {
        assert(AreDifferentIndices<Indices...>() &&
               "Cannot assign to duplicate indices!");
        VecType res{};

        int j = 0;
        for (const uint32_t i : {Indices...}) {
            data[i] = vec[j];
            j++;
        }
        return res;
    }

    operator VecType() {
        VecType res{};

        int j = 0;
        for (const uint32_t i : {Indices...}) {
            res[j] = data[i];
            j++;
        }
        return res;
    }
};

struct Vec2f {
    union {
        float data[2];

        ScalarSwizzle<float, 0> x, r, u;
        ScalarSwizzle<float, 1> y, g, v;

        VectorSwizzle<Vec2f, 2, 0, 0> xx;
        VectorSwizzle<Vec2f, 2, 0, 1> xy;
        VectorSwizzle<Vec2f, 2, 1, 0> yx;
        VectorSwizzle<Vec2f, 2, 1, 1> yy;

        VectorSwizzle<Vec2f, 2, 0, 0> rr;
        VectorSwizzle<Vec2f, 2, 0, 1> rg;
        VectorSwizzle<Vec2f, 2, 1, 0> gr;
        VectorSwizzle<Vec2f, 2, 1, 1> gg;

        VectorSwizzle<Vec2f, 2, 0, 0> uu;
        VectorSwizzle<Vec2f, 2, 0, 1> uv;
        VectorSwizzle<Vec2f, 2, 1, 0> vu;
        VectorSwizzle<Vec2f, 2, 1, 1> vv;
    };

    Vec2f() { x = y = 0; }

    Vec2f(float val) { x = y = val; }

    Vec2f(float x, float y) {
        this->x = x;
        this->y = y;
    }

    float& operator[](uint32_t i) { return data[i]; }

    const float& operator[](uint32_t i) const { return data[i]; }
};

inline std::ostream& operator<<(std::ostream& os, const Vec2f& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

struct Vec3f {
    union {
        float data[3];

        ScalarSwizzle<float, 0> x, r;
        ScalarSwizzle<float, 1> y, g;
        ScalarSwizzle<float, 2> z, b;

        VectorSwizzle<Vec2f, 3, 0, 0> xx;
        VectorSwizzle<Vec2f, 3, 0, 1> xy;
        VectorSwizzle<Vec2f, 3, 0, 2> xz;
        VectorSwizzle<Vec2f, 3, 1, 0> yx;
        VectorSwizzle<Vec2f, 3, 1, 1> yy;
        VectorSwizzle<Vec2f, 3, 1, 2> yz;
        VectorSwizzle<Vec2f, 3, 2, 0> zx;
        VectorSwizzle<Vec2f, 3, 2, 1> zy;
        VectorSwizzle<Vec2f, 3, 2, 2> zz;

        VectorSwizzle<Vec3f, 3, 0, 0, 0> xxx;
        VectorSwizzle<Vec3f, 3, 0, 0, 1> xxy;
        VectorSwizzle<Vec3f, 3, 0, 0, 2> xxz;
        VectorSwizzle<Vec3f, 3, 0, 1, 0> xyx;
        VectorSwizzle<Vec3f, 3, 0, 1, 1> xyy;
        VectorSwizzle<Vec3f, 3, 0, 1, 2> xyz;
        VectorSwizzle<Vec3f, 3, 0, 2, 0> xzx;
        VectorSwizzle<Vec3f, 3, 0, 2, 1> xzy;
        VectorSwizzle<Vec3f, 3, 0, 2, 2> xzz;

        VectorSwizzle<Vec3f, 3, 1, 0, 0> yxx;
        VectorSwizzle<Vec3f, 3, 1, 0, 1> yxy;
        VectorSwizzle<Vec3f, 3, 1, 0, 2> yxz;
        VectorSwizzle<Vec3f, 3, 1, 1, 0> yyx;
        VectorSwizzle<Vec3f, 3, 1, 1, 1> yyy;
        VectorSwizzle<Vec3f, 3, 1, 1, 2> yyz;
        VectorSwizzle<Vec3f, 3, 1, 2, 0> yzx;
        VectorSwizzle<Vec3f, 3, 1, 2, 1> yzy;
        VectorSwizzle<Vec3f, 3, 1, 2, 2> yzz;

        VectorSwizzle<Vec3f, 3, 2, 0, 0> zxx;
        VectorSwizzle<Vec3f, 3, 2, 0, 1> zxy;
        VectorSwizzle<Vec3f, 3, 2, 0, 2> zxz;
        VectorSwizzle<Vec3f, 3, 2, 1, 0> zyx;
        VectorSwizzle<Vec3f, 3, 2, 1, 1> zyy;
        VectorSwizzle<Vec3f, 3, 2, 1, 2> zyz;
        VectorSwizzle<Vec3f, 3, 2, 2, 0> zzx;
        VectorSwizzle<Vec3f, 3, 2, 2, 1> zzy;
        VectorSwizzle<Vec3f, 3, 2, 2, 2> zzz;
    };

    Vec3f() { x = y = z = 0; }

    Vec3f(float val) { x = y = z = val; }

    Vec3f(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    float& operator[](uint32_t i) { return data[i]; }

    const float& operator[](uint32_t i) const { return data[i]; }
};

inline std::ostream& operator<<(std::ostream& os, const Vec3f& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

}