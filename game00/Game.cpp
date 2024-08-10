#include "Game.h"
#include "physics.h"
#include "ResourceManager.h"
#include "GFieldsCollection.h"
Game::Game(ProjectHandler& projectHandler)
    :GprojectHandler(projectHandler)
{
}
void Game::GameLoop()
{

	//------------------------------initialize------------------------------

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Gra made by ja!");
	window.setFramerateLimit(60);

    ResourceManager manager(GprojectHandler.getTexturesFile());
    manager.LoadResource();
    GFieldsCollection collection;
    GRenderer renderer(window);

    sf::View view({ 160.f, 140.f }, { 160.f,90.f });
    

	//------------------------------initialize------------------------------


	//------------------------------load------------------------------
    
    physics::init();
    collection.GFinit(GprojectHandler.getMapFile());
    view.reset(sf::FloatRect(100.f, 100.f, 16.f, 9.f));
    view.setCenter(collection.GetFieldCollection().at(0).GetPosition());
    sf::Clock clock;
	
    //------------------------------load------------------------------

    while (window.isOpen())
    {
        sf::Time deltaTiameTimer = clock.restart();
        float deltaTime = deltaTiameTimer.asSeconds();
        //------------------------------update------------------------------

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        update(deltaTime);
        //------------------------------update------------------------------

        //------------------------------draw------------------------------
        window.clear(sf::Color::Color(156, 156, 166, 255));
        window.setView(view);
        render(window, collection, manager, renderer);

        window.display();
        //------------------------------draw------------------------------
    }
}

void Game::update(float& deltatime)
{
    physics::update(deltatime);
}

void Game::render(sf::RenderTarget& target, const GFieldsCollection& collection, const ResourceManager& manager, GRenderer& renderer)
{

    for (auto i :collection.GetFieldCollection())
    {
        renderer.draw(i, manager);
    }
    physics::debugDraw(renderer);
}
