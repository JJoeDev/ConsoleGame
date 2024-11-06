#include "Game.h"

#include "RenderEngine.h"

Game::Game(const std::shared_ptr<Renderer::RenderEngine>& renderEngine){
    m_renderEngine = renderEngine;

    m_mapX = m_renderEngine->GetFrameX();
    m_mapY = m_renderEngine->GetFrameY();
}

Game::~Game(){

}

void Game::Update(){
    m_renderEngine->SetCursorPos(tmpX, tmpY);

    if(tmpX >= m_mapX){
        tmpX = 0;
        tmpY++;
    }
    else
        tmpX++;
}

void Game::Draw() const{
    m_renderEngine->DrawCharAtCursor('ø');
}