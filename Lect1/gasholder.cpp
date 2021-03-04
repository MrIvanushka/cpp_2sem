/*
Напишите класс GasHolder, описывающий состояние
термостатированного сосуда с газом. Считать, что
для газа верно уравнение состояния PV = (m/M)RT.
Значение постоянной R принять 8.31 Дж/(моль*К).
*/
#include <iostream>
using namespace std;

const float R = 8.31;

class GasHolder
{
public:
	// Создать газгольдер заданного объёма.
	// Температура созданного термостата равна 273 К.
	GasHolder(float v);


	// Впрыск порции газа массой m и молярной массой M.
	// Считать, что газ принимает текущую температуру газгольдера за пренебрежимо малое время.
	void inject(float m, float M);

	// Подогреть газгольдер на dT градусов.
	// Считать, что нагрев возможен до любых значений температуры.
	void heat(float dT);

	// Охладить газгольдер на dT градусов.
	// При попытке охладить ниже 0 К температура становится ровно 0 К.
	void cool(float dT);

	// Получить текущее давление в газгольдере.
	// Считать, что для газа верно уравнение состояния PV = (m/M)RT. 
	// Значение постоянной R принять 8.31 Дж/(моль*К).
	float getPressure();
private:
	float Volume;
	float Temp;
	float Value;
};

GasHolder::GasHolder(float v) : Volume(v), Temp(273), Value(0)
{
}

void GasHolder::inject(float m, float M)
{
	this->Value += (m / M);
}
void GasHolder::heat(float dT)
{
	this->Temp += dT;
}
void GasHolder::cool(float dT)
{
	this->Temp -= dT;
	if (this->Temp < 0)
		this->Temp = 0;
}
float GasHolder::getPressure()
{
	return Value * R * Temp / Volume;
}

//Код для базового тестирования реализации класса :

int main()
{
	GasHolder h(1.0);
	h.inject(29, 29);
	cout << "Pressure after operation: " << h.getPressure() << " Pa" << endl;
	h.inject(29, 29);
	cout << "Pressure after operation: " << h.getPressure() << " Pa" << endl;
	h.heat(273);
	cout << "Pressure after operation: " << h.getPressure() << " Pa" << endl;
	h.cool(373);
	cout << "Pressure after operation: " << h.getPressure() << " Pa" << endl;
	h.cool(373);
	cout << "Pressure after operation: " << h.getPressure() << " Pa" << endl;
	return 0;
}