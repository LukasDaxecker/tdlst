#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <string>
#include <list>

using namespace std;

typedef struct Task {
    int iID;
    string sTitle;
    string sTask;
    string sDeadline;
    bool bFinished;
} tTask;

class TaskMngr {
    public:
        TaskMngr() : m_iID(0), m_sPath("/tmp/tdlst_data.csv") {}
        ~TaskMngr() {}

    private:
        int m_iID;
        list<tTask*> m_listTasks;
        string m_sPath;

    public:
        bool ReadFile();
        bool WriteFile();
        void ListTasks(const bool flag) const;
        void AddTask(const string title, const string task = "", const string deadline = "");
        void FinishTask(const string title);
        void FinishTask(const int iID);
        void DeleteTask(const string title);
        void DeleteTask(const int iID);
};

bool TaskMngr::WriteFile() 
{
    ofstream file(m_sPath);
    if(!file.is_open()) return false;
    for(tTask* task : m_listTasks)
    {
        file << task->iID << "," 
             << "\"" << task->sTitle << "\"," 
             << "\"" << task->sTask << "\"," 
             << "\"" << task->sDeadline << "\"," 
             << task->bFinished << "\n";
    }
    file.close();
    return true;
}

bool TaskMngr::ReadFile()
{
    ifstream file(m_sPath);
    if(!file.is_open()) return false;

    string line;
    while(getline(file, line))
    {
        size_t pos = 0;
        string token;
        int field = 0;

        int iID = 0;
        string sTitle, sTask, sDeadline;
        bool bFinished = false;

        string temp = line;
        while ((pos = temp.find(',')) != string::npos)
        {
            token = temp.substr(0, pos);

            switch(field)
            {
                case 0: iID = stoi(token); break;
                case 1: sTitle = token; break;
                case 2: sTask = token; break;
                case 3: sDeadline = token; break;
            }

            temp.erase(0, pos + 1);
            field++;
        }
        // Last field: bFinished
        bFinished = stoi(temp) != 0;


        sTitle = sTitle.substr(1, sTitle.size()-2);
        sTask = sTask.substr(1, sTask.size()-2);
        sDeadline = sDeadline.substr(1, sDeadline.size()-2);
        tTask* ntask = new tTask{iID, sTitle, sTask, sDeadline, bFinished};
        m_listTasks.push_back(ntask);

        if(iID >= m_iID) m_iID = iID + 1; // keep ID unique
    }

    file.close();
    return true;
}

void TaskMngr::ListTasks(const bool flag) const
{
    for(tTask* task : m_listTasks)
    {
        if(task->bFinished != flag) continue;
        if(!task->sDeadline.empty()) {
            printf("%d. %s - %s\n", task->iID, task->sTitle.c_str(), task->sDeadline.c_str());
            printf("\t%s\n", task->sTask.c_str());
        } else {
            printf("%d. %s\n", task->iID, task->sTitle.c_str());
        }
    }
}

void TaskMngr::AddTask(const string title, const string task, const string deadline)
{
    tTask* ntask = new tTask{m_iID, title, task, deadline, false};

    m_listTasks.push_back(ntask);
    m_iID++;
}

void TaskMngr::FinishTask(const string title)
{
    for(tTask* task : m_listTasks)
    {
        if(task->sTitle != title) continue;
        task->bFinished = true;
        return;
    }
    printf("Task %s was not found\n", title.c_str());
}

void TaskMngr::FinishTask(const int iID)
{
    for(tTask* task : m_listTasks)
    {
        if(task->iID != iID) continue;
        task->bFinished = true;
        return;
    }
    printf("Task with ID %d was not found\n", iID);
}

void TaskMngr::DeleteTask(const string title)
{
    for(tTask* task : m_listTasks)
    {
        if(task->sTitle != title) continue;
        m_listTasks.remove(task);
        return;
    }
    printf("Task %s was not found\n", title.c_str());
}

void TaskMngr::DeleteTask(const int iID)
{
    for(tTask* task : m_listTasks)
    {
        if(task->iID != iID) continue;
        m_listTasks.remove(task);
        return;
    }
    printf("Task with ID %d was not found\n", iID); 
}

//------------------------
// Main
//------------------------

void PrintHelp();

int main(int argc, char** argv) 
{
    TaskMngr mgr; 
    mgr.ReadFile();
    
    switch(argc) {
        case 1:
            mgr.ListTasks(false);
            break;
        case 2:
            if(strcmp(argv[1], "-C") != 0) {
                PrintHelp();
                break;
            }
            mgr.ListTasks(true);
            break;
        case 3:
            if(strcmp(argv[1], "-D") == 0) {
                mgr.DeleteTask(argv[2]);
                mgr.WriteFile();
            }
            else if(strcmp(argv[1], "-d") == 0) {
                mgr.DeleteTask(atoi(argv[2]));
                mgr.WriteFile();
            }
            else if(strcmp(argv[1], "-F") == 0) {
                mgr.FinishTask(argv[2]);
                mgr.WriteFile();
            }
            else if(strcmp(argv[1], "-f") == 0) {
                mgr.FinishTask(atoi(argv[2]));
                mgr.WriteFile();
            }
            else if(strcmp(argv[1], "-A") == 0) {
                mgr.AddTask(argv[2]);
                mgr.WriteFile();
            }
            else
                PrintHelp();
            break;
        case 5:
            if(strcmp(argv[1], "-A") != 0) {
                PrintHelp();
                break;
            }
            mgr.AddTask(argv[2], argv[3], argv[4]);
            mgr.WriteFile();
            break;
        default:
            PrintHelp();
            break;
    }
}

void PrintHelp()
{
    printf("tdlst [-C | -d|-f <ID> | -D|-F <TITLE> | -A <TITLE [DESC DEADLINE]>]\n\n");
    printf("Options:\n");
    printf("    * none ... Prints current list\n");
    printf("    * -C   ... Prints list of completed tasks\n");
    printf("    * -d <ID> ... Deletets task with given ID\n");
    printf("    * -f <ID> ... Finish task with given ID\n");
    printf("    * -D <TITLE> ... Deletets task with given title\n");
    printf("    * -F <TITLE> ... Finish task with given title\n");
    printf("    * -A <PARAM> ... Add task\n");
    printf("        PARAM:\n");
    printf("        * TITLE     ... Title of the task\n");
    printf("        * DESC      ... Task description\n");
    printf("        * DEADLINE  ... Deadline\n");
}
