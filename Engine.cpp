#include "Engine.h"
#include <cstdlib>
#include <ctime>

Engine::Engine()
{
	m_Window.create({ 1600, 900 }, "Particles", Style::Default);
}

void Engine::run()
{
	//Create clock to track time per frame
	Clock tFrame;
	Time dt;
	//Local particle for unit testing
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	//begin game loop
	while (m_Window.isOpen())
	{
		dt = tFrame.restart();
		input();
		update(dt.asSeconds());
		draw();
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		//If window is X'd close
		if (event.type == Event::Closed)
			m_Window.close();

		//Close on escape
		if (Keyboard::isKeyPressed(Keyboard::Escape))
			m_Window.close();

		//Generate particles when left click
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//Seed random for vertices
			srand(time(nullptr));
			for (int i = 0; i < 5; i++)
			{
				//Create 5 particles with random amount of vertices at mouse
				m_particles.emplace_back(m_Window, ((rand() % 26) + 25), Vector2i(event.mouseButton.x, (int)event.mouseButton.y));
			}
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	//Update each particle and delete if time to live is 0
	for (auto it = m_particles.begin(); it != m_particles.end(); )
	{
		if (it->getTTL() > 0.0)
		{
			it->update(dtAsSeconds);
			it++;
		}
		else
		{
			it = m_particles.erase(it);
		}
	}
}

void Engine::draw()
{
	//Clear window
	m_Window.clear();
	//Draw each particle
	for (Particle& p : m_particles)
		m_Window.draw(p);
	//Display drawn particles
	m_Window.display();
}