#pragma once
#include "App/AppSettings.h"
#include "App/app.h"
#include "Components.h"
#include "Collider.h"
#include "ShapeRenderer.h"
#include "SpriteRenderer.h"
#include "LevelBuilder.h"
#include <deque>
class GolfBall
{
public:
	bool visualDebugOn = true;
	Component::Friction friction;
	Component::Transform transform;
	Component::Circle body;
	Component::SpriteRenderer sprite;
	Component::CircleCollider collider;
	LevelBuilder::Level level;
	float maxVelocity = 20;
	bool goalFound = false;
	GolfBall();
	void Update();
	void KeepWithinScreenBoundaries();
	void Draw();
	void DrawRadius();
	void HandleLevelCollision(LevelBuilder::Level& level);
	void HandleCollision(Component::Collider* other);
	void ReflectCircleCollision(Component::CircleCollider& other);
	void ReflectBoxCollision(Component::BoxCollider& other);
	Vector2 GetClosestPointOnBox(Component::BoxCollider& box);
	void DrawCollision();
private:
  std::deque<Vector2> trailPositions;
  int maxTrailSize = 30;
  float trailFade = 0.5f;
};
