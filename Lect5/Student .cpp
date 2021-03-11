#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
    Student(): balls(0), Name(){

    }
    // Задать имя студента
    void setName(string name){
        Name = name;
    }

    // Указать количество баллов за контрольную
    void setScore(unsigned int score){
        balls = score;
    }

    // Получить имя студента
    string getName() const{
        return Name;
    }

    // Получить количество баллов студента
    unsigned int getScore() const{
        return balls;
    }


private:
    unsigned int balls;
    string Name;
};


std::istream& operator >> (std::istream& io, Student& student){
    string name;
    io >> name;
    student.setName(name);
    student.setScore(0);
    return io;
}

std::ostream& operator<<(std::ostream& os, const Student& student){
    os << "'" << student.getName() << "'" << ": " << student.getScore();
    return os;
}


int main(){
    Student s;
    cin >> s;
    s.setScore(10);
    cout << s << endl;
    return 0;
}