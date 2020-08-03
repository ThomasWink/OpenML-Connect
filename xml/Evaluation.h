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
#include <sstream>

/// <summary> Class stores a single evaluation, which can be returned with appropiate functions. </summary>
class Evaluation
{
    private:
        int runID;

        int uploader;

        int taskID;

        int setupID;

        int flowID;

        int dataID;

        int evaluationEngineID;

        double value;

        std::string flowName;

        std::string dataName;

        std::string function;

        std::string uploadTime;

        std::vector<double> arrayData;


    public:
        Evaluation(){

        };

        Evaluation(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::string::size_type sizeOfString;
            Tagged tagger = Tagged();

            this->runID = std::stoi(tagger.getTag(paramList["oml:run_id"].front()) ,&sizeOfString);
            this->uploader = std::stoi(tagger.getTag(paramList["oml:uploader"].front()) ,&sizeOfString);
            this->taskID = std::stoi(tagger.getTag(paramList["oml:task_id"].front()) ,&sizeOfString);
            this->setupID = std::stoi(tagger.getTag(paramList["oml:setup_id"].front()) ,&sizeOfString);
            this->flowID = std::stoi(tagger.getTag(paramList["oml:flow_id"].front()) ,&sizeOfString);
            this->dataID = std::stoi(tagger.getTag(paramList["oml:data_id"].front()) ,&sizeOfString);
            this->evaluationEngineID = std::stoi(tagger.getTag(paramList["oml:evaluation_engine_id"].front()) ,&sizeOfString);
            this->value = std::stod(tagger.getTag(paramList["oml:value"].front()) ,&sizeOfString);
            this->flowName = tagger.getTag(paramList["oml:flow_name"].front());
            this->dataName = tagger.getTag(paramList["oml:data_name"].front());
            this->function = tagger.getTag(paramList["oml:function"].front());
            this->uploadTime = tagger.getTag(paramList["oml:upload_time"].front());

            //parse array from https://www.daniweb.com/programming/software-development/threads/353342/convert-string-into-double-array

            if(paramList.count("oml:array_data")>0){
                std::string s = tagger.getTag(paramList["oml:array_data"].front());
                std::size_t pos = 0;
                double d = 0.0;
                // convert ',' to ' '
                while (pos < s.size ())
                    if ((pos = s.find_first_of (',',pos)) != std::string::npos)
                        s[pos] = ' ';
                std::stringstream ss(s);
                while (ss >> d)
                    arrayData.push_back (d);
            }
            //delete tagger;
        };

        ~Evaluation(){

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

        int getDataID(){
            return this->dataID;
        }

        int getEvaluationEngineID(){
            return this->evaluationEngineID;
        }

        int getUploader(){
            return this->uploader;
        }

        double getValue(){
            return this->value;
        }

        std::string getFlowName(){
            return this->flowName;
        }

        std::string getDataName(){
            return this->dataName;
        }

        std::string getFunction(){
            return this->function;
        }

        std::string getUploadTime(){
            return this->uploadTime;
        }

        std::vector<double> getArrayData(){
            return this->arrayData;
        }

};