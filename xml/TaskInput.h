//TaskInput.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <unordered_map>
#include <list>

/// <summary> Class stores a single taskinput, which can be returned with appropiate functions. </summary>
class TaskInput
{
    private:
        std::string name;

        std::string value;

    public:

        TaskInput(){

        };

        TaskInput(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::string::size_type sizeOfString;
            Tagged tagger = Tagged();
            this->name = tagger.getTag(paramList["oml:name"].front());
            this->value = tagger.getTag(paramList["oml:value"].front());
        };

        ~TaskInput(){

        };

        std::string getName(){
            return this->name;
        }

        std::string getValue(){
            return this->value;
        }

};

