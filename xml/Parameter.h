//Parameter.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <list>
#include <unordered_map>
#include "../src/XMLParser.h"

//using namespace std;

/// <summary> Class stores a single Parameter, which can be returned with appropiate functions. </summary>
class Parameter {
    private:
        std::string name;

        std::string data_type;

        std::string default_value;

        std::string description;

    public:
        Parameter(){

        }

        Parameter(std::unordered_map<std::string, std::list<std::string>> paramList){
            Tagged tagger = Tagged();
            this->name = tagger.getTag(paramList["oml:name"].front());
            this->data_type = tagger.getTag(paramList["oml:data_type"].front());
            this->default_value = tagger.getTag(paramList["oml:default_value"].front());
            this->description = tagger.getTag(paramList["oml:description"].front());
        }

        ~Parameter(){

        }

        //TODO maak getter functies
};