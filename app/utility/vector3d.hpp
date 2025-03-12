#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include "quaternion3d.hpp"
#include <cassert>
#include <cmath>
#include <compare>
#include <concepts>
#include <exception>
#include <stdexcept>
#include <utility>

namespace Utility {

    template <typename T>
    struct Vector3D {
        [[nodiscard]] T distance(Vector3D const& other) const noexcept
        {
            return std::sqrt(std::pow(this->x - other.x, 2) + std::pow(this->y - other.y, 2) +
                             std::pow(this->z - other.z, 2));
        }

        [[nodiscard]] T magnitude() const noexcept
        {
            return std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));
        }

        [[nodiscard]] Vector3D rotated(Quaternion3D<T> const& quaternion) const noexcept
        {
            Quaternion3D p(0, this->x, this->y, this->z);
            p *= quaternion;
            p *= quaternion.conjugated();
            return Vector3D{p.x, p.y, p.z};
        }

        void rotate(Quaternion3D<T> const& quaternion) noexcept
        {
            Quaternion3D p(0, this->x, this->y, this->z);
            p *= quaternion;
            p *= quaternion.conjugated();
            this->x = p.x;
            this->y = p.y;
            this->z = p.z;
        }

        [[nodiscard]] Vector3D normalized() const noexcept
        {
            const auto im{T{1} / this->magnitude()};
            return Vector3D{this->x * im, this->y * im, this->z * im};
        }

        void normalize() noexcept
        {
            const auto im{T{1} / this->magnitude()};
            *this *= im;
        }

        [[nodiscard]] Vector3D& operator+=(Vector3D const& other) noexcept
        {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        [[nodiscard]] Vector3D& operator-=(Vector3D const& other) noexcept
        {
            this->x -= other.x;
            this->y -= other.y;
            this->z -= other.z;
            return *this;
        }

        [[nodiscard]] Vector3D& operator*=(T const factor)
        {
            this->x *= factor;
            this->y *= factor;
            this->z *= factor;
            return *this;
        }

        [[nodiscard]] Vector3D& operator/=(T const factor)
        {
            if (factor == static_cast<T>(0)) {
                assert(true);
            }

            this->x *= factor;
            this->y *= factor;
            this->z *= factor;
            return *this;
        }

        template <typename C>
        [[nodiscard]] explicit operator Vector3D<C>() const noexcept
        {
            return Vector3D<C>{static_cast<C>(this->x), static_cast<C>(this->y), static_cast<C>(this->z)};
        }

        [[nodiscard]] bool operator<=>(Vector3D const& other) const noexcept = default;

        T x{};
        T y{};
        T z{};
    };

    template <typename T>
    [[nodiscard]] Vector3D<T> operator+(Vector3D<T> const& left, Vector3D<T> const& right) noexcept
    {
        return Vector3D<T>{left.x + right.x, left.y + right.y, left.z + right.z};
    }

    template <typename T>
    [[nodiscard]] Vector3D<T> operator-(Vector3D<T> const& left, Vector3D<T> const& right) noexcept
    {
        return Vector3D<T>{left.x - right.x, left.y - right.y, left.z - right.z};
    }

    template <typename T>
    [[nodiscard]] Vector3D<T> operator*(T const factor, Vector3D<T> const& vector)
    {
        return Vector3D<T>{vector.x * factor, vector.y * factor, vector.z * factor};
    }

    template <typename T>
    [[nodiscard]] Vector3D<T> operator*(Vector3D<T> const& vector, T const factor)
    {
        return factor * vector;
    }

    template <typename T>
    [[nodiscard]] Vector3D<T> operator/(Vector3D<T> const& vector, T const factor)
    {
        if (factor == static_cast<T>(0)) {
            assert(true);
        }

        return Vector3D<T>{vector.x / factor, vector.y / factor, vector.z / factor};
    }

}; // namespace Utility

#endif // VECTOR3D_HPP