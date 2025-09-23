#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int PrintList();
int AddTask(const string title, const string contents, const string date);
int FinishTask(const string title);
int DeleteTask(const string title);

int main()
{
    system("rm /tmp/tdlst_data.csv");
    int retval = 0;
    retval = DeleteTask("T1");
    retval = FinishTask("T1");
    retval = PrintList();
    retval = FinishTask("T1");
    retval = DeleteTask("T1");
    retval = AddTask("T1", "Test Test test", "12.09");
    retval = AddTask("T3", "Test Test test", "12.09");
    retval = AddTask("T1", "Test test", "12.09");
    retval = AddTask("T4", "Test Test test", "12.09");
    retval = PrintList();
    retval = FinishTask("T1");
    retval = DeleteTask("T1");
    retval = FinishTask("T2");
    retval = DeleteTask("T2");
    retval = DeleteTask("T3");
    retval = FinishTask("T3");
    retval = PrintList();
    return retval;
}

int PrintList() 
{
    return system("./tdlst");
}

int AddTask(const string title, const string contents, const string date)
{
    string comp = "./tdlst -A " + title + contents + date;
    return system(comp.c_str());
}

int FinishTask(const string title)
{
    string comp = "./tdlst -F " + title;
    return system(title.c_str());
}

int DeleteTask(const string title)
{
    string comp = "./tdlst -D " + title;
    return system(title.c_str());
}
