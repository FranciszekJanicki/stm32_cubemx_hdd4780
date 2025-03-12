#ifndef QUATERNION3D_HPP
#define QUATERNION3D_HPP

#include <cassert>
#include <cmath>
#include <compare>
#include <concepts>
#include <cstdlib>
#include <stdexcept>
#include <tuple>
#include <utility>

namespace Utility {

    template <typename T>
    struct Quaternion3D {
        [[nodiscard]] Quaternion3D conjugated() const noexcept
        {
            return Quaternion3D{this->w, -this->x, -this->y, -this->z};
        }

        void conjugate() noexcept
        {
            this->x = -this->x;
            this->y = -this->y;
            this->z = -this->z;
        }

        [[nodiscard]] T magnitude() const noexcept
        {
            return std::sqrt(std::pow(this->w, 2) + std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));
        }

        [[nodiscard]] Quaternion3D normalized() const noexcept
        {
            const auto im{static_cast<T>(1) / this->magnitude()};
            return Quaternion3D{this->w * im, this->x * im, this->y * im, this->z * im};
        }

        void normalize() noexcept
        {
            const auto im{static_cast<T>(1) / this->magnitude()};
            *this *= im;
        }

        [[nodiscard]] Quaternion3D& operator+=(Quaternion3D const& other)
        {
            this->w += other.w;
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        [[nodiscard]] Quaternion3D& operator-=(Quaternion3D const& other)
        {
            this->w -= other.w;
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            return *this;
        }

        [[nodiscard]] Quaternion3D& operator*=(Quaternion3D const& other)
        {
            this->w = this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z;
            this->x = this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y;
            this->y = this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x;
            this->z = this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w;
            return *this;
        }

        [[nodiscard]] Quaternion3D& operator*=(T const factor)
        {
            this->w *= factor;
            this->x *= factor;
            this->y *= factor;
            this->z *= factor;
            return *this;
        }

        [[nodiscard]] Quaternion3D& operator/=(T const factor)
        {
            if (factor == static_cast<T>(0)) {
                assert(true);
            }

            this->w /= factor;
            this->x /= factor;
            this->y /= factor;
            this->z /= factor;
            return *this;
        }

        template <typename C>
        [[nodiscard]] explicit operator Quaternion3D<C>() const noexcept
        {
            return Quaternion3D<C>{static_cast<C>(this->w),
                                   static_cast<C>(this->x),
                                   static_cast<C>(this->y),
                                   static_cast<C>(this->z)};
        }

        [[nodiscard]] bool operator<=>(Quaternion3D const& other) const noexcept = default;

        T w{};
        T x{};
        T y{};
        T z{};
    };

    template <typename T>
    [[nodiscard]] Quaternion3D<T> operator+(Quaternion3D<T> const& left, Quaternion3D<T> const& right) noexcept
    {
        return Quaternion3D<T>{left.w + right.w, left.x + right.x, left.y + right.y, left.z + right.z};
    }

    template <typename T>
    [[nodiscard]] Quaternion3D<T> operator-(Quaternion3D<T> const& left, Quaternion3D<T> const& right) noexcept
    {
        return Quaternion3D<T>{left.w - right.w, left.x - right.x, left.y - right.y, left.z + right.z};
    }

    template <typename T>
    [[nodiscard]] Quaternion3D<T> operator*(Quaternion3D<T> const& left, Quaternion3D<T> const& right) noexcept
    {
        return Quaternion3D<T>{left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z,
                               left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y,
                               left.w * right.y - left.x * right.z + left.y * right.w + left.z * right.x,
                               left.w * right.z + left.x * right.y - left.y * right.x + left.z * right.w};
    }

    template <typename T>
    [[nodiscard]] Quaternion3D<T> operator*(Quaternion3D<T> const& quaternion, T const factor)
    {
        return Quaternion3D<T>{quaternion.w * factor,
                               quaternion.x * factor,
                               quaternion.y * factor,
                               quaternion.z * factor};
    }

    template <typename T>
    [[nodiscard]] Quaternion3D<T> operator*(T const factor, Quaternion3D<T> const& quaternion)
    {
        return quaternion * factor;
    }

    template <typename T>
    [[nodiscard]] Quaternion3D<T> operator/(Quaternion3D<T> const& quaternion, T const factor)
    {
        if (factor == static_cast<T>(0)) {
            assert(true);
        }

        return Quaternion3D<T>{quaternion.w / factor,
                               quaternion.x / factor,
                               quaternion.y / factor,
                               quaternion.z / factor};
    }

}; // namespace Utility

#endif // QUATERNION3D_HPP