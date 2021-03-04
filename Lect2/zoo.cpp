#include <iostream>
#include <string.h>
using namespace std;
/*
Пишем класс, который умеет взаимодействовать с другими классами.
Причём другие классы могут быть очень разные - иерархия наследования
у них может оказаться очень развесистой.Но наш класс общается с
ними через единый интерфейс, благодаря чему отдельной обработки
всех случаев писать не требуется.

У вас есть зоопарк разных классов.У них есть общий интерфейс.Вот такой :
*/
class Animal {
public:
    virtual string getType() = 0;
    virtual bool isDangerous() = 0;
};
/*
Сколько и каких конкретных зверей будет потом
создано - вы не знаете.Но для вас интерфейс к ним всем будет таким.

Нужно написать класс смотрителя зоопарка. Классу передают на вход зверей,
он их всех последовательно осматривает и пересчитывает, сколько из них было опасных.
*/

class ZooKeeper {
public:
    // Создаём смотрителя зоопарка
    ZooKeeper();

    // Смотрителя попросили обработать очередного зверя.
    // Если зверь был опасный, смотритель фиксирует у себя этот факт.
    void handleAnimal(Animal* a);

    // Возвращает, сколько опасных зверей было обработано на данный момент.
    int getDangerousCount();
private:
    int DangerousCount;

};

ZooKeeper::ZooKeeper() : DangerousCount(0)
{ }

void ZooKeeper::handleAnimal(Animal* a)
{
    if (a->isDangerous())
        DangerousCount++;
}
int ZooKeeper::getDangerousCount()
{
    return DangerousCount;
}
