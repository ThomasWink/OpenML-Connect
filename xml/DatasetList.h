//DatasetList.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <list>
#include <unordered_map>
#include "Dataset.h"

//using namespace std;


/// <summary> Class stores a list of Datasets, which can be returned with appropiate functions. </summary>
class DatasetList {
    private:
        std::list <Dataset> listOfDatasets;

    public:
        DatasetList(){
            
        };

        DatasetList(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::list<std::string> dList = paramList["oml:dataset"];
            for (auto const& it : dList) {
                XMLParser localParse;
                int err;
                std::cout << "DatasetAutput: " << it << std::endl;
                Dataset d = Dataset(localParse.parseFromString("oml:dataset", it, err));//TODO iets met err?
                listOfDatasets.push_back(d);
            }
        };

        ~DatasetList(){

        };

        //TODO build tools for DatasetsLists

        std::list<Dataset> getDatasetList(){
            return this->listOfDatasets;
        }

};