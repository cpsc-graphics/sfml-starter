#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "hilbert.cpp"

int keyPressed(int n){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))//right arrow key
	{
		n++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && n != 1)//left arrow key and n cant be 1
	{
		n--;
	}
	return n;
}

int main()
{
	sf::RenderWindow window( sf::VideoMode( { 1024, 1024 } ), "Hilbert Curve" );
	//sf::View cartesianview(sf::FloatRect({0.f,0.f},{1024,-1024}));
	//cartesianview.setCenter(sf::Vector2f(512.f,512.f));
	//window.setView(cartesianview);
	//sf::State::Fullscreen;
	int n = 1;

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() ){
				window.close();
			}
			n = keyPressed(n);
		}

		window.clear(sf::Color::White);
		hilbert hilbert1;
		sf::VertexArray hilbert2 = hilbert1.hilbertrecursion(n,window);
		window.draw(hilbert2);
		window.display();
		//printf("n = %d\n", n);//debug statement
	}
};
