#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <list>
using namespace std;

class IO
{
public:
    virtual ostream &output(ostream &out) const = 0;
    virtual istream &input(istream &in) = 0;
};

class Task : public IO
{
private:
    string title;
    bool done;

public:
    Task()
    {

        this->title = "Untitled Task";
        bool done = 0;
    }
    Task(string title, bool done)
    {

        this->title = title;
        this->done = done;
    }
    ~Task() {}
    Task(const Task &other)
    {
        this->title = other.title;
        this->done = other.done;
    }
    Task &operator=(const Task &other)
    {
        if (this != &other)
        {
            this->title = other.title;
            this->done = other.done;
        }
        return *this;
    }
    istream &input(istream &in)
    {
        cout << "Task Title: " << endl;
        in >> title;
        return in;
    }
    ostream &output(ostream &out) const
    {
        out << this->title << " ";
        done == 1 ? out << "status: done" << endl : out << "status: not done" << endl;
        return out;
    }
    friend istream &operator>>(istream &in, Task &obj)
    {
        return obj.input(in);
    }
    friend ostream &operator<<(ostream &out, const Task &obj)
    {
        return obj.output(out);
    }
    void checkTask()
    {
        this->done = 1;
    }
    void uncheckTask()
    {
        this->done = 0;
    }
};
class LongTask : public Task
{
private:
    string description;

public:
    LongTask() : Task()
    {
        description = "No Description";
    }
    LongTask(string title, bool done, string description) : Task(title, done)
    {
        this->description = description;
    }
    LongTask(const LongTask &other) : Task(other)
    {
        this->description = other.description;
    }
    LongTask &operator=(const LongTask &other)
    {
        if (this != &other)
        {
            Task::operator=(other);
            this->description = other.description;
        }
        return *this;
    }
    istream &input(istream &in)
    {
        Task::input(in);
        cout << "Description: " << endl;
        in >> this->description;
        return in;
    }
    ostream &output(ostream &out) const
    {
        Task::output(out);
        cout << "Description: " << endl;
        out << this->description;
        return out;
    }
    friend istream &operator>>(istream &in, LongTask &obj)
    {
        return obj.input(in);
    }
    friend ostream &operator<<(ostream &out, LongTask &obj)
    {
        return obj.output(out);
    }
};
class ProgressTask : public LongTask{
    private:
        int progress;
    public:
        ProgressTask():LongTask(){
            progress = 0;
        }
        ProgressTask(string title, bool done, string description, int progress):LongTask(title,done,description){
            this->progress = progress;
        }
        ProgressTask(const ProgressTask& other):LongTask(other){
            this->progress = other.progress;
        }
        ProgressTask& operator=(const ProgressTask& other){
            if(this != &other){
                LongTask::operator=(other);
                this->progress = other.progress;
            }
        }
        iostream &input(iostream &in){
            LongTask::input(in);
        }
        friend iostream &operator>>(iostream &in,ProgressTask & obj){
            return obj.input(in);
        }
        ostream &output(ostream & out){
            LongTask::output(out);
            out<<"progress: "<<progress<<"/10"<<endl;
            return out;
        }
        friend ostream& operator<<(ostream &out,ProgressTask & obj){
            return obj.output(out);
        }
};
class DayPlan : public IO
{
protected:
    vector<Task> tasks;
    int day; // day of the month optional if not used for specific date
public:
    vector<Task> getTasks() { return tasks; }
    void setDay(int day) { this->day=day; }
    int getDay() { return day; }
    DayPlan()
    {
        day = -1;
    }
    ~DayPlan() {}
    DayPlan(vector<Task> &tasks, int day)
    {
        this->day = day;
        this->tasks = move(tasks);
    }
    DayPlan(const DayPlan &other)
    {
        this->day = other.day;
        this->tasks = move(other.tasks);
    }
    DayPlan &operator=(const DayPlan &other)
    {
        if (this != &other)
        {
            this->day = other.day;
            this->tasks = move(other.tasks);
        }
        return *this;
    }
    ostream &output(ostream &out) const
    {
        if (day == -1)
        {
            out << "Daily Tasks: " << endl;
            for (int i = 0; i < tasks.size(); i++)
            {
                out << tasks[i] << endl;
            }
        }
        else{
            out << "Daily Tasks: " << endl;
            for (int i = 0; i < tasks.size(); i++)
            {
                out << tasks[i] << endl;
            }
            out<<day<<endl;
        }
        return out;
    }
    istream &input(istream &in)
    {
        cout << "Day Plan: " << endl;
        Task aux;
        in >> aux;
        tasks.push_back(aux);
        return in;
    }
    friend ostream &operator<<(ostream &out, DayPlan &obj)
    {
        return obj.output(out);
    }
    friend istream &operator>>(istream &in, DayPlan &obj)
    {
        return obj.input(in);
    }
    void addTask()
    {
        cout << "Task: " << endl;
        Task aux;
        cin >> aux;
        tasks.push_back(aux);
    }
};
class MonthPlan : public DayPlan 
{
protected:
    DayPlan Days[32];
    int month;
public:
    void setMonth(int month) { this->month = month; }
    void addDays( DayPlan & Day) { Days[Day.getDay()] = Day; }
    // DayPlan getDays(){return this->Days;}

