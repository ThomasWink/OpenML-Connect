//TaskList.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <unordered_map>
#include <list>
//#include "../src/Tagged.h"
//#include "../src/XMLParser.h"
#include "Task.h"

/// <summary> Class stores a list of tasks, which can be returned with appropiate functions. </summary>
class TaskList
{
    private:

        std::list<Task> listOfTasks;


    public:
        TaskList(){

        };

        TaskList(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::list<std::string> tList = paramList["oml:task"];
            for (auto const& it : tList) {
                XMLParser localParse;
                int err;
                Task t = Task(localParse.parseFromString("oml:task", it, err));//TODO iets met err?
                listOfTasks.push_back(t);
            }
        };

        ~TaskList(){

        };

        std::list<Task> getTaskList(){
            return this->listOfTasks;
        }

};