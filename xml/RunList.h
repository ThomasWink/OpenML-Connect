//runList.h
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
#include "Run.h"

/// <summary> Class stores a list of runs, which can be returned with appropiate functions. </summary>
class RunList
{
    private:

        std::list<Run> listOfRuns;

    public:
        RunList(){

        };

        RunList(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::list<std::string> rList = paramList["oml:run"];
            for (auto const& it : rList) {
                XMLParser localParse;
                int err;
                Run r = Run(localParse.parseFromString("oml:run", it, err));//TODO iets met err?
                listOfRuns.push_back(r);
            }
        };

        ~RunList(){

        };

        std::list<Run> getRunList(){
            return this->listOfRuns;
        }

};