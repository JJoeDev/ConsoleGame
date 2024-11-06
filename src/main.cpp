#include "Application.h"

int main(){
    Engine::AppSpecifications specs{
        "Game of Life", // Title
        500, // Width
        500, // Height
        16, // 16ms for 60FPS (1.0 / 60.0)
    };

    Engine::Application app(specs);

    app.Loop();

    return 0;
}
