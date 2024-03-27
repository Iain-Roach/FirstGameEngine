#include "EngineApp.h"
#include <d2d1.h>
#include <wincodec.h>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <filesystem>
#include "Input.h"


namespace Ferrus
{
    EngineApp::EngineApp() :  hwnd(NULL), sprite(NULL)
    {
        
    }

    EngineApp::~EngineApp()
    {
        if (sprite) delete sprite;
        delete& Input::GetInstance();

    }

    HRESULT EngineApp::Run(HINSTANCE hInstance, int nCmdShow)
    {
        if (FAILED(Initialize(hInstance, nCmdShow)))
        {
            return -1; // Initialize failed
        }

        MessageLoop();

        delete graphics;

        return 0;
    }

    void EngineApp::Update()
    {
        ySpeed += 1.0f;
        yPos += ySpeed;

        t++;
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        // GetClientRect not working?
        if (yPos > 600)
        {
            yPos = 600;
            ySpeed = -30.0f;

        }

        Input& input = Input::GetInstance();

        float speed = 1.0f;




        auto view = registry.view<TransformComponent, SpriteComponent>();
        for (entt::entity entity : view)
        {
            if (entity == entt::entity(0))
            {
                auto& transform = view.get<TransformComponent>(entity);

                if (input.KeyDown('W')) { transform.Pos.y += -speed; }
                if (input.KeyDown('S')) { transform.Pos.y += speed; }
                if (input.KeyDown('A')) { transform.Pos.x += -speed; }
                if (input.KeyDown('D')) { transform.Pos.x += speed; }









                //transform.Pos.x += sinf(t / 100);
            }
            auto& sprite = view.get<SpriteComponent>(entity);
        }

        auto collisionView = registry.view<CollisionComponent, TransformComponent>();
            for (entt::entity entity : collisionView)
            {
                auto& collision = collisionView.get<CollisionComponent>(entity);
                collision.IsColliding = false;
            }
            



            for (entt::entity entity : collisionView)
            {
                auto& collision = collisionView.get<CollisionComponent>(entity);
                auto& transform1 = collisionView.get<TransformComponent>(entity);

                for (entt::entity otherEntity : collisionView)
                {
                    if (entity != otherEntity)
                    {
                        auto& otherCollision = collisionView.get<CollisionComponent>(otherEntity);
                        auto& transform2 = collisionView.get<TransformComponent>(otherEntity);


                        float distance = sqrtf(powf((transform2.Pos.x - transform1.Pos.x), 2) + (powf((transform2.Pos.y - transform1.Pos.y), 2)));
                        if (distance <= collision.Radius + otherCollision.Radius)
                        {
                            collision.IsColliding = true;
                            otherCollision.IsColliding = true;
                        }
                    }
                    
                }
            }

    }

    void EngineApp::OnRender()
    {
        graphics->BeginDraw();

        graphics->ClearScreen(0.3f, 0.3f, 0.5f);
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        graphics->DrawCircle(375.0f, yPos, 50.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        // rotates clockwise 20 degrees.
        graphics->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(90, D2D1::Point2F(50, 50)));                      // For rotations we would have to rotate the render target before and after each draw. would use the transform component for center position of rotation
        // test circle to get location on rendertarget
        graphics->DrawCircle(50, 50, 5, 1.0f, 0.0f, 0.0f, 1.0f);

        // Scaling sprite still needs the center of the sprite
        graphics->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Scale(4.0f, 4.0f, D2D1::Point2F(50, 50)));

        sprite->Draw(50.0f, 50); // We can pass the transform from the transform component as a value when drawing the sprite component.
        graphics->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

        

        auto spriteView = registry.view<TransformComponent, SpriteComponent>();
        for (auto entity : spriteView)
        {
            auto& transformComp = spriteView.get<TransformComponent>(entity);
            auto& spriteComp = spriteView.get<SpriteComponent>(entity);

            /*graphics->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(20, D2D1::Point2F(transformComp.Pos.x, transformComp.Pos.y)));
            graphics->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Scale(4.0f, 4.0f, D2D1::Point2F(transformComp.Pos.x, transformComp.Pos.y)));*/
            // Create a combined transformation matrix for rotation and scale
            D2D1_MATRIX_3X2_F combinedTransform = D2D1::Matrix3x2F::Rotation(transformComp.Rot, D2D1::Point2F(transformComp.Pos.x, transformComp.Pos.y))
                * D2D1::Matrix3x2F::Scale(transformComp.Scale.x, transformComp.Scale.y, D2D1::Point2F(transformComp.Pos.x, transformComp.Pos.y));

            // Set the combined transformation matrix
            graphics->getRenderTarget()->SetTransform(combinedTransform);

            sprite = new Sprite(spriteComp.FilePath, graphics);
            sprite->Draw(transformComp.Pos.x, transformComp.Pos.y);

            graphics->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

            //graphics->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());

            //Sprite drawSprite = Sprite(spriteComp.BitMap, graphics);

            //drawSprite.Draw(transformComp.Pos.x, transformComp.Pos.y);
           // graphics->getRenderTarget()->DrawBitmap(
           //     spriteComp.BitMap,
           //     D2D1::RectF((transformComp.Pos.x - 16.0f), (transformComp.Pos.y - 16.0f), spriteComp.BitMap->GetSize().width + transformComp.Pos.x - 16.0f, spriteComp.BitMap->GetSize().height + transformComp.Pos.y - 16.0f),
           //     1.0f,
           //     D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
           //     D2D1::RectF(0.0f, 0.0f, spriteComp.BitMap->GetSize().width, spriteComp.BitMap->GetSize().height));

        }



