#pragma once
#include "../../header/Graphics/GraphicService.h"
#include "../../header/Event/EventService.h"
#include "../../header/Gameplay/Board/BoardService.h"
#include "../../header/UI/UIService.h"
#include "../../header/Sound/SoundService.h"

namespace Global
{
    class ServiceLocator
    {
    private:
        Graphics::GraphicService* graphic_service;
        Event::EventService* event_service;
        Gameplay::Board::BoardService* board_service;
        Sound::SoundService* sound_service;
        UI::UIService* ui_service;

        ServiceLocator();
        ~ServiceLocator();

        void createServices();
        void clearAllServices();

    public:
        static ServiceLocator* getInstance();

        void initialize();
        void update();
        void render();

        Graphics::GraphicService* getGraphicService();
        Event::EventService* getEventService();
        Gameplay::Board::BoardService* getBoardService();
        Sound::SoundService* getSoundService();
        UI::UIService* getUIService();
        void deleteServiceLocator();
    };
}