    MonthPlan(){
        this->month =-1;
    }
    MonthPlan(vector<Task> &tasks, int day, DayPlan Days[], int month):DayPlan(tasks,day){
        
        
        for(int i=0 ;i <32;i++)
        {
            this->Days[i] =Days[i];
        }
        this->month =month;
    }
    ~MonthPlan(){}
    MonthPlan(const MonthPlan & other):DayPlan(other){
       
         for(int i=0 ;i <32;i++)
        {
            this->Days[i] =Days[i];
        }
        this->month = other.month;
    }
    MonthPlan &operator=(const MonthPlan & other){
        if(this != &other){
            DayPlan::operator=(other);
         for(int i=0 ;i <32;i++)
        {
            this->Days[i] =other.Days[i];
        }
        this->month = other.month;
        }
        return *this;
    }
    istream &input(istream & in){
        cout << "Month Plan: " << endl;
        Task aux;
        in >> aux;
        tasks.push_back(aux);
        return in;

    }
    ostream &output(ostream & out){
          if (month == -1)
        {
            out << "Month Tasks: " << endl;
            for (int i = 0; i < tasks.size(); i++)
            {
                out <<tasks[i] << endl;
            }
        }
        return out;
    }
    friend ostream &operator<<(ostream &out, MonthPlan &obj)
    {
        return obj.output(out);
    }
    friend istream &operator>>(istream &in, MonthPlan &obj)
    {
        return obj.input(in);
    }
    friend void day2mon( DayPlan & Day,  MonthPlan & Month){
            Month.addDays(Day);
    }
};
class YearPlan : public MonthPlan
{
protected:
    MonthPlan Months[12];
    int year;
public:
    // void setYear(int year) { this->year = year; }
    void addMonths( MonthPlan & Month) { Months[1] = Month; }
    // MonthPlan getMonths() { return Months;}
    
    YearPlan() : MonthPlan(){
        year=-1;
    };
    YearPlan(vector<Task> &tasks, int day, DayPlan Days[], int month,MonthPlan Months[],int year):MonthPlan(tasks,  day,  Days,month){
         for(int i=0 ;i <12;i++)
        {
            this->Months[i] =Months[i];
        }
        this->year= year;
    }
    YearPlan(const YearPlan & other):MonthPlan(other){
        
          for(int i=0 ;i <12;i++)
        {
            this->Months[i] =Months[i];
        }
        this->year = other.year;
    }
    YearPlan &operator=(const YearPlan & other){
        if(this != &other){
            MonthPlan::operator=(other);
                for(int i=0 ;i <12;i++)
        {
            this->Months[i] =Months[i];
        }
            this->year = other.year;
        }
        return *this;
    }
    istream &input(istream & in){
        cout << "Year Plan: " << endl;
        Task aux;
        in >> aux;
        tasks.push_back(aux);
        return in;
    }
       ostream &output(ostream & out){
          if (month == -1)
        {
            out << "Year Tasks: " << endl;
            for (int i = 0; i < tasks.size(); i++)
            {
                out <<tasks[i] << endl;
            }
        }
        else{
            // out << "Year Unorganized Tasks: " << endl;
            // for (int i = 0; i < tasks.size(); i++)
            // {
            //     out <<tasks[i] << endl;
            // } 
            out << "Year Tasks: " << endl;
            for (int i=0;i<12;i++){
                cout<<"Luna "<<i<<endl;
                for (int j=0;j<31;j++){
                    cout<<"Ziua "<<j<<endl;
                    for (int t = 0; t < tasks.size(); t++){

                        // out <<Months[i].getDays()[j].tasks[t] << endl;
                        }         
                }

            }

        }
        return out;
    }
    friend ostream &operator<<(ostream &out, YearPlan &obj)
    {
        return obj.output(out);
    }
    friend istream &operator>>(istream &in, YearPlan &obj)
    {
        return obj.input(in);
    }
    
    friend void mon2year( MonthPlan & Month,  YearPlan & Year){
        Year.addMonths(Month);
    }

};
class Planner
{
private:
    set <DayPlan *> Templates;
    list <YearPlan> Years;
    Planner() = default;
public:
    list<YearPlan> getYears(){ return  Years; }
    Planner(const Planner &obj) = delete;
    static Planner &getPlanner()
    {
        static Planner instance;
        return instance;
    }
    void addDate()
    {   
        int Day, Month, Year;
        bool validDate =1;
        while(validDate==false){
        cout<<"Add Date(Day Month Year): "<<endl;
        cin>>Day>>Month>>Year;
        
        try{
            if(Month==2 && Day>28&&Day<1){
                throw("Invalid Date");  

            }
            else if (Month%2==0 && Day>30&&Day<1){
                throw("Invalid Date");
            }
            else if (Month%2==1 && Day>31&&Day<1){
                throw("Invalid Date");
            }
            validDate = true;
        }
        catch(...)
        {
            validDate = false;
        }
        }

        if (Years.size()==0){
            // DayPlan *aux = new DayPlan;
            // cin>>*aux;
            // YearPlan 
            // YearPlan *aux2= dynamic_cast<YearPlan*>(aux);
            // delete aux;
            // cout<<Day<<Month<<Year;
            // cout<<typeid(aux2).name();
            // cout<<(*aux2);

            
            YearPlan year ;
            // year.setYear(Year);
            // MonthPlan month;
            // month.setMonth(Month);
            // DayPlan day;
            // cin>>day;
            // day.setDay(Day);
            // day2mon(day,month);
            // mon2year(month,year);  
            cin>>year;

            Years.push_back(year);


        }
    }
    // template<typename t>
    // void sortByDate(const YearPlan & plan){

    // }
    
    
};    

int main()
{

    Planner &Planner1 = Planner::getPlanner();
    Planner1.addDate();
    
    // DayPlan d;
    // cin>>d;
    // d.setDay(4);
    // cout<<d;
}