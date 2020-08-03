//Run.h
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

/// <summary> Class stores a single run, which can be returned with appropiate functions. </summary>

class Run
{
    private:
        int runID;

        int uploader;

        int taskID;

        int setupID;

        int flowID;

        int taskTypeID;

        std::string errorMessage;

        std::string uploadTime;

        std::string runDetails;


    public:
        Run(){

        };

        Run(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::string::size_type sizeOfString;
            Tagged tagger = Tagged();

            this->runID = std::stoi(tagger.getTag(paramList["oml:run_id"].front()) ,&sizeOfString);
            this->uploader = std::stoi(tagger.getTag(paramList["oml:uploader"].front()) ,&sizeOfString);
            this->taskID = std::stoi(tagger.getTag(paramList["oml:task_id"].front()) ,&sizeOfString);
            this->setupID = std::stoi(tagger.getTag(paramList["oml:setup_id"].front()) ,&sizeOfString);
            this->flowID = std::stoi(tagger.getTag(paramList["oml:flow_id"].front()) ,&sizeOfString);
            this->taskTypeID = std::stoi(tagger.getTag(paramList["oml:task_type_id"].front()) ,&sizeOfString);
            if(paramList.count("oml:error_message") > 0)
                this->errorMessage = tagger.getTag(paramList["oml:error_message"].front());
            if(paramList.count("oml:run_details") > 0)
                this->runDetails = tagger.getTag(paramList["oml:run_details"].front());
            this->uploadTime = tagger.getTag(paramList["oml:upload_time"].front());

        };

        ~Run(){

        };

        int getRunID(){
            return this->runID;
        }

        int getTaskID(){
            return this->taskID;
        }

        int getSetupID(){
            return this->setupID;
        }

        int getFlowID(){
            return this->flowID;
        }

        int getTaskTypeID(){
            return this->taskTypeID;
        }

        int getUploader(){
            return this->uploader;
        }

        std::string getErrorMessage(){
            return this->errorMessage;
        }

        std::string getRunDetails(){
            return this->runDetails;
        }

        std::string getUploadTime(){
            return this->uploadTime;
        }

};