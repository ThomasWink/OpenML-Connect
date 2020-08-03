//DatasetDescription.h
//Thomas Wink

#pragma once
#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <list>
#include <unordered_map>

//using namespace std;

/// <summary> Class stores a single datasetdescription, which can be returned with appropiate functions. </summary>
class DatasetDescription {
    private:
        /* data */

        int id;

        int file_id;

        std::string name;
        
        std::string version;
        
        std::string description;
        
        std::string format;
        
        std::string collection_date;
        
        std::string upload_date;
        
        std::string language;
        
        std::string licence;
        
        std::string url;
        
        std::string default_target_attribute;
        
        std::string row_id_attribute;
        
        std::string version_label;
        
        std::string citation;
        
        std::string visibility;
        
        std::string original_data_url;
        
        std::string paper_url;
        
        std::string update_comment;
        
        std::string status;
        
        std::string processing_date;
        
        std::string error;
        
        std::string warning;

        std::string md5_checksum;

        std::list <std::string> creator;

        std::list <std::string> tag;

        std::list <std::string> contributor;

        std::list <std::string> ignore_attribute;

        //Private functions

    public:     //TODO add all getters and setters

        //default constructor
        DatasetDescription(){
            this->id = -10;
            this->file_id = -1;
        };

        DatasetDescription(std::string n, std::string d, std::string f){
            this->name = n;
            this->description = d;
            this->format = f;
        }

        DatasetDescription(std::unordered_map<std::string, std::list<std::string>> paramList){ 
            Tagged tagger = Tagged();
            this->id = std::stoi(tagger.getTag(paramList["oml:id"].front()));
            this->file_id = std::stoi(tagger.getTag(paramList["oml:file_id"].front()));
            
            
            this->name = tagger.getTag(paramList["oml:name"].front());
            this->version = tagger.getTag(paramList["oml:version"].front());
            this->description = tagger.getTag(paramList["oml:description"].front());
            this->format = tagger.getTag(paramList["oml:format"].front());
            this->collection_date = tagger.getTag(paramList["oml:collection_date"].front());
            this->upload_date = tagger.getTag(paramList["oml:upload_date"].front());
            this->licence = tagger.getTag(paramList["oml:licence"].front());
            this->url = tagger.getTag(paramList["oml:url"].front());
            this->default_target_attribute = tagger.getTag(paramList["oml:default_target_attribute"].front());
            this->version_label = tagger.getTag(paramList["oml:version_label"].front());
            this->visibility = tagger.getTag(paramList["oml:visibility"].front());
            this->original_data_url = tagger.getTag(paramList["oml:original_data_url"].front());
            this->paper_url = tagger.getTag(paramList["oml:paper_url"].front());
            this->status = tagger.getTag(paramList["oml:status"].front());
            this->processing_date = tagger.getTag(paramList["oml:processing_date"].front());
            this->md5_checksum = tagger.getTag(paramList["oml:md5_checksum"].front());

            this->tag = paramList["oml:tag"]; //TODO
            this->creator = paramList["oml:creator"]; //TODO
        };

        ~DatasetDescription(){
            
        };

        //void setId(int id) { this->id = id; } 
        int getId() { return this->id; }
        //void setFile_id(int file_id) { this->file_id = file_id; } 
        int getFile_id() { return this->file_id; }

        void setName(std::string name) { this->name = name; } 
        std::string getName() { return this->name; }
        void setVersion(std::string version) { this->version = version; } 
        std::string getVersion() { return this->version; }
        void setDescription(std::string description) { this->description = description; } 
        std::string getDescription() { return this->description; }
        void setFormat(std::string format) { this->format = format; } 
        std::string getFormat() { return this->format; }
        void setCollection_date(std::string collection_date) { this->collection_date = collection_date; } 
        std::string getCollection_date() { return this->collection_date; }
        //void setUpload_date(std::string upload_date) { this->upload_date = upload_date; } 
        std::string getUpload_date() { return this->upload_date; }
        void setLanguage(std::string language) { this->language = language; } 
        std::string getLanguage() { return this->language; }
        void setLicence(std::string licence) { this->licence = licence; } 
        std::string getLicence() { return this->licence; }
        void setUrl(std::string url) { this->url = url; } 
        std::string getUrl() { return this->url; }
        void setDefault_target_attribute(std::string default_target_attribute) { this->default_target_attribute = default_target_attribute; } 
        std::string getDefault_target_attribute() { return this->default_target_attribute; }
        void setRow_id_attribute(std::string row_id_attribute) { this->row_id_attribute = row_id_attribute; } 
        std::string getRow_id_attribute() { return this->row_id_attribute; }
        void setVersion_label(std::string version_label) { this->version_label = version_label; } 
        std::string getVersion_label() { return this->version_label; }
        void setCitation(std::string citation) { this->citation = citation; } 
        std::string getCitation() { return this->citation; }
        void setVisibility(std::string visibility) { this->visibility = visibility; } 
        std::string getVisibility() { return this->visibility; }
        void setOriginal_data_url(std::string original_data_url) { this->original_data_url = original_data_url; } 
        std::string getOriginal_data_url() { return this->original_data_url; }
        void setPaper_url(std::string paper_url) { this->paper_url = paper_url; } 
        std::string getPaper_url() { return this->paper_url; }
        void setUpdate_comment(std::string update_comment) { this->update_comment = update_comment; } 
        std::string getUpdate_comment() { return this->update_comment; }
        //void setStatus(std::string status) { this->status = status; } 
        std::string getStatus() { return this->status; }
        //void setProcessing_date(std::string processing_date) { this->processing_date = processing_date; } 
        std::string getProcessing_date() { return this->processing_date; }
        //void setError(std::string error) { this->error = error; } 
        std::string getError() { return this->error; }
        //void setWarning(std::string warning) { this->warning = warning; } 
        std::string getWarning() { return this->warning; }
        //void setMd5_checksum(std::string md5_checksum) { this->md5_checksum = md5_checksum; } 
        std::string getMd5_checksum() { return this->md5_checksum; }

        //list
        void setCreator(std::list<std::string> creator) { this->creator = creator; } 
        std::list<std::string> getCreator() { return this->creator; }
        void setTag(std::list<std::string> tag) { this->tag = tag; } 
        std::list<std::string> getTag() { return this->tag; }
        void setContributor(std::list<std::string> contributor) { this->contributor = contributor; } 
        std::list<std::string> getContributor() { return this->contributor; }
        void setIgnore_attribute(std::list<std::string> ignore_attribute) { this->ignore_attribute = ignore_attribute; } 
        std::list<std::string> getIgnore_attribute() { return this->ignore_attribute; }

};