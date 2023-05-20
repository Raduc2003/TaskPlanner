#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Planner{
    
    private:
        Planner()=default;

    public:
        Planner(const Planner &obj) = delete;
        static Planner &getPlanner() { 
             
            static Planner instance;
            return  instance;

        }

};
class DayPlan{
    protected:
        int Task;
    public:
        DayPlan(){

            
        }

};
class MonthPlan: public DayPlan{
    protected:
        DayPlan month[31];
    public:
        MonthPlan():DayPlan(){


        };
};
class YearPlan: public MonthPlan{
    protected:
        MonthPlan month[12];
    public:
        YearPlan():MonthPlan(){};
};

int main(){

    Planner  &Planner1 = Planner::getPlanner();



}