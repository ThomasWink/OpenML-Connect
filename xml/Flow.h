//Flow.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <list>
#include <unordered_map>
#include "Component.h"
#include "../src/XMLParser.h"

//using namespace std;

// Elaboration of the class as it was declared in Component.h
Flow::Flow(std::unordered_map<std::string, std::list<std::string>> paramList){
    params = paramList;
    parse();
}

void Flow::parse(void){
    Tagged tagger = Tagged();

    if(params.count("oml:id")>0)
        this->id = std::stoi(tagger.getTag(params["oml:id"].front()));
    if(params.count("oml:uploader")>0)
        this->uploader = std::stoi(tagger.getTag(params["oml:uploader"].front()));
    if(params.count("oml:version")>0)
        this->version = std::stoi(tagger.getTag(params["oml:version"].front()));

    if(params.count("oml:name")>0)
        this->name = tagger.getTag(params["oml:name"].front());
    if(params.count("oml:full_name")>0)
        this->full_name = tagger.getTag(params["oml:full_name"].front());
    if(params.count("oml:class_name")>0)
        this->class_name = tagger.getTag(params["oml:class_name"].front());
    if(params.count("oml:external_version")>0)
        this->external_version = tagger.getTag(params["oml:external_version"].front());
    if(params.count("oml:description")>0)
        this->description = tagger.getTag(params["oml:description"].front());
    if(params.count("oml:upload_date")>0)
        this->upload_date = tagger.getTag(params["oml:upload_date"].front());
    if(params.count("oml:language")>0)
        this->language = tagger.getTag(params["oml:language"].front());
    if(params.count("oml:dependencies")>0)
        this->dependencies = tagger.getTag(params["oml:dependencies"].front());


    XMLParser localParse;
    int err;
    std::list<std::string> hList = params["oml:tag"];
    for (auto const& it : hList) {
        tags.push_back(tagger.getTag(it));
    }
    hList = params["oml:parameter"];
    for (auto const& it : hList) {
        std::cout << "Parameteroutput: " << it << std::endl;
        Parameter p = Parameter(localParse.parseFromString("oml:parameter", it, err));
        parameters.push_back(p);
        localParse.clear();
    }
    hList = params["oml:component"];
    for (auto const& it : hList) {
        std::cout << "Componentoutput: " << it << std::endl;
        Component c = Component(localParse.parseFromString("oml:component", it, err));//TODO iets met err?
        listOfComponents.push_back(&c);
        localParse.clear();
    }
}

Flow* Flow::recast(void){
    Flow * f = dynamic_cast<Flow*>(this);
    XMLParser localParse;
    int err;
    std::cout << "parseflowagain: " << std::endl;
    std::unordered_map<std::string, std::list<std::string>> paramList;
    std::list<std::string> hList = params["oml:flow"];
    for (auto const& it : hList) {//TODO dit wordt maar 1 keer gedaan, moet slimmer/netter
        paramList = localParse.parseFromString("oml:flow", it, err);
    }
    params = paramList;
    f->parse();
    std::cout << "parseflowagain2: " << std::endl;
    return f;
}

int Flow::getID(){
    return this->id;
}