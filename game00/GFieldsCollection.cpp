#include "GFieldsCollection.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include "physics.h"

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

void GFieldsCollection::GFinit(std::string path)
{
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
	int marekchuj = 0;
	for (const auto& item : js.items())
	{
		float posX = item.value()[position]["x"].get<float>();
		float posY = item.value()[position]["y"].get<float>();

		float SizeX = item.value()[size]["x"].get<float>();
		float SizeY = item.value()[size]["y"].get<float>();

		GField temField;
		temField.SetPosition({posX,posY});
		temField.SetSize({ SizeX ,SizeY });
		std::string ass = item.value()["textureName"].get<std::string>();
		temField.SetTextureName(ass);
	
		int elementsCount = item.value()["hitboxCount"].get<int>();

		b2BodyDef bodydef{};
		bodydef.type = b2_dynamicBody;
		//if(marekchuj == 1)
		//	bodydef.type = b2_staticBody;
		marekchuj++;
		bodydef.position.Set( posX,posY );
		bodydef.fixedRotation = true;
		b2Body* body = physics::world.CreateBody(&bodydef);

		b2FixtureDef fixturedef{};
		fixturedef.density = 1.0f;
		fixturedef.friction = 0.0f;

		for (size_t i = 0; i < elementsCount; i++)
		{

			std::string marek = std::to_string(i);

			std::string type = item.value()[hitbox][marek]["type"].get<std::string>();

			if (type == polygon)
			{

				float offsetX = item.value()[hitbox][std::to_string(i)][polygon][offset]["x"].get<float>();
				float offsetY = item.value()[hitbox][std::to_string(i)][polygon][offset]["y"].get<float>();

				float radius = item.value()[hitbox][std::to_string(i)][polygon]["radius"].get<float>();

				b2CircleShape circleShape{};
				circleShape.m_radius = radius;
				circleShape.m_p.Set(offsetX+radius, offsetY + radius );
				fixturedef.shape = &circleShape;
				body->CreateFixture(&fixturedef);

			}
			else if (type == rectangle)
			{
				float offsetX = item.value()[hitbox][std::to_string(i)][rectangle][offset]["x"].get<float>();
				float offsetY = item.value()[hitbox][std::to_string(i)][rectangle][offset]["y"].get<float>();

				float sizeX = item.value()[hitbox][std::to_string(i)][rectangle][size]["x"].get<float>();
				float sizeY = item.value()[hitbox][std::to_string(i)][rectangle][size]["y"].get<float>();


				b2PolygonShape polygonShape{};
				polygonShape.SetAsBox(sizeX/2, sizeY/2,b2Vec2(offsetX+sizeX / 2, offsetY+sizeY / 2), 0);
				fixturedef.shape = &polygonShape;
				body->CreateFixture(&fixturedef);

			}
			else if (type == irregular)
			{

				int in = item.value()[hitbox][std::to_string(i)][irregular]["elements"].get<int>();

				b2Vec2 vertices[4];

				for (size_t d = 0; d <= in; d++)
				{
					std::string da = std::to_string(d);

					float pointX = item.value()[hitbox][std::to_string(i)][irregular][da]["x"].get<float>();
					float pointY = item.value()[hitbox][std::to_string(i)][irregular][da]["y"].get<float>();

					vertices[d].Set(pointX, pointY);


				}
				b2PolygonShape polygon;
				polygon.Set(vertices, vertices->Length());
				
				fixturedef.shape = &polygon;
				body->CreateFixture(&fixturedef);

			}
		}

		Collection.push_back(temField);

	}
}

const std::vector<GField>& GFieldsCollection::GetFieldCollection() const
{
	return Collection;
}
