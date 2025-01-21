
#pragma once
#include "App/app.h"
/*#include "Components.h"*/
#include "Golfball.h"
#include "Vector2.h"
#include <string>
#include <deque>
#include "Collider.h"
#include "SpriteRenderer.h"

struct GolfClub
{
	std::deque<Vector2> positionHistory;
	const int smoothingWindow = 5;

	Component::Transform transform;
	Component::CircleCollider collider;
	Vector2 previousPos;
	GolfBall* ball = nullptr;
	bool visualDebugOn = true;
	bool canStrike = true;
	float strikeCooldown = 20;
	float impactMultiplier = 0.5f;
	int strikeCounter;

	void Init();
	void StrikeBall(GolfBall& ball);
	void Update();
	void Draw();
	void UpdateMousePosition(Vector2 currentPos);
	Vector2 CalculateVelocity(Vector2& prev, Vector2& cur);
	Vector2 CalculateVelocity();
	Vector2 GetBallEdgeImpactPoint(const Vector2& ballCenter, const Vector2& cursorPos, float ballRadius);
	void ApplyEdgeCollisionForce(Vector2& ballVelocity, const Vector2& ballCenter, const Vector2& cursorPos, const Vector2& cursorVelocity, float ballRadius, float forceMultiplier);
};