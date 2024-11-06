#ifndef GAME_H
#define GAME_H

#include <cstdint>
#include <memory>

#include "RenderEngine.h"

class Game {
public:
    explicit Game(const std::shared_ptr<Renderer::RenderEngine>& renderEngine);
    ~Game();

    void Update();
    void Draw() const;

private:
    std::shared_ptr<Renderer::RenderEngine> m_renderEngine{nullptr};
    uint32_t m_mapX, m_mapY;
    int tmpX = 0, tmpY = 0;
};

#endif //GAME_H
