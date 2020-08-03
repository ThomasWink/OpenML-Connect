//File.h
//Thomas Wink
//#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <unordered_map>
#include <list>
#include <fstream>
//#include "Tagged.h"

/// <summary> Class makes a file in the same directory, which can be used for uploads. </summary>
class File
{
    private:
        std::string filename;
    public:
        File(std::string filename){
            this->filename = filename;
        };

        ~File(){

        };

        void makeDataset(std::string name, std::string description, std::string format){ //convert to list of attributes and list of values
            std::ofstream out(filename);
            out << "<oml:data_set_description xmlns:oml=\"http://openml.org/openml\"> \n";
            out << "<oml:name>" << name << "</oml:name>\n";
            out << "<oml:description>" << description << "</oml:description>\n";
            out << "<oml:format>" << format << "</oml:format>\n";
            out << "</oml:data_set_description>";
            out.close();
        }
};