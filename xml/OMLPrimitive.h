//OMLPrimitive.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <list>
#include <unordered_map>
#include "Parameter.h"

//using namespace std;

// forward declaration of Flow
class Flow;

/// <summary> Virtual class, Component and Flow both inherit from this class. </summary>
class OMLPrimitive {
    protected:
        std::unordered_map<std::string, std::list<std::string>> params;

        
    public:
        OMLPrimitive(){

        }

        OMLPrimitive(std::unordered_map<std::string, std::list<std::string>> paramList){
            params = paramList;
        }

        void setParams (std::unordered_map<std::string, std::list<std::string>> paramList){
            this->params = paramList;
        }

        virtual Flow* recast (void){

        };

        virtual void parse (void){

        };
};