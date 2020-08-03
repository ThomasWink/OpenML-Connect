//Tagged.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <unordered_map>
#include <list>


/// <summary> Class provides a way to remove artifacts from .xml files. </summary>

class Tagged
{
    private:

    public:
        Tagged(){

        };

        ~Tagged(){

        };

        std::string getTag(std::string untag){ //deletes all surplus tags in te string untag
            std::size_t foundFirst = untag.find_first_of(">");
            std::size_t foundLast;
            std::size_t valueLength;
            while(foundFirst != std::string::npos){
                foundLast = untag.find_last_of("<");
                valueLength = (foundLast - foundFirst) - 1;
                untag = untag.substr (foundFirst + 1, valueLength);
                foundFirst = untag.find_first_of(">");
            }
            return untag;
        }
        
};
