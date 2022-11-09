#include <SFML/Graphics.hpp>  //Библиотека для отрисовки
#include <iostream>
using namespace std;
using namespace sf;  //Подключение пространство имён sf (чтобы не писать sf::)

int WIDTH = 800, HEIGHT = 600, kol1 = 0, kol2 = 0, kol3 = 0, kol4 = 0;

sf::Vertex rect[] =
{
		    sf::Vertex(Vector2f(0,   0), sf::Color::Red),
		    sf::Vertex(Vector2f(WIDTH,   0), sf::Color::Red),
		    sf::Vertex(Vector2f(WIDTH, HEIGHT), sf::Color::Red),
		    sf::Vertex(Vector2f(0,   HEIGHT), sf::Color::Red)
};
		
Color GetRainbow(int x){
	x %= 1530; //ограничиваем
	
	int layer = x/255; // узнаём какой сектор
	
	x %= 255; // делаем до цветового диапазона
	
	switch(layer){
		case 0:{
			return Color(255, x, 0);
		}
		case 1:{
			return Color(255 - x, 255, 0);
		}
		case 2:{
			return Color(0, 255, x);
		}
		case 3:{
			return Color(0, 255 - x, 255);
		}
		case 4:{
			return Color(x, 0, 255);
		}
		case 5:{
			return Color(255, 0, 255-x);
		}
	}
}

int main()
{	
	ContextSettings settings;  
	settings.antialiasingLevel = 8; 
	
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "SFML Works!", Style::Default, settings);  //Параметр создания окна 1) разрешение 2) загаловок 3) Отвечает за отабражение загаловка 4) параметры настроек
	
	kol1 = 0;
	kol2 = 0;
	kol3 = 0;
	kol4 = 0;
	
	while (window.isOpen())  //Главный цикл приложения. Выполняется, пока открыто окно
	{
		Event event;  //Обрабатываем очередь событий в цикле (event - событие)
		while (window.pollEvent(event))  //Если произошло событие
		{
			if (event.type == Event::Closed)  //Если событие - закртыие окна
				window.close();  //Закрываем окно
				
			if (event.type == Event::Resized)  //Строчки на нормальное изменения окон
			{
	            WIDTH = event.size.width;
	            HEIGHT = event.size.height;          
	            window.setView(
	                View(
	                   Vector2f(WIDTH / 2.0, HEIGHT / 2.0), 
	                   Vector2f(WIDTH, HEIGHT)
	                )
	            );
	            rect[0].position = Vector2f(0, 0);
	            rect[1].position = Vector2f(WIDTH,   0);
	            rect[2].position = Vector2f(WIDTH, HEIGHT);
	            rect[3].position = Vector2f(0, HEIGHT);
	        }
	        if(event.type == Event::MouseWheelMoved){					
				int x = event.mouseWheel.x, y = event.mouseWheel.y;
				
				if((0 <= x and x <= WIDTH/2) and (0 <= y and y <= HEIGHT/2))
					kol1 += event.mouseWheel.delta*5;
				if((WIDTH/2 < x and x <= WIDTH) and (0 <= y and y <= HEIGHT/2))
					kol2 += event.mouseWheel.delta*5;
				if((0 <= x and x <= WIDTH/2) and (HEIGHT/2 < y and y <= HEIGHT))
					kol4 += event.mouseWheel.delta*5;
				if((WIDTH/2 < x and x <= WIDTH) and (HEIGHT/2 < y and y <= HEIGHT))
					kol3 += event.mouseWheel.delta*5;
				
				if(kol1 < 0)
					kol1 = 1530;
				if(kol2 < 0)
					kol2 = 1530;
				if(kol3 < 0)
					kol3 = 1530;
				if(kol4 < 0)
					kol4 = 1530;
				
				rect[0].color = GetRainbow(kol1);
				rect[1].color = GetRainbow(kol2);
				rect[2].color = GetRainbow(kol3);
				rect[3].color = GetRainbow(kol4);
			}
		}
		window.clear(Color::Black);  //Очисктка окна и заливка в цвет(RGBA) 
		
		window.draw(rect, 4, sf::Quads);
		
		window.display();  //Отрисовка окна
	}
	return 0;
}