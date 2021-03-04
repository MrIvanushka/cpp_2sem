/*
Напишите класс Train, описывающий движение паровоза по рельсам.
Паровоз описывается тремя параметрами - масса, текущая скорость,
текущая координата (одномерная, отсчитывается вдоль рельсов).
*/

#include <iostream>

class Train
{
public:
	// Создать паровоз массой m, 
	// стоящий в начале координат
	Train(double m) : Mass(m), Speed(0), Coord(0) { }

	// Ехать с текущей скоростью в течение времени dt
	void move(double dt)
	{
		this->Coord += this->Speed * dt;
	}

	// Изменить полный импульс паровоза (p = mv) на dp
	// Изменение может менять знак скорости
	void accelerate(double dp)
	{
		this->Speed += dp / this->Mass;
	}

	// Получить текущую координату паровоза
	double getX()
	{
		return this->Coord;
	}
private:
	double Mass;
	double Speed;
	double Coord;
};

//Код для базового тестирования реализации класса:
int main()
{
	Train t(10);
	t.accelerate(1); // Скорость стала 0.1
	t.move(1);
	std::cout << "Current X: " << t.getX() << std::endl;
	t.move(1);
	std::cout << "Current X: " << t.getX() << std::endl;
	t.accelerate(-2); // Скорость стала -0.1
	t.move(3);
	std::cout << "Current X: " << t.getX() << std::endl;
	return 0;
}