#include <map>
#include <iostream>
#include <cmath>
#include <vector>

struct cartesian_point {
    double x;
    double y;
    double operator*(cartesian_point const& cp) const {
        return cp.x * x + cp.y * y;
    }
    cartesian_point operator-(cartesian_point const& cp) const {
        return cartesian_point{ x - cp.x, y - cp.y };
    }
    cartesian_point operator/(double v) const {
        return cartesian_point{ x / v, y / v };
    }
};
std::ostream& operator<<(std::ostream& out, cartesian_point const& p) {
    out << "(" << p.x << "," << p.y << ")";
    return out;
}

template <typename point_type>
class tracker_system {
public:
    //Структура с информацией о отслеживаемом объекте
    struct track_point {
        track_point() {}
        track_point(point_type const& point, double eps, size_t ID)
        {
            id = ID;
            position = point;
            epsilon = eps;
            track_timestamp = -1;
            velocity = acceleration = 0;
            tracked = locked = false;
        }
        void SetNewPos(point_type NewPos, double timestep)
        {
            std::cout << "   While setting new position locked was " << locked << std::endl;
            direction = NewPos - position;
            double directionMagnitude = sqrt(direction * direction);
            if (locked)
            {
                double dt = timestep - track_timestamp;
                double NewVelocity = directionMagnitude / dt;
                if (tracked)
                    acceleration = (NewVelocity - velocity) / dt;
                else
                    tracked = true;
                velocity = NewVelocity;
            }
            else
                locked = true;
            direction = direction / directionMagnitude;
            position = NewPos;
            track_timestamp = timestep;
            std::cout << "   After setting new position locked was " << locked << std::endl;
        }
        void CheckVisible(double timestep)
        {
            if (std::abs(track_timestamp - timestep) > 0.01)
            {
                locked = tracked = false;
                std::cout << "Unable to find a target with ID " << id << std::endl;
            }
        }

        size_t id{}; //Уникальный id отслеживаемого объекта
        double epsilon{}; //Погрешность вычисления положения объекта

        point_type position{}; //Положение объекта
        point_type direction{}; //Единичный вектор указывающий направление движения объекта
        double velocity{}; //скоросто объекта
        double acceleration{}; //ускорение объекта 

        double track_timestamp{}; //временная метка (в секундах), когда объект последний раз был обнаружен 

        bool tracked = false; //объект отслеживается больше чем в двух временных точках подряд. Можно определить ускорение объекта
        bool locked = false; //объект обнаружен бошье чем в одной временной точке подряд. Можно определить скорость объекта. 
    };

    /*
    Добавить объект с координатами point в систему слежения.
    Максимальное смещение объекта в результате его эволюции не превышает eps.
    Метод возвращает уникальный номер объекта в наборе отслеживаемых объектов.
    Для двух различных вызовов этого метода, возвращаемые значения всегда должны отличаться.
    */
    size_t lock(point_type const& point, double eps)
    {
        LockedPool[maxID] = track_point(point, eps, maxID);
        maxID++;
        std::cout << "Locked a point in coordinates (" << point.x << ' ' << point.y << ") with index " << maxID - 1 << std::endl;
        return maxID - 1;

    }
    /*Удалить объект с заданным lock_id из системы слежения.*/
    void unlock(size_t lock_id)
    {
        LockedPool.erase(lock_id);
    }

    /*
    Получить информацию о всех отслеживаемых объектах в момент времени timestep.
    Список обнаруженных объектов передается в векторе points.
    Если отслеживаемых объект в этом списке не обнаружен, поле tracked, для записи об объекте, должно равнятся false.
    Если для объекта невозможно определить скорость или ускорения, то предполагать что эти величины равными нулю.
    */
    std::vector<track_point> track(std::vector<point_type> const& points, double timestep)
    {

        std::vector<track_point> TargetPool;
        for (auto lockedTarget : LockedPool)
        {
            for (auto target : points)
            {
                if ((target - lockedTarget.second.position) * (target - lockedTarget.second.position) <= lockedTarget.second.epsilon * lockedTarget.second.epsilon)
                {
                    std::cout << "Found a target with ID " << lockedTarget.first << std::endl;
                    lockedTarget.second.SetNewPos(target, timestep);
                    TargetPool.push_back(lockedTarget.second);
                    break;
                }
            }
            lockedTarget.second.CheckVisible(timestep);
        }
        trackedCount = TargetPool.size();
        return TargetPool;
    }

    /*
    Количество отслеживаемых объектов.
    */
    size_t tracked_count() const
    {
        return LockedPool.size();
    }
private:
    size_t maxID = 0;
    std::map<size_t, track_point> LockedPool;
    size_t trackedCount = 0;
};

int main()
{
    std::vector<cartesian_point> p{ 2 };
    auto& a = p[0];
    auto& b = p[1];

    a = { 1, 1 };
    b = { 0, 1 };
    tracker_system<cartesian_point> ts;
    ts.lock({ 0.8, 0.8 }, 0.5);
    ts.lock({ 0.0, 0.9 }, 0.2);
    double time = 0;
    for (auto i = 0; i < 101; ++i, time += 0.01) {
        auto d = ts.track(p, time);
        //if (i % 25 == 0) {
            for (auto const& td : d) {
                std::cout << i << ": " << td.id << " " << td.position << " " << td.direction << " "
                    << td.velocity << " " << std::round(td.acceleration) << " "
                    << std::boolalpha << td.tracked << " " << td.locked
                    << std::endl;
            }
        //}

        a.x = a.x + 2 * 0.01;
        a.y = a.y - 5 * 0.01;

        b.x = b.x + 5 * 0.01;
    }
    return 0;
}