#include "stdafx.h"
#include "Vector2.h"
#include "GolfMath.h"
#include "iomanip"
#include "sstream"

Vector2::Vector2(float x, float y) : m_x(x), m_y(y)
{
}


Vector2::~Vector2()
{
}


Vector2::Vector2(const Vector2& rhs)
{
	Set(rhs.GetX(), rhs.GetY());
}


Vector2 Vector2::operator+(const Vector2& rhs) const
{
	Vector2 vector;
	vector.Set(GetX() + rhs.GetX(), GetY() + rhs.GetY());
	return vector;
}


Vector2 Vector2::operator-(const Vector2& rhs) const
{
	Vector2 vector;
	vector.Set(GetX() - rhs.GetX(), GetY() - rhs.GetY());
	return vector;
}


Vector2 Vector2::operator*(const Vector2& rhs) const
{
	Vector2 vector;
	vector.Set(GetX() * rhs.GetX(), GetY() * rhs.GetY());
	return vector;
}

Vector2 Vector2::operator*(float scale) const
{
	Vector2 vector;
	vector.Set(GetX() * scale, GetY() * scale);
	return vector;
}


Vector2 Vector2::operator/(const Vector2& rhs) const
{
	Vector2 vector;
	vector.Set(GetX() / rhs.GetX(), GetY() / rhs.GetY());
	return vector;
}


Vector2 Vector2::operator/(float scale) const
{
	return Vector2(GetX() / scale, GetY() / scale);
}


Vector2& Vector2::operator=(const Vector2& rhs)
{
	Set(rhs.GetX(), rhs.GetY());
	return *this;
}


Vector2& Vector2::operator+=(const Vector2& rhs)
{
	Set(GetX() + rhs.GetX(), GetY() + rhs.GetY());
	return *this;
}


Vector2& Vector2::operator-=(const Vector2& rhs)
{
	Set(GetX() - rhs.GetX(), GetY() - rhs.GetY());
	return *this;
}


Vector2& Vector2::operator*=(const Vector2& rhs)
{
	Set(GetX() * rhs.GetX(), GetY() * rhs.GetY());
	return *this;
}

Vector2& Vector2::operator*=(float scale)
{
	Set(GetX() * scale, GetY() * scale);
	return *this;
}


Vector2& Vector2::operator/=(const Vector2& rhs)
{
	Set(GetX() / rhs.GetX(), GetY() / rhs.GetY());
	return *this;
}

Vector2& Vector2::operator/=(float scale)
{
	Set(GetX() / scale, GetY() / scale);
	return *this;
}


bool Vector2::operator==(const Vector2& rhs) const
{
	return ((GetX() == rhs.GetX()) && (GetY() == rhs.GetY()));
}


bool Vector2::operator!=(const Vector2& rhs) const
{
	return ((GetX() != rhs.GetX()) && (GetY() != rhs.GetY()));
}


bool Vector2::operator>(const Vector2& rhs) const
{
	return ((GetX() > rhs.GetX()) && (GetY() > rhs.GetY()));
}


bool Vector2::operator<(const Vector2& rhs) const
{
	return ((GetX() < rhs.GetX()) && (GetY() < rhs.GetY()));
}


bool Vector2::operator>=(const Vector2& rhs) const
{
	return ((GetX() >= rhs.GetX()) && (GetY() >= rhs.GetY()));
}


bool Vector2::operator<=(const Vector2& rhs) const
{
	return ((GetX() <= rhs.GetX()) && (GetY() <= rhs.GetY()));
}



Vector2& Vector2::operator++()
{
	Set(GetX() + 1, GetY() + 1);
	return *this;
}


Vector2 Vector2::operator++(int)
{
	Vector2 vector = *this;
	++*this;
	return vector;
}


Vector2& Vector2::operator--()
{
	Set(GetX() - 1, GetY() - 1);
	return *this;
}


Vector2 Vector2::operator--(int)
{
	Vector2 vector = *this;
	--*this;
	return vector;
}


float Vector2::GetX() const
{
	return m_x;
}


float Vector2::GetY() const
{
	return m_y;
}


void Vector2::SetX(float x)
{
	m_x = x;
}


void Vector2::SetY(float y)
{
	m_y = y;
}


void Vector2::Set(float x, float y)
{
	m_x = x;
	m_y = y;
}


float Vector2::GetMagnitude() const
{
	return GolfMath::Sqrt(GetX() * GetX() +
		GetY() * GetY());
}


float Vector2::GetSqrMagnitude() const
{
	return GetX() * GetX() + GetY() * GetY();
}


void Vector2::SetScale(const Vector2& scale)
{
	*this *= scale;
}


