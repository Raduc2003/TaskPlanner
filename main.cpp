#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Planner
{

private:
    Planner() = default;

public:
    Planner(const Planner &obj) = delete;
    static Planner &getPlanner()
    {
        static Planner instance;
        return instance;
    }
};

template <typename T>
class Task
{
private:
    char title[30];
    bool done;

public:
    Task()
    {
        this->title = "Untitled Task";
        bool done = false;
    }
    Task(char title)
    {
        this->title = title;
    }
};
class Task<string>
{
private:
    string description;

public:
    Task(string description)
    {
        this->description = description;
    }
};

class DayPlan
{
protected:
    vector<Task<char>> tasks;

public:
    DayPlan()
    {
    }
};
class MonthPlan : public DayPlan
{
protected:
    DayPlan month[31];

public:
    MonthPlan() : DayPlan(){

                  };
};
class YearPlan : public MonthPlan
{
protected:
    MonthPlan month[12];

public:
    YearPlan() : MonthPlan(){};
};

int main()
{

    Planner &Planner1 = Planner::getPlanner();
}