        // im thinking: when drawing sprites to screen. 
        // 1st create loop that will loop threw all the existing spritecomponenets
        // 2nd create variable of the center of the sprite
        // 3rd rotate rendertarget
        // 4th scale rendertarget
        // 5th draw sprite at specific position
        // 6th reset rendertarget
        // loop until no more sprites need to be drawn.

        

        // Testing transform component:
        auto view = registry.view<TransformComponent, CollisionComponent>();
        for (auto entity : view)
        {
            auto& transformComp = view.get<TransformComponent>(entity);
            auto& collisionComp = view.get<CollisionComponent>(entity);

            if (collisionComp.IsColliding)
            {
                graphics->DrawCircle(transformComp.Pos.x, transformComp.Pos.y, collisionComp.Radius, 0.0f, 1.0f, 1.0f, 1.0f);
            }
            else
            {
                graphics->DrawCircle(transformComp.Pos.x, transformComp.Pos.y, collisionComp.Radius, 1.0f, 0.0f, 1.0f, 1.0f);
            }
            
        }


        





        


        graphics->EndDraw();
    }

    void EngineApp::MessageLoop()
    {
        // Message Loop
        MSG message;
        message.message = WM_NULL;
        while (message.message != WM_QUIT)
        {
            if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&message);
                DispatchMessage(&message); // sends message to WndPrc
            }
            else
            {
                Input::GetInstance().Update();


                // Update
                Update();

                // Render
                OnRender();



                Input::GetInstance().EndOfFrame();
            }
        }
        

        delete graphics;
    }

    HRESULT EngineApp::initFileLoader(Graphics* gfx)
    {
        FileLoader fl = FileLoader(gfx);
        fileLoader = &fl;
        return S_OK;
    }

    FileLoader* EngineApp::GetFileLoader()
    {
        return fileLoader;
    }

    HRESULT EngineApp::Initialize(HINSTANCE hInstance, int nCmdShow)
	{
        // Can move this stuff to EngineApp using method commented below ( used to be in engineapp.initialize())
        WNDCLASSEX windowClass;
        ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
        windowClass.hInstance = hInstance;
        windowClass.lpfnWndProc = WndProc;
        windowClass.lpszClassName = L"MainWindow"; // making the LPWSTR into LPCWSTR and then back fixed error???
        windowClass.style = CS_HREDRAW | CS_VREDRAW; // redraw when resized vertically / horizontally

        RegisterClassExW(&windowClass);


        RECT clientArea = { 0, 0, 800, 600 };
        AdjustWindowRectEx(&clientArea, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW); // Calculating the width and height so the client area is accurate
        HWND windowHandle = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, L"MainWindow", L"Direct2D Engine", WS_OVERLAPPEDWINDOW, 100, 100, clientArea.right - clientArea.left, clientArea.bottom - clientArea.top, NULL, NULL, hInstance, 0);


        if (!windowHandle) return -1;

        graphics = new Graphics();

        if (!graphics->Init(windowHandle))
        {
            delete graphics;
            return -1;
        }

        ShowWindow(windowHandle, nCmdShow);

        Input::GetInstance().Initialize(windowHandle);




        std::filesystem::path currentPath = std::filesystem::current_path();
        std::stringstream stream;
        stream << "Current working directory: " << currentPath << std::endl;
        OutputDebugStringA(stream.str().c_str());

        // Will need to add error handling incase of incorrect sprite names
        try {
            sprite = new Sprite(L"Assets\\TestSprite.png", graphics);
            /*sprite = new Sprite(L"E:\\Repo\\IndependentStudyEngine\\FirstEngine\\TestSite\\Assets\\TestSprite.png", graphics);*/
        }
        catch (const std::runtime_error& e) {
            std::stringstream ss;
            ss << "Runtime error: " << e.what() << std::endl;
            OutputDebugStringA(ss.str().c_str());
        }
        
        // Registry Testing Zone
        entt::entity testEntity = registry.create();
        auto& transformTest = registry.emplace<TransformComponent>(testEntity, D2D1::Point2F(200.0f, 400.0f), 0.0f, D2D1::Point2F(1.0f, 1.0f));
        entt::entity anotherEntity = registry.create();
        registry.emplace<TransformComponent>(anotherEntity, D2D1::Point2F(600.0f, 400.0f), 0.0f, D2D1::Point2F(1.0f, 1.0f));

        initFileLoader(graphics);

        // Load Files >:(
        /*auto view = registry.view<SpriteComponent>();
        for (auto entity : view)
        {
            auto& spriteComp = view.get<SpriteComponent>(entity);
            Sprite testBitmap = Sprite(spriteComp.FilePath, graphics);
            spriteComp.BitMap = testBitmap.GetBitMap();
        }*/

        return S_OK;
	}

    // Will update graphics->Init to HRESULT
    HRESULT EngineApp::initGraphics(HWND hwnd)
    {
        graphics = new Graphics();
        if (!graphics) {
            return E_FAIL; // failed to allocate memory
        }

        HRESULT hr = graphics->Init(hwnd);
        if (FAILED(hr))
        {
            delete graphics;
            graphics = nullptr;
            return hr;
        }

        return S_OK;

    }
    LRESULT EngineApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_DESTROY) { PostQuitMessage(0); return 0; }

        switch (message)
        {
        case WM_MOUSEWHEEL:
            Input::GetInstance().SetWheelDelta(GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA);
            return 0;
        case WM_INPUT:
            Input::GetInstance().ProcessRawMouseInput(lParam);
            break;
        }


		return DefWindowProcW(hwnd, message, wParam, lParam);
	}
}
