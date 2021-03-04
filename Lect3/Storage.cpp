#include <iostream>
using namespace std;


class Storage
{
public:
    // Конструктор хранилища размерности n
    Storage(unsigned int n): length(n),   F( new int[length]){
    }
    // Добавьте нужный деструктор
    virtual ~Storage() {
        delete[] F;
    }

    // Получение размерности хранилища
    unsigned getSize(){
        return length;
    }

    // Получение значения i-го элемента из хранилища,
    // i находится в диапазоне от 0 до n-1,
    // случаи некорректных i можно не обрабатывать.
    int getValue(unsigned int i){
        for(unsigned int j = 0; j < length; i++){
            if ( j == i)
                return F[j];
        }
    }

    // Задание значения i-го элемента из хранилища равным value,
    // i находится в диапазоне от 0 до n-1,
    // случаи некорректных i можно не обрабатывать.
    void setValue(unsigned int i, int value){
        F[i] = value;
    }

private:
    unsigned int length;
    int* F;
};



// Класс TestStorage, наследуется от вашей реализации Storage
class TestStorage : public Storage {
protected:
    // Унаследованная реализация зачем-то хочет выделить ещё памяти. Имеет право.
    int* more_data;

public:
    // В конструкторе память выделяется,
    TestStorage(unsigned int n) : Storage(n) {
        more_data = new int[n];
    }
    // ... а в деструкторе освобождается - всё честно.
    ~TestStorage() {
        delete[] more_data;
    }
};

int main() {
    Storage *ts = new TestStorage(42);
    delete ts;
    return 0;
}
