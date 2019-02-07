#include "Vector2f.hpp"
#include "Mathf.hpp"
#include "Vector2i.hpp"
#include "Vector2u.hpp"
#include "Vector3f.hpp"
#include "Vector3i.hpp"
#include "Vector3u.hpp"
#include "Vector4f.hpp"
#include "Vector4i.hpp"
#include "Vector4u.hpp"

namespace chill
{
const Vector2f Vector2f::DOWN = Vector2f(0.0f, -1.0f);
const Vector2f Vector2f::LEFT = Vector2f(-1.0f, 0.0f);
const Vector2f Vector2f::ONE = Vector2f(1.0f, 1.0f);
const Vector2f Vector2f::RIGHT = Vector2f(1.0f, 0.0f);
const Vector2f Vector2f::UP = Vector2f(0.0f, 1.0f);
const Vector2f Vector2f::ZERO = Vector2f(0.0f, 0.0f);

Vector2f::Vector2f()
    : x(0.0f)
    , y(0.0f)
{
}

Vector2f::Vector2f(const Vector2f& other)
    : x(other.x)
    , y(other.y)
{
}

Vector2f::Vector2f(const Vector2i& other)
    : x(static_cast<f32>(other.x))
    , y(static_cast<f32>(other.y))
{
}

Vector2f::Vector2f(const Vector2u& other)
    : x(static_cast<f32>(other.x))
    , y(static_cast<f32>(other.y))
{
}

Vector2f::Vector2f(const Vector3f& other)
    : x(other.x)
    , y(other.y)
{
}

Vector2f::Vector2f(const Vector3i& other)
    : x(other.x)
    , y(other.y)
{
}

Vector2f::Vector2f(const Vector3u& other)
    : x(static_cast<f32>(other.x))
    , y(static_cast<f32>(other.y))
{
}

Vector2f::Vector2f(const Vector4f& other)
    : x(other.x)
    , y(other.y)
{
}

Vector2f::Vector2f(const Vector4i& other)
    : x(static_cast<f32>(other.x))
    , y(static_cast<f32>(other.y))
{
}

Vector2f::Vector2f(const Vector4u& other)
    : x(static_cast<f32>(other.x))
    , y(static_cast<f32>(other.y))
{
}

Vector2f::Vector2f(f32 x, f32 y)
    : x(x)
    , y(y)
{
}

Vector2f::Vector2f(f32 uniform)
    : x(uniform)
    , y(uniform)
{
}

Vector2f::Vector2f(const std::string& str)
{
    x = std::stof(str.substr(str.find_first_of("(") + 1u));
    y = std::stof(str.substr(str.find_first_of(",") + 1u));
}

f32 Vector2f::angle(const Vector2f& from, const Vector2f& to)
{
    return Mathf::radToDeg(acos(dot(from, to)));
}

Vector2f& Vector2f::clamp(const Vector2f& min, const Vector2f& max)
{
    x = Mathf::clamp(min.x, max.x, x);
    y = Mathf::clamp(min.y, max.y, y);

    return *this;
}

f32 Vector2f::distance(const Vector2f& p1, const Vector2f& p2)
{
    Vector2f v = p2 - p1;
    return v.length();
}

f32 Vector2f::distanceSquared(const Vector2f& p1, const Vector2f& p2)
{
    Vector2f v = p2 - p1;
    return v.lengthSquared();
}

f32 Vector2f::dot(const Vector2f& lhs, const Vector2f& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

f32 Vector2f::length() const
{
    return abs(x * x + y * y);
}

f32 Vector2f::lengthSquared() const
{
    return sqrt(abs(x * x + y * y));
}

Vector2f Vector2f::lerp(const Vector2f& start, const Vector2f& end, f32 t)
{
    return start + t * (end - start);
}

Vector2f& Vector2f::normalize()
{
    f32 len = sqrt(x * x + y * y);
    x /= len;
    y /= len;

    return *this;
}

Vector2f Vector2f::normalized() const
{
    f32 len = sqrt(x * x + y * y);
    return { x / len, y / len };
}

std::string Vector2f::toString() const
{
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

Vector2f& Vector2f::operator=(const Vector2f& other)
{
    // Check for self assignemnt.
    if (this != &other)
    {
        x = other.x;
        y = other.y;
    }

    return *this;
}

Vector2f& Vector2f::operator+=(const Vector2f& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2f& Vector2f::operator-=(const Vector2f& other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vector2f& Vector2f::operator*=(const Vector2f& other)
{
    x *= other.x;
    y *= other.y;

    return *this;
}

Vector2f& Vector2f::operator*=(f32 v)
{
    x *= v;
    y *= v;

    return *this;
}

Vector2f& Vector2f::operator/=(const Vector2f& other)
{
    x /= other.x;
    y /= other.y;

    return *this;
}

Vector2f& Vector2f::operator/=(f32 v)
{
    x /= v;
    y /= v;

    return *this;
}

f32& Vector2f::operator[](uint32 i)
{
    return (&x)[i];
}

Vector2f operator+(const Vector2f& lhs, const Vector2f& rhs)
{
    return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Vector2f operator-(const Vector2f& lhs, const Vector2f& rhs)
{
    return { lhs.x - rhs.x, lhs.y - rhs.y };
}

Vector2f operator-(const Vector2f& vector)
{
    return { -vector.x, -vector.y };
}

Vector2f operator*(const Vector2f& lhs, const Vector2f& rhs)
{
    return { lhs.x * rhs.x, lhs.y * rhs.y };
}

Vector2f operator*(const Vector2f& lhs, f32 rhs)
{
    return { lhs.x * rhs, lhs.y * rhs };
}

Vector2f operator*(f32 lhs, const Vector2f& rhs)
{
    return { lhs * rhs.y, lhs * rhs.y };
}

Vector2f operator/(const Vector2f& lhs, const Vector2f& rhs)
{
    return { lhs.x / rhs.x, lhs.y / rhs.y };
}

Vector2f operator/(const Vector2f& lhs, f32 rhs)
{
    return { lhs.x / rhs, lhs.y / rhs };
}
} // namespace chill