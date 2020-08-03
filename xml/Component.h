//Component.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <list>
#include <unordered_map>
#include "OMLPrimitive.h"

//using namespace std;


/// <summary> Class stores a single Flow, which can be returned with appropiate functions.
/// Class inherits from OMLPrimitive. Is elaborated on in Flow.h
/// </summary>
class Flow : public OMLPrimitive {

    private:
        std::list<OMLPrimitive *> listOfComponents;

        int id;

        int uploader;

        int version;

        std::string name;

        std::string full_name;

        std::string class_name;

        std::string external_version;

        std::string description;

        std::string upload_date;

        std::string language;

        std::string dependencies;

        std::list<std::string> tags;

        std::list<Parameter> parameters;

    public:
        Flow(){

        };

        Flow(std::unordered_map<std::string, std::list<std::string>> paramList);

        void parse(void);

        Flow* recast(void);

        int getID();
};

/// <summary> Class stores a single Component, which can be returned with appropiate functions. 
/// Inherits from OMLPrimitive.
/// </summary>
class Component : public OMLPrimitive {
    private:
        std::string identifier;
        std::list<Flow*> listOfFlows; //TODO this should not be a list but a single pointer.
    public:
        Component(std::unordered_map<std::string, std::list<std::string>> paramList){
            Tagged tagger = Tagged();
            this->identifier = tagger.getTag(paramList["oml:identifier"].front());
            std::cout << this->identifier << endl;
            //zelf parsen, dan een omlprimitive maken en daar dan de parse functie op aanroepen, die uitgewerkt is in flow
            //TODO parsen en dan "paramList" anders doorgeven 
            std::cout << "nu primitive maken" << endl;
            
            OMLPrimitive * o = new Flow;
            o->setParams(paramList);
            Flow * f = o->recast();
            listOfFlows.push_back(f);
        }

    //TODO getter functies

};