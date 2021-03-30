#include <iostream>
#include <string>
#include <vector>
using namespace std;


class VectorN
{
public:
    // Конструктор вектора размерности n
    VectorN(unsigned int n): len(n), vec(n) {
    }

    // Деструктор
    ~VectorN();

    // Получение размерности вектора
    unsigned getSize() const{
        return len;
    }

    // Получение значения i-ой координаты вектора,
    // i находится в диапазоне от 0 до n-1
    int getValue(unsigned int i) const{
           return vec[i];
    }

    // Задание значения i-ой координаты вектора равным value,
    // i находится в диапазоне от 0 до n-1
    void setValue(unsigned int i, int value){
            vec[i] = value;
    }

    /*
     * Далее реализуйте перегруженные операторы
     */

    // Оператор == проверяет два вектора на равенство,
    // равны они, если строго равны всех их координаты
    bool operator== (const VectorN& vN){
        for (int i = 0; i < len; ++i) {
            if(vN.vec[i] != vec[i])
                return false;
        }

        return true;
    }

    // Оператор != проверяет два вектора на неравенство,
    // они не равны, если хотя бы одна координата отличается
    bool operator != (const VectorN& vN){
        for (int i = 0; i < len; ++i) {
            if(vN.vec[i] != vec[i])
                return true;
        }

        return false;
      //  return ~(*this == vN);
    }

    // Оператор + складывает два вектора покоординатно,
    // возвращает результат как новый экземпляр вектора
    VectorN operator+ (const VectorN& vN){
        VectorN New(len);
        for (int i = 0; i < len; ++i) {
         New.vec[i] = vN.vec[i] + vec[i];
        }
        return New;
    }
    // Оператор * умножает вектор на скаляр типа int покоординатно,
    // возвращает результат как новый экземпляр вектора.
    // Умножение должно работать при любом порядке операндов.
    VectorN operator* (unsigned int a){
       VectorN New2(len);
        for (int i = 0; i < len; ++i) {
           New2.vec[i] = vec[i] * a;
        }
        return New2;
    }

private:
    vector<int> vec;
    int len;
};


int main(){
    VectorN a(4);
    a.setValue(0, 0);
    a.setValue(1, 1);
    a.setValue(2, 2);
    a.setValue(3, 3);

    VectorN b(4);
    b.setValue(0, 0);
    b.setValue(1, -1);
    b.setValue(2, -2);
    b.setValue(3, -3);

    cout << (a == b) << endl;
    cout << (a != b) << endl;

    VectorN c = a + b;
    VectorN d = c * 5;

    for(unsigned int i = 0; i < a.getSize(); ++i)
        cout << d.getValue(i) << endl;
    return 0;
}