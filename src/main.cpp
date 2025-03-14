#include "App.hpp"
#include "Map.hpp"

#include "Core/Context.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    App app;
    Map gameMap(10,10);
    gameMap.SetTile(2,3,'#');
    gameMap.Render();

    while (!context->GetExit()) {
        switch (app.GetCurrentState()) {
            case App::State::START:
                app.Start();
                break;

            case App::State::UPDATE:
                app.Update();
                break;

            case App::State::END:
                app.End();
                context->SetExit(true);
                break;
        }
        context->Update();
    }
    return 0;
}
