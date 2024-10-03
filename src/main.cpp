#include "Application.h"

#include <iostream>

int main(){
    Engine::AppSpecifications specs{
        "Game of Life",
        500,
        500,
    };

    Engine::Application app(specs);

    app.Loop();

    return 0;
}
