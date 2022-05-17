#include "ApplicationMain.h"

#include <SDL.h>

#include "Management/Managers.h"
#include "Utils/ShardUtils.h"
#include "Entities/Entity.h"
#include "Tweens/TweensManager.h"

import MathUtils;
import BooleanUtils;

using namespace Shard2D;

void MouseBeginOverlap(MouseEvent* _event)
{
    Shard2D::Log("Begin Overlap");
}

void MouseEndOverlap(MouseEvent* _event)
{
    Shard2D::Log("End overlap");
}

void KeyPressed(KeyboardEvent* _event)
{
    std::cout << "Key pressed: " << _event->GetKeycode() << std::endl;
}

ApplicationMain::ApplicationMain()
{

}

void ApplicationMain::Init()
{
    M_GraphicManager->SetDefaultResolution(1280, 720, true);
    M_GraphicManager->ResizeWindow(1280, 720, WindowType::Window);

    M_ClockManager->EnableFrameRateCap(144);

    for (int i = 0; i < 1; i++)
    {
        Entity* a = new Entity();
        AddToStage(a);
    }

    sprite = new Sprite(M_AssetsManager->GetImageFromPNG("PNGs/Doge"));
    AddToStage(sprite);
    sprite->SetVisibility(true);
    sprite->scaleX = 0.5f;
    sprite->scaleY = 0.5f;
    sprite->x = 640.f;
    sprite->y = 360.f;
    sprite->color = SDL_Color(0, 0, 255, 255);
    sprite->a = 1.f;
    sprite->rotation = 0;
    sprite->centerPivot = true;
    Log("This new sprite is" + std::to_string(sizeof(*sprite)) + "KB");

    childSprite = new Sprite(M_AssetsManager->GetImageFromPNG("PNGs/Doge"));
    childSprite->scaleX = 0.5f;
    childSprite->scaleY = 0.5f;
    childSprite->x = childSprite->width / 4;
    childSprite->y = childSprite->height / 4;
    sprite->AddChild(childSprite);
    childSprite->a = 1;
    childSprite->centerPivot = true;
    childSprite->blockMouseEvents = false;

    for (int i = 0; i < 1; i++)
    {
        superChildSprite = new Sprite(M_AssetsManager->GetImageFromPNG("PNGs/Doge"));
        superChildSprite->scaleX = 0.5f;
        superChildSprite->scaleY = 0.5f;
        superChildSprite->x = -childSprite->width / 4;
        superChildSprite->y = childSprite->height / 4;
        childSprite->AddChild(superChildSprite);
        superChildSprite->a = 1.f;
        superChildSprite->centerPivot = true;
        superChildSprite->blockMouseEvents = false;
    }

    fpsCounter = new TextField("", "Fonts/arial", 36);
    fpsCounter->y = 670;
    AddToStage(fpsCounter);

    runtimeText = new TextField("Test", "Fonts/arial", 36);
    runtimeText->y = 620;
    AddToStage(runtimeText);

    for (int i = 0; i < 1; i++)
    {
        TextField* b = new TextField("This is a sad day for ulthuan, when Asurs fight Asurs within sight of the white tower!", "Fonts/arial", 36);
        b->scaleX = 1;
        b->scaleY = 1;
        b->centerPivot = true;
        b->x = 640;
        b->y = 50;
        b->width = 640;
        b->SetColor(SDL_Color(0, 0, 255, 255));
        AddToStage(b);
    }

    /*TextField* b = new TextField("This is a sad day for ulthuan, when Asurs fight Asurs within sight of the white tower!", "arial", 72);
    b->scaleX = 1;
    b->scaleY = 1;
    b->centerPivot = true;
    b->x = 640;
    b->y = 360;
    b->SetColor(SDL_Color(255, 255, 0, 255));
    AddToStage(b);*/

    sprite->AddEventListener(MouseEvent::BeginOverlap, &MouseBeginOverlap);
    sprite->AddEventListener(MouseEvent::EndOverlap, &MouseEndOverlap);
    sprite->AddEventListener(KeyboardEvent::ButtonPressed, &ApplicationMain::TestMethod, this);
    sprite->AddEventListener(KeyboardEvent::ButtonReleased, &ApplicationMain::TestMethod2, this);

    //ITween* a = CreateTween(sprite->x, 1280.f, 3)->Ease(EaseType::BounceOut)->Repeat(-1)->Reflect()->Delay(3);
    //StartTween(a);

    ITween* b = CreateTween(sprite->scaleX, 1.25f, 0.5f)->Ease(EaseType::SineInOut)->Repeat(-1)->Reflect()->Delay(2);
    ITween* c = CreateTween(sprite->scaleY, 1.25f, 0.5f)->Ease(EaseType::SineInOut)->Repeat(-1)->Reflect()->Delay(2);
    ITween* d = CreateTween(sprite->rotation, 360.f, 20.f)->Ease(EaseType::SineInOut)->Repeat(-1)->Reflect()->Delay(2);
    //StartTween(b);
    //StartTween(c);
    StartTween(d);

    sprite->rotation = 0;

    //sprite->AddEventListener<Event>("TestEvent", &EventDispatched);
    //sprite->AddEventListener<MouseEvent>("TestEvent", &SecondEventDispatched);
}

