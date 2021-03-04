class SpacePort
{
public:
    // Создать космодром, в котором size штук доков.
    // Доки нумеруются от 0 до size-1.
    // В момент создания все доки свободны.
    SpacePort(unsigned int size);

    ~SpacePort();
    // Запросить посадку в док с номером dockNumber.
    // Если такого дока нет - вернуть false (запрет посадки).
    // Если док есть, но занят - вернуть false (запрет посадки).
    // Если док есть и свободен - вернуть true (разрешение посадки) и док становится занят.
    bool requestLanding(unsigned int dockNumber);
    // Запросить взлёт из дока с номером dockNumber.
    // Если такого дока нет - вернуть false (запрет взлёта).
    // Если док есть, но там пусто - вернуть false (запрет взлёта).
    // Если док есть и в нём кто-то стоит - вернуть true (разрешение взлёта) и док становится свободен.
    bool requestTakeoff(unsigned int dockNumber);
private:
    unsigned int size;
    bool* DockIsFree;
};

SpacePort::SpacePort(unsigned int size) : size(size)
{
    this->DockIsFree = new bool[size];
    for (unsigned int i = 0; i < size; i++)
        this->DockIsFree[i] = true;
}

bool SpacePort::requestLanding(unsigned int dockNumber)
{
    if (dockNumber < size)
        if (DockIsFree[dockNumber])
        {
            DockIsFree[dockNumber] = false;
            return true;
        }

    return false;
}

bool SpacePort::requestTakeoff(unsigned int dockNumber)
{
    if (dockNumber < size)
        if (!DockIsFree[dockNumber])
        {
            DockIsFree[dockNumber] = true;
            return true;
        }
    return false;
}

SpacePort::~SpacePort()
{
    delete[] this->DockIsFree;
}

//Код для базового тестирования реализации класса :

#include <iostream>
using namespace std;

int main()
{
    SpacePort s(5);
    cout << boolalpha << s.requestLanding(0) << endl;
    cout << boolalpha << s.requestLanding(4) << endl;
    cout << boolalpha << s.requestLanding(5) << endl;

    cout << boolalpha << s.requestTakeoff(0) << endl;
    cout << boolalpha << s.requestTakeoff(4) << endl;
    cout << boolalpha << s.requestTakeoff(5) << endl;
    return 0;
}