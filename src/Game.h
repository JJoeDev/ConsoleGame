#ifndef GAME_H
#define GAME_H

#include <cstdint>
#include <memory>
#include <vector>
#include <string>

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

    std::vector<std::vector<int>> m_grid;
    mutable std::string m_drawBuffer;
};

#endif //GAME_H