void ApplicationMain::Update()
{

    /*if (sprite->HasEventListener<KeyboardEvent, ApplicationMain>(KeyboardEvent::ButtonPressed, &ApplicationMain::TestMethod, this))
    {
        std::cout << "EventListener Found!" << std::endl;
        sprite->RemoveEventListener<KeyboardEvent, ApplicationMain>(KeyboardEvent::ButtonPressed, &ApplicationMain::TestMethod, this);
        std::cout << "EventListener Removed!" << std::endl;
    }*/

    //Log(sprite->rotation);

    //if (sprite->HasEventListener<MouseEvent>(MouseEvent::BeginOverlap, &MouseBeginOverlap))
    //{
        //std::cout << "EventListener Found!" << std::endl;
        //sprite->RemoveEventListener<MouseEvent>(MouseEvent::BeginOverlap, &MouseBeginOverlap);
        //std::cout << "EventListener Removed!" << std::endl;
    //}

    fpsCounter->SetText("FPS: " + std::to_string(int(M_ClockManager->GetFPS())));

    runtime += M_ClockManager->GetDeltaTime();
    runtimeText->SetText("Runtime: " + std::to_string(runtime) + " seconds");
    //point->x = sprite->RenderingX();
    //point->y = sprite->RenderingY();

    //SDL_Event e;
    //childSprite->rotation -= 180 * M_ClockManager->GetDeltaTime();
    //superChildSprite->rotation += 360 * M_ClockManager->GetDeltaTime();
    //sprite->rotation += 30 * M_ClockManager->GetDeltaTime();

   

    /*while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT:
            Managers::gameManager->ExitGame();

        case SDL_KEYDOWN:
           //Managers::gameObjectsManager->RemoveObjectFromStage(sprite);
            //sprite->rotation += 360 * M_ClockManager->GetDeltaTime();
            //sprite->DispatchEvent<Event>("TestEvent");
            //sprite->RemoveEventListener<Event>("TestEvent", &EventDispatched);
            //sprite->RemoveEventListener("TestEvent", &EventDispatched);
            break;
        case SDL_KEYUP:
            //Managers::gameObjectsManager->AddObjectToStage(sprite);

            break;
        case SDL_MOUSEBUTTONDOWN:

            //sprite->DispatchEvent<MouseEvent>("TestEvent");
            //sprite->RemoveEventListener<MouseEvent>("TestEvent", &SecondEventDispatched);
            
            //int mouseX = 0;
            //int mouseY = 0;
            //if (SDL_GetMouseState(&mouseX, &mouseY))
            //{
            //    std::cout << mouseX << " - " << mouseY << std::endl;
            //}
            //
            //if (PointInsideRect(Vector2(mouseX, mouseY), Vector2(sprite->RenderingX(), sprite->RenderingY()), sprite->width * sprite->GlobalScaleX(), sprite->height * sprite->GlobalScaleY(), sprite->GlobalRotation()))
            //    std::cout << "Point Inside!" << std::endl;
           
            break;
        }
    }*/
}

void ApplicationMain::TestMethod(KeyboardEvent* _event)
{
    //M_GraphicManager->ResizeWindow(640, 360, WindowType::Window);
}

void ApplicationMain::TestMethod2(KeyboardEvent* _event)
{
    //M_GraphicManager->ResizeWindow(1280, 720, WindowType::Window);
}
