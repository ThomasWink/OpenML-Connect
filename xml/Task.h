//Task.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <unordered_map>
#include <list>
//#include "../src/Tagged.h"
#include "../src/XMLParser.h"
#include "TaskInput.h"

/// <summary> Class stores a single task, which can be returned with appropiate functions. </summary>
class Task
{
    private:
        int taskID;

        int typeID;

        std::list<std::string> tags;

        std::list<TaskInput> listOfInputs;

        QualitiesList listOfQualities;


    public:
        Task(){

        };

        Task(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::string::size_type sizeOfString;
            Tagged tagger = Tagged();
            this->taskID = std::stoi(tagger.getTag(paramList["oml:task_id"].front()) ,&sizeOfString);
            this->typeID = std::stoi(tagger.getTag(paramList["oml:task_type_id"].front()) ,&sizeOfString);
            std::list<std::string> iList = paramList["oml:input"];
            for (auto const& it : iList) {
                XMLParser localParse;
                int err;
                std::cout << "TaskAutput: " << it << std::endl;
                TaskInput i = TaskInput(localParse.parseFromString("oml:input", it, err));//TODO iets met err?
                listOfInputs.push_back(i);
            }
            std::list<std::string> tList = paramList["oml:tag"];
            for (auto const& it : tList) {
                tags.push_back(tagger.getTag(it));
            }
            this->listOfQualities = QualitiesList(paramList);
            //delete tagger;
        };

        ~Task(){

        };

        int getID(){
            return this->taskID;
        }

        int getTypeID(){
            return this->typeID;
        }

        std::list<std::string> getTags(){
            return this->tags;
        }

        std::list<TaskInput> getInputs(){
            return this->listOfInputs;
        }

};