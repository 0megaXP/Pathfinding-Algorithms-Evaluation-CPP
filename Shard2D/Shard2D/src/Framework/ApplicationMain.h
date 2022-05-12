#pragma once

#include "../Framework/Entities/Sprite.h"
#include "../Framework/Entities/TextField.h"
#include "Events/EventTypes/MouseEvent.h"
#include "Events/EventTypes/KeyboardEvent.h"
#include "Management/IMain.h"

class ApplicationMain : public Shard2D::IMain
{
public:
	ApplicationMain();

private: 
	friend class Shard2D::GameManager;

	void Init();

	void Update();

	void TestMethod(Shard2D::KeyboardEvent* _event);
	void TestMethod2(Shard2D::KeyboardEvent* _event);

	Shard2D::Sprite* sprite;
	Shard2D::Sprite* childSprite; 
	Shard2D::Sprite* superChildSprite;

	Shard2D::TextField* fpsCounter;
	Shard2D::TextField* runtimeText;

	float runtime = 0;
};

