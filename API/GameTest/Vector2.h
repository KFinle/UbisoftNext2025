#include "string"
#pragma once


class Vector2
{
public:
	// constructor
	Vector2(float x = 0.0f, float y = 0.0f);
	~Vector2();

	// copy constructor
	Vector2(const Vector2& rhs);

	// arithmetic operators
	Vector2 operator+(const Vector2& rhs) const;
	Vector2 operator-(const Vector2& rhs) const;
	Vector2 operator*(const Vector2& rhs) const;
	Vector2 operator*(float scale) const;
	Vector2 operator/(const Vector2& rhs) const;
	Vector2 operator/(float scale) const;
	Vector2& operator=(const Vector2& rhs);

	// shortcut operators
	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs);
	Vector2& operator*=(const Vector2& rhs);
	Vector2& operator*=(float scale);
	Vector2& operator/=(const Vector2& rhs);
	Vector2& operator/=(float scale);

	// comparison operators
	bool operator==(const Vector2& rhs) const;
	bool operator!=(const Vector2& rhs) const;
	bool operator>(const Vector2& rhs) const;
	bool operator<(const Vector2& rhs) const;
	bool operator>=(const Vector2& rhs) const;
	bool operator<=(const Vector2& rhs) const;

	// increment / decrement operators
	Vector2& operator++();
	Vector2 operator++(int);
	Vector2& operator--();
	Vector2 operator--(int);

	// Getters and Setters
	float GetX() const;
	float GetY() const;
	void SetX(float x);
	void SetY(float y);
	void Set(float x, float y);

	// utility functions
	float GetMagnitude() const;
	float GetSqrMagnitude() const;
	void SetScale(const Vector2& scale);
	Vector2 GetNormalized() const;
	void Normalize();

	// static functions
	static Vector2 Zero();
	static Vector2 One();
	static Vector2 Up();
	static Vector2 Down();
	static Vector2 Right();
	static Vector2 Left();
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
	static Vector2 LerpUnclamped(const Vector2& a, const Vector2& b, float t);
	static Vector2 MoveTowards(const Vector2& current, const Vector2& target, float max_distance_delta);
	static Vector2 Scale(const Vector2& a, const Vector2& b);
	static Vector2 Reflect(const Vector2& in_direction, const Vector2& in_normal);
	static Vector2 Perpendicular(const Vector2& in_direction);
	static float Dot(const Vector2& lhs, const Vector2& rhs);
	static Vector2 Cross(const Vector2& lhs, const Vector2& rhs);
	static float Angle(const Vector2& from, const Vector2& to);
	static float SignedAngle(const Vector2& from, const Vector2& to);
	static float Distance(const Vector2& a, const Vector2& b);
	static Vector2 ClampMagnitude(const Vector2& vector, float max_length);
	static float SqrMagnitude(const Vector2& a);
	static Vector2 Min(const Vector2& lhs, const Vector2& rhs);
	static Vector2 Max(const Vector2& lhs, const Vector2& rhs);
	static Vector2 ScaledToScreen(const Vector2& a);

	// to string
	std::string ToString(int precision = 2) const;

private:
	float m_x;
	float m_y;
};


