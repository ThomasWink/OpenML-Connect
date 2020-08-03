//Evaluation.h
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
#include "Evaluation.h"

/// <summary> Class stores a list of evaluations, which can be returned with appropiate functions. </summary>
class EvaluationList
{
    private:

        std::list<Evaluation> listOfEvaluations;

    public:
        EvaluationList(){

        };

        EvaluationList(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::list<std::string> eList = paramList["oml:evaluation"];
            for (auto const& it : eList) {
                XMLParser localParse;
                int err;
                Evaluation e = Evaluation(localParse.parseFromString("oml:evaluation", it, err));//TODO iets met err?
                listOfEvaluations.push_back(e);
            }
        };

        ~EvaluationList(){

        };

        std::list<Evaluation> getEvaluationList(){
            return this->listOfEvaluations;
        }

};