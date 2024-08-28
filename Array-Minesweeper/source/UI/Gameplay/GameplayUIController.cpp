#include "../../header/UI/Gameplay/GameplayUIController.h"
#include "../../header/Main/GameService.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Event/EventService.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"

#include <iomanip>   // For std::setw, std::setfill
#include <sstream>   // For std::stringstream

namespace UI
{
    namespace Gameplay
    {
        using namespace Global;
        using namespace UIElement;
        using namespace Main;
        using namespace Graphics;
        using namespace Sound;

        GameplayUIController::GameplayUIController()
        {
            createTexts();
        }

        GameplayUIController::~GameplayUIController()
        {
            delete(mine_text);
            delete(time_text);
        }

        void GameplayUIController::createTexts()
        {
            mine_text = new TextView();
            time_text = new TextView();
        }

        void GameplayUIController::initialize()
        {
            initializeTexts();
        }

        void GameplayUIController::update()
        {
            updateMineText();
            updateTimeText();
        }

        void GameplayUIController::render()
        {
            mine_text->render();
            time_text->render();
        }

        void GameplayUIController::show()
        {
            mine_text->show();
            time_text->show();
        }

        void GameplayUIController::initializeTexts()
        {
            initializeMineText();
            initializeTimeText();
        }

        void GameplayUIController::initializeMineText()
        {
            mine_text->initialize("000", sf::Vector2f(mine_text_left_offset, mine_text_top_offset), FontType::ROBOTO, font_size, text_color);
        }

        void GameplayUIController::initializeTimeText()
        {
            time_text->initialize("000", sf::Vector2f(time_text_left_offset, time_text_top_offset), FontType::ROBOTO, font_size, text_color);
        }

        void GameplayUIController::updateMineText()
        {
            int mines_count = ServiceLocator::getInstance()->getGameplayService()->getMinesCount();

            std::stringstream stream;
            stream << std::setw(3) << std::setfill('0') << mines_count;
            std::string string_mine_count = stream.str();

            mine_text->setText(string_mine_count);
            mine_text->update();
        }

        void GameplayUIController::updateTimeText()
        {
            int remaining_time = ServiceLocator::getInstance()->getGameplayService()->getRemainingTime();

            std::stringstream stream;
            stream << std::setw(3) << std::setfill('0') << remaining_time;
            std::string string_remaining_time = stream.str();

            time_text->setText(string_remaining_time);
            time_text->update();
        }
    }
}