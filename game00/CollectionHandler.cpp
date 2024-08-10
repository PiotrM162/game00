#include "CollectionHandler.h"
#include <iostream>
#include <fstream> 
#include "json.hpp"
#include "Field.h"
using json = nlohmann::json;
auto constexpr irregular = "irregular";
auto constexpr hitbox = "hitbox";
auto constexpr polygon = "polygon";
auto constexpr rectangle = "rectangle";

auto constexpr position = "position";
auto constexpr size = "size";
auto constexpr textureName = "textureName";

auto constexpr offset = "offset";
auto constexpr startSize = "startSize";
auto constexpr scale = "scale";


CollectionHandler::CollectionHandler(std::string Path)
	:path(Path)
{
}

void CollectionHandler::saveCollection(FieldsColletction collection)
{
	std::ofstream outfile(path);
	std::ofstream writer;
	writer.open(path);
	json js;
	outfile.close();
	int index = 0;

	for (auto i : collection.GetFieldCollection())
	{
		std::string indexS = std::to_string(index);
		js[indexS][position]["x"] = i.GetPosition().x;
		js[indexS][position]["y"] = i.GetPosition().y;

		js[indexS][size]["x"] = i.GetSize().x;
		js[indexS][size]["y"] = i.GetSize().y;
		
		js[indexS][textureName] = i.GetTextureNameS();

		int hitboxIndex = 0;

		for (auto a : i.seetHitboxes().polygons )
		{
			std::string hitboxIndexS = std::to_string(hitboxIndex);
			js[indexS][hitbox][hitboxIndexS]["type"] = polygon;
			js[indexS][hitbox][hitboxIndexS][polygon][offset]["x"] = a.offset.x;
			js[indexS][hitbox][hitboxIndexS][polygon][offset]["y"] = a.offset.y;
					   						 
			js[indexS][hitbox][hitboxIndexS][polygon][startSize]["x"] = a.startSize.x;
			js[indexS][hitbox][hitboxIndexS][polygon][startSize]["y"] = a.startSize.y;
					  						 
			js[indexS][hitbox][hitboxIndexS][polygon][scale]["x"] = a.scale.x;
			js[indexS][hitbox][hitboxIndexS][polygon][scale]["y"] = a.scale.y;
					   						 
			js[indexS][hitbox][hitboxIndexS][polygon]["radius"] = a.polygons.getRadius();

			hitboxIndex++;
		}
		for (auto a : i.seetHitboxes().rectangles)
		{
			std::string hitboxIndexS = std::to_string(hitboxIndex);
			js[indexS][hitbox][hitboxIndexS]["type"] = rectangle;
					   
			js[indexS][hitbox][hitboxIndexS][rectangle][offset]["x"] = a.offset.x;
			js[indexS][hitbox][hitboxIndexS][rectangle][offset]["y"] = a.offset.y;
											 
			js[indexS][hitbox][hitboxIndexS][rectangle][startSize]["x"] = a.startSize.x;
			js[indexS][hitbox][hitboxIndexS][rectangle][startSize]["y"] = a.startSize.y;
											 
			js[indexS][hitbox][hitboxIndexS][rectangle][scale]["x"] = a.scale.x;
			js[indexS][hitbox][hitboxIndexS][rectangle][scale]["y"] = a.scale.y;
						  					 
			js[indexS][hitbox][hitboxIndexS][rectangle][size]["x"] = a.rectangles.getSize().x;
			js[indexS][hitbox][hitboxIndexS][rectangle][size]["y"] = a.rectangles.getSize().y;
			hitboxIndex++;
		}
		
		for (auto a : i.seetHitboxes().irregular)
		{
			std::string hitboxIndexS = std::to_string(hitboxIndex);
			js[indexS][hitbox][hitboxIndexS]["type"] = irregular;
					   
			js[indexS][hitbox][hitboxIndexS][irregular][offset]["x"] = a.offset.x;
			js[indexS][hitbox][hitboxIndexS][irregular][offset]["y"] = a.offset.y;
						  
			js[indexS][hitbox][hitboxIndexS][irregular][startSize]["x"] = a.startSize.x;
			js[indexS][hitbox][hitboxIndexS][irregular][startSize]["y"] = a.startSize.y;
						 
			js[indexS][hitbox][hitboxIndexS][irregular][scale]["x"] = a.scale.x;
			js[indexS][hitbox][hitboxIndexS][irregular][scale]["y"] = a.scale.y;
			int bb;
			for (size_t b = 0; b < a.irregular.getPointCount(); b++)
			{
				std::string bString = std::to_string(b);
				//js[indexS][hitbox][hitboxIndexS][irregular][bString] = b;
				js[indexS][hitbox][hitboxIndexS][irregular][bString]["x"] = a.irregular.getPoint(b).x;
				js[indexS][hitbox][hitboxIndexS][irregular][bString]["y"] = a.irregular.getPoint(b).y;
				bb = b;
			}
			js[indexS][hitbox][hitboxIndexS][irregular]["elements"] = bb;
			hitboxIndex++;
		}
		js[indexS]["hitboxCount"] = hitboxIndex;
		index++;
	}
	writer << js;
	writer.close();
}

