#include "MainSpace.h"
#include <iostream>
#include "filesHandler.h"
#include "CollectionHandler.h"

void MainSpace::Core()
{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                              initialize
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (!font.loadFromFile("fonts/Montserrat/Montserrat-VariableFont_wght.ttf")){};

    if(!openProject())
    {
        exit(0);
    }

    toolBar.Initialize(font);
    infoBar.Initialize(font);
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Engine made by me");

    Renderer renderer(window);
    filesHandler fHandler;
    ResourceManager manager(projectHandler.getTexturesFile());
    CollectionHandler Chandler(projectHandler.getMapFile());

    manager.LoadResource();
    Chandler.loadCollection(Elements);

    view.reset(sf::FloatRect(100.f, 100.f, 120.f, 80.f));
    view.setViewport(sf::FloatRect(0.f, 0.2f, 0.8f, 0.8f));

    ToolBarView.reset(sf::FloatRect(1000.f, 1000.f, 1000.f, 200.f));
    ToolBarView.setViewport(sf::FloatRect(0.f, 0.f, 0.8f, 0.2f));
    ToolBarView.setCenter(sf::Vector2f(10000.f,10000.f));

    InfoBarView.reset(sf::FloatRect(1000.f, 1000.f, 240.f, 800.f));
    InfoBarView.setViewport(sf::FloatRect(0.8f, 0.f, 0.2f, 1.f));
    InfoBarView.setCenter(sf::Vector2f(50000.f, 50000.f));
    
    
    window.setFramerateLimit(60);

    sf::IntRect viewport = window.getViewport(view);
    sf::IntRect viewport2 = window.getViewport(ToolBarView);
    sf::IntRect viewport3 = window.getViewport(InfoBarView);

    sf::Event event;
    Controls controls(event, window);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                              end initialize
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    while (window.isOpen())
    {   
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //                                              Update
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
       
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

            if (toolBar.shapeSelecting && ElementSelected != -1 )
            {
                window.setView(view);
                view.setCenter(
                    { Elements.getField(ElementSelected).GetPosition().x + Elements.getField(ElementSelected).GetSize().x / 2
                            ,
                      Elements.getField(ElementSelected).GetPosition().y + Elements.getField(ElementSelected).GetSize().y / 2
                    }
                );
            }

            if (viewport.contains(pixelPos))
            {
                controls.ControlsOnMainView(view, Drag, action, OldPos);
            }

            if(viewport.contains(pixelPos) && toolBar.shapeSelecting&& selected)
            {
                window.setView(view);
                ControlsForHitbox(event, window, controls);
                     
            }
            else if (viewport.contains(pixelPos))// action if mouse on main view
            {
                window.setView(view);
                ControlsForFields(event, window, controls);//manipulating objects
            }
                
            if (viewport2.contains(pixelPos))// action if mouse on tool view
            {
                window.setView(ToolBarView);
                switch (toolBar.Controls(event, window, Elements,selected)) // selecting tools
                {

                case BA_Delete:
                {
                    if (ElementSelected != -1)
                    {
                        Elements.DleteFromCollection(ElementSelected);
                        ElementSelected = -1;
                        selected = false;
                        toolBar.shapeSelecting = false;
                        break;
                    }
                    break;
                }

                case BA_AddHitbox:// adding hitboxes
                {
                    if (selected)
                    {
                        if (!toolBar.shapeSelecting)
                        {
                            showHitboxes = false;
                        }
                        else 
                        {
                            showHitboxes = true;
                        }
                    }
                    break;
                }
                case BA_ShowHitbox:// show\hide hitboxes
                {
                    if (showHitboxes)
                    {
                        showHitboxes = false;
                    }
                    else
                    {
                        showHitboxes = true;
                    }
                    break;
                }
                case BA_AddSprite:
                {
                    std::string filePath = fHandler.getFilePath();
                    std::string fileName = filePath.substr(filePath.find_last_of("/\\") + 1);
                    fileName = fileName.substr(0, fileName.find_last_of(".\\"));
                    if (filePath != "")
                    {
                        manager.AddResuorce(fileName, filePath);
                        manager.saveResource();
                    }
                    break;
                }
                case BA_CreateProject:
                {
                    Chandler.saveCollection(Elements);
                    //projectHandler.CreateDirectoryTree("kurczak");
                    break;
                }
                default:
                    break;
                }
                    
            }
            if (viewport3.contains(pixelPos))// action if mouse on info view
            {
                window.setView(InfoBarView);
                if (infoBar.Controls(event, window)) // modify info 
                {
                    if(ElementSelected!=-1)//if modified and alement is selected from collection
                        infoBar.updateField(Elements.getField(ElementSelected));// update element
                }

            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //                                              end update
        ////////////////////////////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //                                              display
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        window.clear(sf::Color::Color(156,156,166,255));
        
        Render(window, renderer,manager);
        
        window.display();
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //                                              end display
        ////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
}

void MainSpace::Render(sf::RenderTarget& target, Renderer& renderer,ResourceManager& manager)
{
    //toolbar
    target.setView(ToolBarView);
    
    toolBar.DrawToolBar(target); // displaing tool view elements  

    //infobar

    target.setView(InfoBarView);

    infoBar.DrawInfoBar(target, manager);// displaing info view elements  

    // main window
    target.setView(view);
    int a = 0;
    
    for (auto i : Elements.GetFieldCollection())// displayin hitboxes 
    {
        if (a == ElementSelected)
        {
            renderer.draw(i, manager, true);
        }
        else
        {
            renderer.draw(i, manager,false);
        }
        if (toolBar.shapeSelecting || showHitboxes )
        {
            renderer.drawHitbox(i, manager);
        }
        a++;
    }

    if (toolBar.shapeSelecting)//displaying convex shape build elements 
    {
        if (convexShapeCordinats.size() < 2)// if only startig point diplaing circle
        {
            for (auto i : convexShapeCordinats)
            {
                sf::CircleShape circle(0.05f);
                circle.setPosition(i);
                circle.setOrigin(circle.getRadius(), circle.getRadius());
                circle.setFillColor(sf::Color::Color(153, 241, 94, 126));
                target.draw(circle);
            }
        }
        else// if more than 1 point drawing lines
        {
            sf::Vector2f point2{1111111.f,1111111.f };
            sf::Vector2f point1;
            for (auto i : convexShapeCordinats)
            {
                point1 = i;

                if (point2.x != 1111111.f && point2.y != 1111111.f)
                {
                    sf::Vertex line[] =
                    {
                        sf::Vertex(point1),
                        sf::Vertex(point2)
                    };

                    target.draw(line, 2, sf::Lines);
                }

                point2 = point1;
            }
        }
    }
}

void MainSpace::ControlsForFields(sf::Event& event, sf::RenderWindow& window, Controls controls)
{

    controls.Zoom(view);

    window.setView(view);

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);//mouse position in window

    if (sf::Event::MouseMoved)
    {
        if (action == 1 && Drag)// new camera position
        {
            NewPos = worldPos;

            sf::Vector2f deltaPos = OldPos - NewPos;// by getting delta pos you knew how much your position on window change so you can move  
            view.setCenter(view.getCenter() + deltaPos);// moving camera
            window.setView(view);

            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            OldPos = worldPos;
        }

        if (action == 2 && selected && Drag)//new elemnt position
        {
            Elements.update();
            NewPos = worldPos;

            sf::Vector2f deltaPos = OldPos - NewPos;// by getting delta pos you knew how much your position on window change so you can move object


            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            OldPos = worldPos;

            sf::Vector2f pos = Elements.getField(ElementSelected).GetPosition();

            pos -= deltaPos;

            Elements.getField(ElementSelected).SetPosition(pos);//moving object
        }

        if (action == 3 && selected && Drag)// new element size
        {
            Elements.update();
            NewPos = worldPos;

            sf::Vector2f deltaPos = OldPos - NewPos;// by getting delta pos you knew how much your position on window change so you can change objcet size


            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            OldPos = worldPos;

            sf::Vector2f Nsize = Elements.getField(ElementSelected).GetSize();

            Nsize -= deltaPos;
            if (Nsize.x < 0.1)
            {
                Nsize.x = 0.1;
            }
            if (Nsize.y < 0.1)
            {
                Nsize.y = 0.1;
            }
            Elements.getField(ElementSelected).SetSize(Nsize);//change object size
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)  && !toolBar.shapeSelecting && action == 0)//selectiong element to change
    {
        int count = 0;
        for (auto i : Elements.GetFieldCollection())// checking every element 
        {
            float mouseX = worldPos.x;
            float mouseY = worldPos.y;

            float elementX = i.GetPosition().x;// top left corner
            float elementY = i.GetPosition().y;

            float elementEndX = i.GetPosition().x + i.GetSize().x;// bottom right corner 
            float elementEndY = i.GetPosition().y + i.GetSize().y;

            if ((mouseX <elementEndX && mouseX > elementX && mouseY < elementEndY && mouseY > elementY) ) // checking if mouse is on any element
            {
                ElementSelected = count;
                infoBar.FieldInfo(Elements.getField(count));// update on field info
                selected = true;
                break;
            }
            else if (count == Elements.GetFieldCollection().size()-1)
            {
                selected = false;
            }
            count++;
        }
        if (!selected)
        {
            ElementSelected = -1;
            
        }
    }

    if (ElementSelected != -1 )
    {
        controls.BoundryOfelemt(Elements.getField(ElementSelected).GetPosition(), Elements.getField(ElementSelected).GetSize());
        infoBar.FieldInfo(Elements.getField(ElementSelected));// update on field info
    }
    controls.ControlsOnMainView(view, Drag, action, OldPos);
}

void MainSpace::ControlsForHitbox(sf::Event& event, sf::RenderWindow& window, Controls controls)
{   
    if (polygonPtr != nullptr)
    {
        controls.BoundryOfelemt(polygonPtr->polygons.getGlobalBounds());
    }
    else if (rectanglePtr != nullptr)
    {
        controls.BoundryOfelemt(rectanglePtr->rectangles.getGlobalBounds());
    }
    else if (irregularPtr != nullptr)
    {
        controls.BoundryOfelemt(irregularPtr->irregular.getGlobalBounds());
    }
    controls.ControlsOnMainView(view, Drag, action, OldPos);

    controls.Zoom(view);

    window.setView(view);

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);//mouse position in window

    if (toolBar.ActionsOnHitbox ==HA_None)
    {
        convexShapeCordinats.clear();
    }
    if (toolBar.ActionsOnHitbox == HA_Modyfi )// modyfing hitbox
    {
        for (auto& i : Elements.getField(ElementSelected).GetHitboxes().polygons)
        {
            if (i.polygons.getGlobalBounds().contains(worldPos))
            {
                i.polygons.setFillColor(sf::Color::Color(255, 163, 0, 126));
                polygonPtr = &i;
                rectanglePtr = nullptr;
                irregularPtr = nullptr;
                
            }
            else
            {
                i.polygons.setFillColor(sf::Color::Color(153, 241, 94, 126));
            }
        }
        for (auto& i : Elements.getField(ElementSelected).GetHitboxes().rectangles)
        {
            if (i.rectangles.getGlobalBounds().contains(worldPos))
            {
                i.rectangles.setFillColor(sf::Color::Color(255, 163, 0, 126));
                rectanglePtr = &i;
                polygonPtr = nullptr;
                irregularPtr = nullptr;
            }
            else
            {
                i.rectangles.setFillColor(sf::Color::Color(153, 241, 94, 126));
            }
        }
        for (auto& i : Elements.getField(ElementSelected).GetHitboxes().irregular)
        {
            if (i.irregular.getGlobalBounds().contains(worldPos))
            {
                i.irregular.setFillColor(sf::Color::Color(255, 163, 0, 126));
                irregularPtr = &i;
                rectanglePtr = nullptr;
                polygonPtr = nullptr;
            }
            else
            {
                i.irregular.setFillColor(sf::Color::Color(153, 241, 94, 126));
            }
        }

        if (action == 2 && selected && Drag)//new elemnt position
        {
            Elements.update();
            NewPos = worldPos;

            sf::Vector2f deltaPos = OldPos - NewPos;// by getting delta pos you knew how much your position on window change so you can move object


            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

            OldPos = worldPos;

            sf::Vector2f pos;

            if (polygonPtr != nullptr)
            {
                pos = polygonPtr->offset;
                pos -= deltaPos;
                polygonPtr->offset = pos;
            }
            else if (rectanglePtr!= nullptr)
            {
                pos = rectanglePtr->offset;
                pos -= deltaPos;
                rectanglePtr->offset = pos;
            }
            else if(irregularPtr != nullptr)
            {
                pos = irregularPtr->offset;
                pos -= deltaPos;
                irregularPtr->offset = pos;
            }
        }
        if (action == 3 && selected && Drag)// new element size
        {
            NewPos = worldPos;

            sf::Vector2f deltaPos = OldPos - NewPos;// by getting delta pos you knew how much your position on window change so you can change objcet size


            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            OldPos = worldPos;


            if (polygonPtr != nullptr)
            {
                float radius = polygonPtr->polygons.getRadius();
                radius -= deltaPos.x;
                if (radius < 0.1)
                {
                    radius = 0.1;
                }
                polygonPtr->polygons.setRadius(radius);
            }
            else if (rectanglePtr != nullptr)
            {
                sf::Vector2f size = rectanglePtr->rectangles.getSize();
                size -= deltaPos;
                if (size.x < 0.1)
                {
                    size.x = 0.1;
                }
                if (size.y < 0.1)
                {
                    size.y = 0.1;
                }
                rectanglePtr->rectangles.setSize(size);
            }
            else if (irregularPtr != nullptr)
            {
                //pos = irregularPtr->offset;
                //pos -= deltaPos;
                //irregularPtr->offset = pos;
            }
        }
    }
    else if(toolBar.ActionsOnHitbox == HA_Delete)// delete hitbox
    {
        int index = 0;
        for (auto& i : Elements.getField(ElementSelected).GetHitboxes().polygons)
        {
            if (i.polygons.getGlobalBounds().contains(worldPos))
            {
                i.polygons.setFillColor(sf::Color::Color(255, 0, 0, 126));
                if (sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left && i.polygons.getGlobalBounds().contains(worldPos))
                {
                    Elements.getField(ElementSelected).GetHitboxes().polygons.erase(Elements.getField(ElementSelected).GetHitboxes().polygons.begin() + index);
                    break;
                }
            }
            else
            {
                i.polygons.setFillColor(sf::Color::Color(153, 241, 94, 126));
            }
            index++;
        }
        index = 0;
        for (auto& i : Elements.getField(ElementSelected).GetHitboxes().rectangles)
        {
            if (i.rectangles.getGlobalBounds().contains(worldPos))
            {
                i.rectangles.setFillColor(sf::Color::Color(255, 0, 0, 126));
                if (sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left && i.rectangles.getGlobalBounds().contains(worldPos))
                {
                    Elements.getField(ElementSelected).GetHitboxes().rectangles.erase(Elements.getField(ElementSelected).GetHitboxes().rectangles.begin() + index);
                    break;
                }
            }
            else
            {
                i.rectangles.setFillColor(sf::Color::Color(153, 241, 94, 126));
            }
            index++;
        }
        index = 0;
        for (auto& i : Elements.getField(ElementSelected).GetHitboxes().irregular)
        {
            if (i.irregular.getGlobalBounds().contains(worldPos))
            {
                i.irregular.setFillColor(sf::Color::Color(255, 0, 0, 126));
                if (sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left && i.irregular.getGlobalBounds().contains(worldPos))
                {
                    Elements.getField(ElementSelected).GetHitboxes().irregular.erase(Elements.getField(ElementSelected).GetHitboxes().irregular.begin()+index);
                    break;
                }
            }
            else
            {
                i.irregular.setFillColor(sf::Color::Color(153, 241, 94, 126));
            }
            index++;
        }
    }
    else if (toolBar.ActionsOnHitbox == HA_Convex)//adding convex shape
    {
        if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
        {
            convexShapeCordinats.push_back(worldPos);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z && convexShapeCordinats.size()>0)
        {
            convexShapeCordinats.erase(convexShapeCordinats.begin()+convexShapeCordinats.size()-1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && convexShapeCordinats.size() > 2)
        {
            sf::Vector2f point2;//positon of previus point
            sf::Vector2f point1;//position of actual point
            sf::Vector2f start;//starting position

            float sum = 0;//sum which determinates if point are set clockwise (<0), counter clockwise (>0) or linear (=0)
            int index = 0;

            for (auto i : convexShapeCordinats)
            {
                point1 = i;

                if (index == 0)
                {
                    start = i;
                }
                else if(index == convexShapeCordinats.size())
                {
                    sum += (start.x - point1.x) * (start.y + point1.y);
                }
                else
                {
                    sum += (point1.x - point2.x) * (point1.y + point2.y);
                }
                point2 = point1;
                index++;
            }

            index = 0;

            sf::ConvexShape convexS;
            convexS.setPointCount(convexShapeCordinats.size());

            for (auto i : convexShapeCordinats)
            {
                convexS.setPoint(index, i);
                index++;
            }
            convexS.setFillColor(sf::Color::Color(153, 241, 94, 126));
            sf::Vector2f offset = convexS.getPosition() - Elements.getField(ElementSelected).GetPosition(); // triangle.getPosition() - Elements.getField(ElementSelected).GetPosition();
            sf::Vector2f startsize = Elements.getField(ElementSelected).GetSize();
            Elements.getField(ElementSelected).Addcovex(convexS, offset, startsize);
            convexShapeCordinats.clear();
        }
    }
    else
    {

        if (toolBar.shapeSelecting && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
        {
            switch (toolBar.ActionsOnHitbox )
            {
            case HA_Circle:
            {
                sf::CircleShape circle(0.5f);
                circle.setPosition(worldPos);
                circle.setOrigin(circle.getRadius(), circle.getRadius());
                circle.setFillColor(sf::Color::Color(153, 241, 94, 126));
                sf::Vector2f offset = circle.getPosition() - Elements.getField(ElementSelected).GetPosition();
                sf::Vector2f startsize = Elements.getField(ElementSelected).GetSize();
                Elements.getField(ElementSelected).AddPolygon(circle, offset, startsize);
                toolBar.shapeSelecting = true;
                break;
            }
            case HA_Rectangle:
            {
                sf::RectangleShape rectangle({ 0.5f,0.5f });
                rectangle.setPosition(worldPos);
                rectangle.setFillColor(sf::Color::Color(153, 241, 94, 126));

                rectangle.setOrigin({ rectangle.getSize().x / 2,rectangle.getSize().y / 2 });
                sf::Vector2f offset = rectangle.getPosition() - Elements.getField(ElementSelected).GetPosition();
                sf::Vector2f startsize = Elements.getField(ElementSelected).GetSize();
                Elements.getField(ElementSelected).AddRectangle(rectangle, offset, startsize);
                toolBar.shapeSelecting = true;
                break;
            }
            case HA_Triangle:
            {
                sf::CircleShape triangle(0.5f, 3);
                triangle.setPosition(worldPos);
                triangle.setFillColor(sf::Color::Color(153, 241, 94, 126));

                triangle.setOrigin(triangle.getRadius(), triangle.getRadius());
                sf::Vector2f offset = triangle.getPosition() - Elements.getField(ElementSelected).GetPosition();
                sf::Vector2f startsize = Elements.getField(ElementSelected).GetSize();
                Elements.getField(ElementSelected).AddPolygon(triangle, offset, startsize);
                toolBar.shapeSelecting = true;
                break;
            }
            
            default:
                break;
            }
        }
    }
}

bool MainSpace::openProject()
{
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Engine made by me");
    window.setFramerateLimit(60);
    button bt("open project", { 128.f,36.f }, 18, sf::Color::Color(178, 156, 255, 255), sf::Color::Black, font, { 90, 10 });
    button bt00("create project", { 128.f,36.f }, 18, sf::Color::Color(178, 156, 255, 255), sf::Color::Black, font, { 90, 90 });

    textbox name;
    name.set(18, sf::Color::Black);
    
    name.steFont(font);
    name.setPosition({ 200,90 });
    name.setOutLine({ 120.f,40.f });
    name.setOutColor(sf::Color::Black);
    name.setText("name");
    name.setSelected(true);

    while (window.isOpen())
    {
        //
        //  update
        //
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }
            if (event.type == sf::Event::TextEntered)// typing if selected before 
            {
                name.type(event);

            }
        }
        //
        //  End update
        //

        if (event.type == sf::Event::MouseButtonPressed)//on pressing mouse button
        {

            if (event.key.code == sf::Mouse::Left)//on pressing mouse button left
            {
                if (bt.isMouseOver(window))
                {
                    projectHandler.openProject();
                    window.close();
                    return true;
                }
                if (bt00.isMouseOver(window))
                {
                    projectHandler.CreateDirectoryTree(name.getText());
                    window.close();
                    return true;
                }
                name.isMouseOver(window);
            }
        }

        //
        //  display
        //
        window.clear(sf::Color::Color(156, 156, 166, 255));
        
        bt.draw(window);
        bt00.draw(window);
        name.draw(window);
        window.display();
        //
        //  end display
        //
    }
}
