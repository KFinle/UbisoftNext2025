#include "stdafx.h"
#include "GolfMath.h"
#include <cmath>
#include <limits>

const float GolfMath::Epsilon = 0.00001f;
const float GolfMath::EpsilonNormalSqrt = 1e-15f;
const float GolfMath::Infinity = std::numeric_limits<float>::infinity();
const float GolfMath::NegativeInfinity = -std::numeric_limits<float>::infinity();
const float GolfMath::Deg2Rad = 0.01745329f;
const float GolfMath::Rad2Deg = 57.29578f;


float GolfMath::Sin(const float f)
{
	return static_cast<float>(sin(static_cast<double>(f)));
}

float GolfMath::Cos(const float f)
{
	return static_cast<float>(cos(static_cast<double>(f)));
}

float GolfMath::Tan(const float f)
{
	return static_cast<float>(tan(static_cast<double>(f)));
}

float GolfMath::Asin(const float f)
{
	return static_cast<float>(asin(static_cast<double>(f)));
}

float GolfMath::Acos(const float f)
{
	return static_cast<float>(acos(static_cast<double>(f)));
}

float GolfMath::Atan(const float f)
{
	return static_cast<float>(atan(static_cast<double>(f)));
}

float GolfMath::Atan2(const float y, const float x)
{
	return static_cast<float>(atan2(static_cast<double>(y), static_cast<double>(x)));
}

float GolfMath::Sqrt(const float f)
{
	return static_cast<float>(sqrt(static_cast<double>(f)));
}

float GolfMath::Abs(const float f)
{
	return abs(f);
}

int GolfMath::Abs(int value)
{
	return abs(value);
}

float GolfMath::Min(const float a, const float b)
{
	if (static_cast<double>(a) < static_cast<double>(b))
	{
		return a;
	}
	return b;
}

int GolfMath::Min(const int a, const int b)
{
	if (a < b)
	{
		return a;
	}
	return b;
}

float GolfMath::Max(const float a, const float b)
{
	if (static_cast<double>(a) > static_cast<double>(b))
	{
		return a;
	}
	return b;
}

int GolfMath::Max(const int a, const int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

float GolfMath::Pow(const float f, const float p)
{
	return static_cast<float>(pow(static_cast<double>(f), static_cast<double>(p)));
}

float GolfMath::Exp(const float power)
{
	return static_cast<float>(exp(static_cast<double>(power)));
}

float GolfMath::Log(const float f)
{
	return static_cast<float>(log(static_cast<double>(f)));
}

float GolfMath::Log10(const float f)
{
	return static_cast<float>(log10(static_cast<double>(f)));
}

float GolfMath::Ceil(const float f)
{
	return static_cast<float>(ceil(static_cast<double>(f)));
}

float GolfMath::Floor(const float f)
{
	return static_cast<float>(floor(static_cast<double>(f)));
}

float GolfMath::Round(const float f)
{
	return static_cast<float>(round(static_cast<double>(f)));
}

int GolfMath::CeilToInt(const float f)
{
	return static_cast<int>(ceil(static_cast<double>(f)));
}

int GolfMath::FloorToInt(const float f)
{
	return static_cast<int>(floor(static_cast<double>(f)));
}

int GolfMath::RoundToInt(const float f)
{
	return static_cast<int>(round(static_cast<double>(f)));
}

float GolfMath::Sign(const float f)
{
	return static_cast<double>(f) >= 0.0 ? 1.0f : -1.0f;
}

float GolfMath::Clamp(float value, const float min, const float max)
{
	if (static_cast<double>(value) < static_cast<double>(min))
	{
		value = min;
	}
	else if (static_cast<double>(value) > static_cast<double>(max))
	{
		value = max;
	}
	return value;
}

int GolfMath::Clamp(int value, const int min, const int max)
{
	if (value < min)
	{
		value = min;
	}
	else if (value > max)
	{
		value = max;
	}
	return value;
}

float GolfMath::ClampFloat(const float value)
{
	if (static_cast<double>(value) < 0.0)
	{
		return 0.0f;
	}
	if (static_cast<double>(value) > 1.0)
	{
		return 1.0f;
	}
	return value;
}

float GolfMath::Lerp(const float a, const float b, const float t)
{
	return a + (b - a) * GolfMath::ClampFloat(t);
}

float GolfMath::LerpUnclamped(const float a, const float b, const float t)
{
	return a + (b - a) * t;
}

float GolfMath::LerpAngle(const float a, const float b, const float t)
{
	float num = GolfMath::Repeat(b - a, 360.0f);
	if (static_cast<double>(num) > 180.0)
	{
		num -= 360.0f;
	}
	return a + num * GolfMath::ClampFloat(t);
}

float GolfMath::MoveTowards(const float current, const float target, const float max_delta)
{
	if (static_cast<double>(GolfMath::Abs(target - current)) <= static_cast<double>(max_delta))
	{
		return target;
	}
	return current + GolfMath::Sign(target - current) * max_delta;
}

float GolfMath::MoveTowardsAngle(const float current, float target, const float max_delta)
{
	target = current + GolfMath::DeltaAngle(current, target);
	return GolfMath::MoveTowards(current, target, max_delta);
}

float GolfMath::SmoothStep(const float from, const float to, float t)
{
	t = GolfMath::ClampFloat(t);
	t = static_cast<float>(-2.0 * static_cast<double>(t) * static_cast<double>(t) * static_cast<double>(t) + 3.0 * static_cast<double>(t) * static_cast<double>(t));
	return static_cast<float>(static_cast<double>(to) * static_cast<double>(t) + static_cast<double>(from) * (1.0 - static_cast<double>(t)));
}

bool GolfMath::Approximately(const float a, const float b)
{
	return static_cast<double>(GolfMath::Abs(b - a)) < static_cast<double>(GolfMath::Max(1E-06f * GolfMath::Max(GolfMath::Abs(a), GolfMath::Abs(b)), GolfMath::Epsilon * 8.0f));
}

float GolfMath::Repeat(const float t, const float length)
{
	return t - GolfMath::Floor(t / length) * length;
}

float GolfMath::PingPong(float t, const float length)
{
	t = GolfMath::Repeat(t, length * 2.0f);
	return length - GolfMath::Abs(t - length);
}

float GolfMath::InverseLerp(const float a, const float b, const float value)
{
	if (static_cast<double>(a) != static_cast<double>(b))
	{
		return GolfMath::ClampFloat(static_cast<float>((static_cast<double>(value) - static_cast<double>(a)) / (static_cast<double>(b) - static_cast<
			double>(a))));
	}
	return 0.0f;
}

float GolfMath::DeltaAngle(const float current, const float target)
{
	float num = GolfMath::Repeat(target - current, 360.0f);
	if (static_cast<double>(num) > 180.0)
	{
		num -= 360.0f;
	}
	return num;
}
