//Dataupload.h
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

/// <summary> Class stores a single Dataupload, which can be returned with appropiate functions. </summary>

class Dataupload
{
    private:
        int id;
    public:
        Dataupload(){

        };

        ~Dataupload(){

        };

        Dataupload(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::string::size_type sizeOfString;
            Tagged tagger = Tagged();

            if(paramList.count("oml:id") > 0)
                this->id = std::stoi(tagger.getTag(paramList["oml:id"].front()) ,&sizeOfString);            
            
        }

        int getID(){
            return this->id;
        }
};