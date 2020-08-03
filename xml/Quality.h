//Quality.h
//Thomas Wink
#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <list>
#include <unordered_map>

//using namespace std;

/// <summary> Class stores a single quality, which can be returned with appropiate functions. </summary>
class Quality {
    private:
        std::string name;
        
        double value;
        
    public:

        Quality(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::string::size_type sizeOfString;
            Tagged tagger = Tagged();
            this->name = tagger.getTag(paramList["oml:name"].front());
            std::cout << this->name << std::endl;
            if(!paramList["oml:value"].empty())
                std::cout << tagger.getTag(paramList["oml:value"].front()) << std::endl;
                this->value = std::stod(tagger.getTag(paramList["oml:value"].front()) ,&sizeOfString);
        }

        Quality(){
            this->name = "None";
            this->value = 0;
        }

        std::string getName(){
            return this->name;
        }

        double getValue(){
            return this->value;
        }
        ~Quality(){

        }
};