void CollectionHandler::loadCollection(FieldsColletction& collection)
{
	FieldsColletction crossount;
	collection = crossount;
	std::ifstream reader(path);
	json js;
	try
	{
		js = json::parse(reader);
	}
	catch (json::parse_error& ex)
	{
		std::cerr << "parse error at byte " << ex.byte << std::endl;
	}
	for (const auto& item : js.items())
	{
		float posX = item.value()[position]["x"].get<float>();
		float posY = item.value()[position]["y"].get<float>();

		float SizeX = item.value()[size]["x"].get<float>();
		float SizeY = item.value()[size]["y"].get<float>();

		Field temField({ SizeX,SizeY }, { posX,posY });
		std::string ass = item.value()["textureName"].get<std::string>();
		temField.SetTextureName(ass);


		int elementsCount = item.value()["hitboxCount"].get<int>();

		for (size_t i = 0; i < elementsCount; i++)
		{
			std::string marek = std::to_string(i);

			std::string type = item.value()[hitbox][marek]["type"].get<std::string>();

			if (type == polygon)
			{

				float offsetX = item.value()[hitbox][std::to_string(i)][polygon][offset]["x"].get<float>();
				float offsetY = item.value()[hitbox][std::to_string(i)][polygon][offset]["y"].get<float>();

				float startSizeX = item.value()[hitbox][std::to_string(i)][polygon][startSize]["x"].get<float>();
				float startSizeY = item.value()[hitbox][std::to_string(i)][polygon][startSize]["y"].get<float>();

				float scaleX = item.value()[hitbox][std::to_string(i)][polygon][scale]["x"].get<float>();
				float scaleY = item.value()[hitbox][std::to_string(i)][polygon][scale]["y"].get<float>();

				float radius = item.value()[hitbox][std::to_string(i)][polygon]["radius"].get<float>();

				sf::CircleShape circle(radius);
				circle.setPosition({ 0,0 });
				//circle.setOrigin({ 0.5f,0.5f });
				circle.setFillColor(sf::Color::Color(153, 241, 94, 126));

				temField.AddPolygon(circle, { offsetX,offsetY }, { startSizeX,startSizeY });
			}
			else if(type==rectangle)
			{
				float offsetX = item.value()[hitbox][std::to_string(i)][rectangle][offset]["x"].get<float>();
				float offsetY = item.value()[hitbox][std::to_string(i)][rectangle][offset]["y"].get<float>();

				float startSizeX = item.value()[hitbox][std::to_string(i)][rectangle][startSize]["x"].get<float>();
				float startSizeY = item.value()[hitbox][std::to_string(i)][rectangle][startSize]["y"].get<float>();

				float scaleX = item.value()[hitbox][std::to_string(i)][rectangle][scale]["x"].get<float>();
				float scaleY = item.value()[hitbox][std::to_string(i)][rectangle][scale]["y"].get<float>();

				float sizeX = item.value()[hitbox][std::to_string(i)][rectangle][size]["x"].get<float>();
				float sizeY = item.value()[hitbox][std::to_string(i)][rectangle][size]["y"].get<float>();

				sf::RectangleShape rectangle({ sizeX,sizeY });
				rectangle.setPosition({ 0,0 });
				rectangle.setFillColor(sf::Color::Color(153, 241, 94, 126));
				//rectangle.setOrigin(0.25f, 0.25f);
				temField.AddRectangle(rectangle, { offsetX,offsetY }, { startSizeX,startSizeY });
			}
			else if(type == irregular)
			{
				float offsetX = item.value()[hitbox][std::to_string(i)][irregular][offset]["x"].get<float>();
				float offsetY = item.value()[hitbox][std::to_string(i)][irregular][offset]["y"].get<float>();

				float startSizeX = item.value()[hitbox][std::to_string(i)][irregular][startSize]["x"].get<float>();
				float startSizeY = item.value()[hitbox][std::to_string(i)][irregular][startSize]["y"].get<float>();

				float scaleX = item.value()[hitbox][std::to_string(i)][irregular][scale]["x"].get<float>();
				float scaleY = item.value()[hitbox][std::to_string(i)][irregular][scale]["y"].get<float>();

				int in = item.value()[hitbox][std::to_string(i)][irregular]["elements"].get<int>();
				 

				sf::ConvexShape convexS;
				convexS.setPointCount(in+1);

				for (size_t d = 0; d <= in; d++)
				{
					std::string da = std::to_string(d);

					float pointX = item.value()[hitbox][std::to_string(i)][irregular][da]["x"].get<float>();
					float pointY = item.value()[hitbox][std::to_string(i)][irregular][da]["y"].get<float>();

					convexS.setPoint(d, { pointX,pointY });


				}
					
				convexS.setFillColor(sf::Color::Color(153, 241, 94, 126));

				temField.Addcovex(convexS, { offsetX,offsetY }, { startSizeX,startSizeY });

			}
		}
		collection.AddToCollection(temField);
		collection.update();
	}
}
