#include "Game.h"

#include "RenderEngine.h"

Game::Game(const std::shared_ptr<Renderer::RenderEngine>& renderEngine){
    m_renderEngine = renderEngine;

    m_mapX = m_renderEngine->GetFrameX() - 2; // Subtract border
    m_mapY = m_renderEngine->GetFrameY() - m_renderEngine->GetStatusBarY() - 1; // Subtract status bar & the border

    m_grid.resize(m_mapX, std::vector<int>(m_mapY, 0));
}

Game::~Game(){

}

void Game::Update(){
    int x = rand() % m_mapX;
    int y = rand() % m_mapY;
    if(m_grid[x][y] == 0) m_grid[x][y] = 1;
}

void Game::Draw() const{
    m_drawBuffer.clear();

    for(int y = 0; y < m_mapY; ++y){
        for(int x = 0; x < m_mapX; ++x){
            if(m_grid[x][y] == 1){
                //m_renderEngine->DrawCharAtCursor('ø');
                m_drawBuffer += 'a';
            }
            else{
                //m_renderEngine->DrawCharAtCursor(' ');
                m_drawBuffer += ' ';
            }
        }
        m_drawBuffer += '\n';
    }

    m_renderEngine->SetCursorPos(1, 1);
    m_renderEngine->DrawStrAtCursor(m_drawBuffer);
}