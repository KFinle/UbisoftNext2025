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
#include "Golfball.h"
#include "GolfClub.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------
CSimpleSprite *field;
/*CSimpleSprite *ball;*/
GolfBall ball;
GolfClub club;
/*enum*/
/*{*/
/*	ANIM_FORWARDS,*/
/*	ANIM_BACKWARDS,*/
/*	ANIM_LEFT,*/
/*	ANIM_RIGHT,*/
/*};*/
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	ball.visualDebugOn = true;
  club.ball = &ball;
  field = App::CreateSprite(".\\Resources\\field.bmp", 1, 1);
  ball.transform.position = Vector2(400, 400);
  ball.sprite = Component::SpriteRenderer("./Resources/ball.bmp", .02f, ball.transform.position);

  /*ball = App::CreateSprite(".\\Resources\\ball.bmp", 1, 1);*/
  
	//------------------------------------------------------------------------
	// Example Sprite Code....
	/*testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);*/
	field->SetPosition(400.0f, 400.0f);
	/*ball->SetPosition(400.0f, 400.0f);*/
	/* ball->SetScale(.02f);*/
	/*const float speed = 1.0f / 15.0f;*/
	/*testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });*/
	/*testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });*/
	/*testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });*/
	/*testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });*/
	/*testSprite->SetScale(1.0f);*/
	//------------------------------------------------------------------------
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{
	ball.Update();
  club.Update();
	//------------------------------------------------------------------------
	// Example Sprite Code....
	/*testSprite->Update(deltaTime);*/
	/*if (App::GetController().GetLeftThumbStickX() > 0.5f)*/
	/*{*/
	/*	testSprite->SetAnimation(ANIM_RIGHT);*/
	/*	float x, y;*/
	/*	testSprite->GetPosition(x, y);*/
	/*	x += 1.0f;*/
	/*	testSprite->SetPosition(x, y);*/
	/*}*/
	/*if (App::GetController().GetLeftThumbStickX() < -0.5f)*/
	/*{*/
	/*	testSprite->SetAnimation(ANIM_LEFT);*/
	/*	float x, y;*/
	/*	testSprite->GetPosition(x, y);*/
	/*	x -= 1.0f;*/
	/*	testSprite->SetPosition(x, y);*/
	/*}*/
	/*   if (App::GetController().GetLeftThumbStickY() > 0.5f)*/
	/*   {*/
	/*       testSprite->SetAnimation(ANIM_FORWARDS);*/
	/*       float x, y;*/
	/*       testSprite->GetPosition(x, y);*/
	/*       y += 1.0f;*/
	/*       testSprite->SetPosition(x, y);*/
	/*   }*/
	/*if (App::GetController().GetLeftThumbStickY() < -0.5f)*/
	/*{*/
	/*	testSprite->SetAnimation(ANIM_BACKWARDS);*/
	/*	float x, y;*/
	/*	testSprite->GetPosition(x, y);*/
	/*	y -= 1.0f;*/
	/*	testSprite->SetPosition(x, y);*/
	/*}*/
	/*if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))*/
	/*{*/
	/*	testSprite->SetScale(testSprite->GetScale() + 0.1f);*/
	/*}*/
	/*if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))*/
	/*{*/
	/*	testSprite->SetScale(testSprite->GetScale() - 0.1f);*/
	/*}*/
	/*if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))*/
	/*{*/
	/*	testSprite->SetAngle(testSprite->GetAngle() + 0.1f);*/
	/*}*/
	/*if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))*/
	/*{*/
	/*	testSprite->SetAngle(testSprite->GetAngle() - 0.1f);*/
	/*}*/
	/*if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))*/
	/*{*/
	/*	testSprite->SetAnimation(-1);*/
	/*}*/
	/*//------------------------------------------------------------------------*/
	/*// Sample Sound.*/
	/*//------------------------------------------------------------------------*/
	/*if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))*/
	/*{*/
	/*	App::PlaySound(".\\TestData\\Test.wav", true);*/
	/*}*/
	/*if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))*/
	/*{*/
	/*	App::StopSound(".\\TestData\\Test.wav");*/
	/*}*/
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	field->Draw();
	ball.Draw();
	club.Draw();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
  
 
	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	delete field;
	//------------------------------------------------------------------------
}
