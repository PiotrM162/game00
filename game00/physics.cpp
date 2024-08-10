#include "physics.h"
#include <SFML/Graphics.hpp>
b2World physics::world{ b2Vec2(0,9.81) };
myDebugDraw* physics::DebugDraw{};

class myDebugDraw
	:public b2Draw
{
public:

	myDebugDraw(sf::RenderTarget& target)
		:target(target)
	{

	}

	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
	{
		sf::ConvexShape shape(vertexCount);
		for (size_t i = 0; i < vertexCount; i++)
		{
			shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
		}
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineThickness(0.02f);
		shape.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 80));
		target.draw(shape);
	}

	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
	{
		sf::ConvexShape shape(vertexCount);
		for (size_t i = 0; i < vertexCount; i++)
		{
			shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
		}
		shape.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 80));
		target.draw(shape);
	}

	virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override
	{
		sf::CircleShape circle(radius);
		circle.setPosition(center.x, center.y);
		circle.setOrigin(radius, radius);
		circle.setFillColor(sf::Color::Transparent);
		circle.setOutlineThickness(0.02f);
		circle.setOutlineColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 80));
		target.draw(circle);
	}

	virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override
	{
		sf::CircleShape circle(radius);
		circle.setPosition(center.x, center.y);
		circle.setOrigin(radius, radius);
		circle.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 180));
		target.draw(circle);

		b2Vec2 p = center + (radius * axis);
		DrawSegment(center, p, color);
	}

	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override
	{
		sf::VertexArray va(sf::Lines, 2);
		sf::Color sfcolor = sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255);

		va[0].position = sf::Vector2f(p1.x, p1.y);
		va[0].color = sfcolor;

		va[1].position = sf::Vector2f(p2.x, p2.y);
		va[1].color = sfcolor;
		target.draw(va);
	}

	virtual void DrawTransform(const b2Transform& xf) override
	{
		b2Vec2 p = xf.p;
		b2Vec2 px = p + (0.5f * xf.q.GetXAxis());
		b2Vec2 py = p + (0.5f * xf.q.GetYAxis());
		DrawSegment(p, px, b2Color(1.0f, 0.0f, 0.0f));
		DrawSegment(p, py, b2Color(1.0f, 1.0f, 0.0f));
	}

	virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override
	{
		sf::CircleShape circle(size);
		circle.setPosition(p.x, p.y);
		circle.setOrigin(size / 2.0f, size / 2.0f);
		circle.setFillColor(sf::Color(color.r * 255, color.g * 255, color.b * 255, color.a * 255));
		target.draw(circle);
	}

	private:
	sf::RenderTarget& target;
};

void physics::init()
{
}

class myGlobalContactLitener :
	public b2ContactListener
{
	virtual void BeginContact(b2Contact* contact) override
	{
		contactListener* listener = (contactListener*)contact->GetFixtureA()->GetUserData().pointer;

		if (listener)
			listener->OnBeginContact();

		listener = (contactListener*)contact->GetFixtureB()->GetUserData().pointer;

		if (listener)
			listener->OnBeginContact();
	}



	virtual void EndContact(b2Contact* contact) override
	{
		contactListener* listener = (contactListener*)contact->GetFixtureA()->GetUserData().pointer;

		if (listener)
			listener->OnEndContact();

		listener = (contactListener*)contact->GetFixtureB()->GetUserData().pointer;

		if (listener)
			listener->OnEndContact();
	}
};

void physics::update(float deltaTime)
{
	world.Step(deltaTime, 8, 4);
	world.SetContactListener(new myGlobalContactLitener);
}
 
void physics::debugDraw(GRenderer Renderer)
{
	if (!DebugDraw)
	{
		DebugDraw = new myDebugDraw(Renderer.RrenderTarget);
		DebugDraw->SetFlags(b2Draw::e_shapeBit);
		world.SetDebugDraw(DebugDraw);
	}
	world.DebugDraw();
}