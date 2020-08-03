//FlowList.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <list>
#include <unordered_map>
//#include "../src/XMLParser.h"
#include "Flow.h"

/// <summary> Class stores a list of flows, which can be returned with appropiate functions. </summary>
class FlowList {
    private:
        std::list<Flow> listOfFlows;

    public:
        FlowList(){

        };

        FlowList(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::list<std::string> fList = paramList["oml:flow"];
            for (auto const& it : fList) {
                XMLParser localParse;
                int err;
                std::cout << "FlowsetOutput: " << it << std::endl;
                Flow f = Flow(localParse.parseFromString("oml:flow", it, err));//TODO iets met err?
                listOfFlows.push_back(f);
            }
        };

        ~FlowList(){

        };

        //TODO build tools for FlowLists

        std::list<Flow> getFlowList(){
            return this->listOfFlows;
        }
};