Vector2 Vector2::GetNormalized() const
{
	Vector2 vector = Vector2(GetX(), GetY());
	vector.Normalize();
	return vector;
}


void Vector2::Normalize()
{
	const auto magnitude = GetMagnitude();
	if (static_cast<double>(magnitude) > 9.99999974737875E-06)
	{
		Set(GetX() / magnitude, GetY() / magnitude);
	}
	else
	{
		*this = Vector2::Zero();
	}
}


Vector2 Vector2::Zero()
{
	return Vector2(0.0f, 0.0f);
}


Vector2 Vector2::One()
{
	return Vector2(1.0, 1.0);
}


Vector2 Vector2::Up()
{
	return Vector2(0.0, 1.0);
}


Vector2 Vector2::Down()
{
	return Vector2(0.0, -1.0);
}


Vector2 Vector2::Right()
{
	return Vector2(1.0, 0.0);
}


Vector2 Vector2::Left()
{
	return Vector2(-1.0, 0.0);
}





Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
{
	t = GolfMath::ClampFloat(t);
	return Vector2(a.GetX() + (b.GetX() - a.GetX()) * t, a.GetY() + (b.GetY() - a.GetY()) * t);
}


Vector2 Vector2::LerpUnclamped(const Vector2& a, const Vector2& b, float t)
{
	return Vector2(a.GetX() + (b.GetX() - a.GetX()) * t, a.GetY() + (b.GetY() - a.GetY()) * t);
}


Vector2 Vector2::MoveTowards(const Vector2& current, const Vector2& target, float max_distance_delta)
{
	const Vector2 vector = target - current;
	const auto magnitude = vector.GetMagnitude();
	if (static_cast<double>(magnitude) <= static_cast<double>(max_distance_delta) || static_cast<double>(magnitude) == 0.0)
	{
		return target;
	}
	return current + vector / magnitude * max_distance_delta;
}


Vector2 Vector2::Scale(const Vector2& a, const Vector2& b)
{
	return Vector2(a.GetX() * b.GetX(), a.GetY() * b.GetY());
}


Vector2 Vector2::Reflect(const Vector2& in_direction, const Vector2& in_normal)
{
	return in_normal * (-2.0f * Vector2::Dot(in_normal, in_direction)) + in_direction;
}


Vector2 Vector2::Perpendicular(const Vector2& in_direction)
{
	return Vector2(-in_direction.GetY(), in_direction.GetX());
}


float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.GetX() * rhs.GetX() + lhs.GetY() * rhs.GetY();
}



float Vector2::Angle(const Vector2& from, const Vector2& to)
{
	const auto denominator = GolfMath::Sqrt(from.GetSqrMagnitude() * to.GetSqrMagnitude());
	if (denominator < GolfMath::EpsilonNormalSqrt)
	{
		return 0.0F;
	}

	const auto dot = GolfMath::Clamp(Vector2::Dot(from, to) / denominator, -1.0F, 1.0F);
	return GolfMath::Acos(dot) * GolfMath::Rad2Deg;
}

float Vector2::SignedAngle(const Vector2& from, const Vector2& to)
{
	const auto unsigned_angle = Vector2::Angle(from, to);
	const auto sign = GolfMath::Sign(from.GetX() * to.GetY() - from.GetY() * to.GetX());
	return unsigned_angle * sign;
}


float Vector2::Distance(const Vector2& a, const Vector2& b)
{
	const auto delta_x = static_cast<double>(b.GetX()) - static_cast<double>(a.GetX());
	const auto delta_y = static_cast<double>(b.GetY()) - static_cast<double>(a.GetY());
	return GolfMath::Sqrt(static_cast<float>(delta_x * delta_x + delta_y * delta_y));
}


Vector2 Vector2::ClampMagnitude(const Vector2& vector, float max_length)
{
	if (static_cast<double>(vector.GetSqrMagnitude()) > static_cast<double>(max_length) * static_cast<double>(max_length))
	{
		return vector.GetNormalized() * max_length;
	}
	return vector;
}


float Vector2::SqrMagnitude(const Vector2& a)
{
	return a.GetX() * a.GetX() + a.GetY() * a.GetY();
}


Vector2 Vector2::Min(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(GolfMath::Min(lhs.GetX(), rhs.GetX()), GolfMath::Min(lhs.GetY(), rhs.GetY()));
}


Vector2 Vector2::Max(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(GolfMath::Max(lhs.GetX(), rhs.GetX()), GolfMath::Max(lhs.GetY(), rhs.GetY()));
}


std::string Vector2::ToString(const int precision) const
{
	std::stringstream out;

	out << std::fixed << std::setprecision(precision);
	out << "(" << m_x << ", " << m_y << ")";
	return out.str();
}
