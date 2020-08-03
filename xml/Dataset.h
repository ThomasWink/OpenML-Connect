//Dataset.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <list>
#include <unordered_map>

//using namespace std;

/// <summary> Class stores a single dataset, which can be returned with appropiate functions. </summary>
class Dataset {
    private:
        int did;

        int version;

        int uploader;

        int fileID;

        std::string name;

        std::string status;

        std::string format;

        QualitiesList listOfQualities;

    public:
        Dataset(){

        }

        Dataset(std::unordered_map<std::string, std::list<std::string>> paramList){
            std::string::size_type sizeOfString;
            Tagged tagger = Tagged();
            this->did = std::stoi(tagger.getTag(paramList["oml:did"].front()) ,&sizeOfString);
            this->version = std::stoi(tagger.getTag(paramList["oml:version"].front()) ,&sizeOfString);
            this->uploader = std::stoi(tagger.getTag(paramList["oml:uploader"].front()) ,&sizeOfString);
            this->fileID = std::stoi(tagger.getTag(paramList["oml:file_id"].front()) ,&sizeOfString);
            this->name = tagger.getTag(paramList["oml:name"].front());
            this->status = tagger.getTag(paramList["oml:status"].front());
            this->format = tagger.getTag(paramList["oml:format"].front());
            this->listOfQualities = QualitiesList(paramList);
        }

        ~Dataset(){

        }

        //getters and setters
        //int
        void setDid(int did) { this->did = did; } 
        int getDid() { return this->did; }
        void setVersion(int version) { this->version = version; } 
        int getVersion() { return this->version; }
        void setUploader(int uploader) { this->uploader = uploader; } 
        int getUploader() { return this->uploader; }
        void setFileID(int fileID) { this->fileID = fileID; } 
        int getFileID() { return this->fileID; }
        //string
        void setName(std::string name) { this->name = name; } 
        std::string getName() { return this->name; }
        void setStatus(std::string status) { this->status = status; } 
        std::string getStatus() { return this->status; }
        void setFormat(std::string format) { this->format = format; } 
        std::string getFormat() { return this->format; }
        //Qualities
        void setListOfQualities(QualitiesList listOfQualities) { this->listOfQualities = listOfQualities; } 
        QualitiesList getListOfQualities() { return this->listOfQualities; }


};