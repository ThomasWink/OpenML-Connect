//QualitiesList.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <list>
#include <unordered_map>
#include "Quality.h"

//using namespace std;



/// <summary> Class stores a list of qualities, which can be returned with appropiate functions. </summary>
class QualitiesList {
    private:
        std::list <Quality> listOfQualities;
    public:
        //default
        QualitiesList(){}

        QualitiesList(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::list<std::string> qList = paramList["oml:quality"];
            for (auto const& it : qList) {
                XMLParser localParse;
                int err;
                //std::cout << "qualityoutput: " << it << std::endl; TODO
                Quality q = Quality(localParse.parseFromString("oml:quality", it, err));//TODO iets met err?
                listOfQualities.push_back(q);
                
            }
        }

        ~QualitiesList(){}

        void test(){//TODO remove
            for (auto& it : listOfQualities) {
                cout << it.getName() << endl
                     << it.getValue() << endl;
            }
            //return "test2";//quality.front();
        }

        std::list<Quality> getQualityList(){
            return this->listOfQualities;
        }

};