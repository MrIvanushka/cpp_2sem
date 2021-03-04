#include <iostream>
using namespace std;

class Car
{
protected:
    bool allowesBoarding;
    bool allowesLoading;
    unsigned int numberOfSeats;
    unsigned int numberOfContainers;

public:
    Car(bool allowesBoarding, bool allowesLoading, unsigned int numberOfSeats, unsigned int numberOfContainers) {
        this->allowesBoarding = allowesBoarding;
        this->allowesLoading = allowesLoading;
        this->numberOfSeats = numberOfSeats;
        this->numberOfContainers = numberOfContainers;
    }
    ~Car() {}

    bool isBoardingAllowed() const {
        return allowesBoarding;
    }

    bool isLoadingAllowed() const {
        return allowesLoading;
    }

    unsigned int getNumberOfSeats() const {
        return numberOfSeats;
    }

    unsigned int getNumberOfContainers() const {
        return numberOfContainers;
    }
};


class ConvoyManager
{
public:
    ConvoyManager(): places(0), containers(0){
    }
    // Зарегистрировать новую машину в колонне
    void registerCar(const Car& c){
        if (c.isBoardingAllowed() == true)
            places += c.getNumberOfSeats();
        if ( c.isLoadingAllowed()== true)
            containers += c.getNumberOfContainers();
    }

    // Сообщить, сколько всего пассажиров может принять колонна
    unsigned int getTotalSeats() const{
        return places;
    }

    // Сообщить, сколько всего грузовых контейнеров может взять колонна
    unsigned int getTotalContainers() const{
        return containers;
    }

private:
    unsigned int places, containers;
};



int main(){
    ConvoyManager cm;

    Car c1(true, false, 12, 3);
    cm.registerCar(c1);
    Car c2(false, true, 12, 3);
    cm.registerCar(c2);
    Car c3(true, true, 12, 3);
    cm.registerCar(c3);
    Car c4(false, false, 12, 3);
    cm.registerCar(c4);

    cout << "Total available seats: " << cm.getTotalSeats() << endl;
    cout << "Total available containers: " << cm.getTotalContainers() << endl;
    return 0;
}