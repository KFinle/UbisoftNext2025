///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
#include "Vector2.h"
#include "stdafx.h"
//------------------------------------------------------------------------
#include <string>
#include <windows.h> 
#include <math.h>  
//------------------------------------------------------------------------
#include "app\app.h"
#include "LevelBuilder.h"
#include "Golfball.h"
#include "GolfClub.h"
#include "LevelBuilder.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
GolfBall ball;
GolfClub club;
LevelBuilder::Level level;
int maxObjects = 20;

//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	ball = GolfBall();
    level = LevelBuilder::Level::GenerateLevel(maxObjects);
	ball.visualDebugOn = true;
	ball.level = level;
  club.ball = &ball;
  ball.transform.position = level.spawnPoint;
  ball.sprite = Component::SpriteRenderer("./Resources/ball.bmp", .03f, ball.transform.position);
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	ball.Update();
	club.Update();
	if (ball.goalFound || App::IsKeyPressed('R'))
	{
		LevelBuilder::Level::currentLevel++;
		club.strikeCounter = 0;
		maxObjects++;
		Init();
	}
}

void Render()
{	
	/*field->Draw();*/
	ball.Draw();
	club.Draw();
	level.DrawObjects();
	
}
void Shutdown()
{	
}
