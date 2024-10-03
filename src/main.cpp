#include "Application.h"

#include <iostream>

int main(){
    Engine::AppSpecifications specs{
        .title = "Game of Life",
        .width = 500,
        .height = 500,
    };

    Engine::Application app(specs);

    app.Loop();

    std::cin.get();

    return 0;
}
