#include "Application.h"

#include <iostream>

int main(){
    Engine::AppSpecifications specs{
        "Game of Life",
        500,
        500,
        16, // 16ms for 60FPS (1.0 / 60.0)
    };

    Engine::Application app(specs);

    app.Loop();

    return 0;
}
