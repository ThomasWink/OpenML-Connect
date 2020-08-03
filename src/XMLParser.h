//XMLParser.h
//Thomas Wink
#pragma once

#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <rapidxml.hpp>
#include <unordered_map>
#include <list>

using namespace rapidxml;
using namespace std;


/// <summary> Class provides functionality to parse .xml to an unordered map of strings and a list of strings.
/// Can parse from an .xml file and from a string in .xml format.
/// </summary>
class XMLParser {
    private:
        //std::string filename;

        std::unordered_map<string, list<string>> paramList;

        bool printer = true;

        bool attributeCheck(std::string & buildstring, xml_node<> * loop_node, std::string value){
            if (loop_node->first_attribute()){
                cout << loop_node->name() << loop_node->name_size() << endl;
                const char *s = loop_node->name();
                std::string str(s);
                //cout << "bijna" << endl;
                /*if (loop_node->name() == "oml:input"){

                }
                else if(loop_node->name() == "oml:parameter"){

                }
                else if(loop_node->name() == "oml:output"){

                }
                else*/ if(str == "oml:input"){
                    buildstring.append("<oml:input><oml:name>");
                    buildstring.append(loop_node->first_attribute()->value());
                    buildstring.append("</oml:name><oml:value>" + value + "</oml:value></oml:input>");
                    //cout << "used" << endl;
                    
                }
                else if(str == "oml:flow"){
                    return false; //dont use this attribute
                }
                else if(str == "oml:quality"){
                    buildstring.append("<oml:quality><oml:name>");
                    buildstring.append(loop_node->first_attribute()->value());
                    buildstring.append("</oml:name><oml:value>" + value + "</oml:value></oml:quality>");
                    cout << "used" << endl;
                }
                else
                    return false;
                //cout << loop_node->first_attribute()->name() << " en " << loop_node->first_attribute()->value() << endl;
                return true;
            }
            return false;
        }

        std::string parseNodeToString(xml_node<> * loop_node){
            std::string returnstring = "";
            std::string hulp = "";
            std::string hulpLocal;
            std::string value;
            for (loop_node; loop_node; loop_node = loop_node->next_sibling()){
                hulpLocal = loop_node->name();//TODO camelcase of underscores, kies er 1
                //cout << "parseroutput:" << loop_node->value() << endl;
                //TODO parse child to text (recursive)

                value = loop_node->value();

                if( !attributeCheck(returnstring, loop_node, value)){
                    if(loop_node->first_node())
                        returnstring.append("<" + hulpLocal + ">" + parseNodeToString(loop_node->first_node()) + "</" + hulpLocal + ">");
                    else{
                        if(hulpLocal == "")
                            returnstring.append(value);
                        else
                            returnstring.append("<" + hulpLocal + ">" + value + "</" + hulpLocal + ">");
                    }
                }

                //if(loop_node->first_node()){
                //    returnstring.append("<" + hulpLocal + ">" + parseNodeToString(loop_node->first_node()) + "</" + hulpLocal + ">" );
                //}
                //if( !attributeCheck(returnstring, loop_node, value))
                //    returnstring.append("<" + hulpLocal + ">" + value + "</" + hulpLocal + ">");
                
                //if(loop_node->first_node()){
                    //cout << "node output" << loop_node->first_node()->value() << endl;
                //    returnstring.append(parseNodeToString(loop_node->first_node()));
                //}
                //if (hulp == hulpLocal){ //pushed niet value, maar opentag + value + sluittag
                //returnstring.append("<" + hulpLocal + ">" + value + "</" + hulpLocal + ">");
                
            }

            return returnstring;
        }

        // function used to fix problems with qualities
        void checkValueAndFix(std::string & value, xml_node<> * loop_node){
            const char *s = loop_node->name();
            std::string str(s);
            if(str == "oml:value"){
                std::cout << "helpX" << value << std::endl;
                value = "-1";
                std::cout << "helpX" << value << std::endl;
            }
        }

        int parser(std::string input, std::string parseTo){
            xml_document<> doc;
            xml_node<> * root_node;
            // Read the xml file into a vector

            //ifstream theFile(filename);
            //vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
            //buffer.push_back('\0');
            // Parse the buffer using the xml file parsing library into doc 
            //doc.parse<0>(&buffer[0]);
            // Find our root node
            char* copystr = new char[input.size() + 1];  // Create char buffer to store string copy
            strcpy (copystr, input.c_str());
            if(printer)
                std::cout << "help1" << endl;
            doc.parse<0>(&copystr[0]);
            const char *cstr = parseTo.c_str();
            root_node = doc.first_node(cstr);
            int id;
            string name;
            if (root_node){
                string hulp ="";
                string hulpLocal ="";
                string attribute = "";
                list<string>* lptr = nullptr;
                if(printer)
                    std::cout << "help2" << endl;
                bool started = true;
                for (xml_node<> * loop_node = root_node->first_node(); loop_node; loop_node = loop_node->next_sibling()){
                    if(printer)
                        std::cout << "help2a" << endl;
                    hulpLocal = loop_node->name();//TODO camelcase of underscores, kies er 1
                    //cout << "parseroutput:" << loop_node->value() << endl;
                    //TODO hier ongeveer plaatsen en verwerken:
                    //for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute()){

                    //}
                    //TODO TODO TODO TODO TODO TODO TODO TODO
                    std::string value = loop_node->value();
                    if(value == ""){
                        checkValueAndFix(value, loop_node);
                    }
                    if(printer)
                        std::cout << "help2b" << value << endl;

                    if(printer)
                        std::cout << "help3" << endl;
                    if(loop_node->first_node() != 0){
                        if(loop_node->first_node()->first_node() != 0){
                            value = parseNodeToString(loop_node->first_node());
                            //std::cout << "value: " << value << endl;
                        }
                    }
                    if( attributeCheck(attribute, loop_node, value)){

                        std::cout << "help2c" << endl;
                        if (hulp == hulpLocal){ //pushed niet value, maar opentag + value + sluittag
                            if (value != "")
                                lptr->push_back(attribute);
                        }
                        else{
                            if(started){
                                started = false;
                            }
                            else{
                                paramList.insert({hulp, (*lptr)}) ;
                            }
                            hulp = hulpLocal;
                            lptr = new list<string>;
                            if (value != "")
                                (*lptr).push_back(attribute);
                        }
                        attribute = "";
                    }
                    else{
                        if (hulp == hulpLocal){ //pushed niet value, maar opentag + value + sluittag
                            if (value != "")
                                lptr->push_back("<" + hulpLocal + ">" + value + "</" + hulpLocal + ">");
                            //std::cout << "help3a" << endl;
                        }
                        else{
                            if(started){
                                started = false;
                            }
                            else{
                                paramList.insert({hulp, (*lptr)}) ;
                            }
                            if(printer)
                                std::cout << "help4" << endl;
                            hulp = hulpLocal;
                            lptr = new list<string>;
                            if(printer)
                                std::cout << "help5" << endl;
                            if (value != "")
                                (*lptr).push_back("<" + hulpLocal + ">" + value + "</" + hulpLocal + ">");
                            else{
                                (*lptr).push_back("<" + hulpLocal + "> </" + hulpLocal + ">");
                            }
                            
                            if(printer)
                                std::cout << "help6" << endl;
                        }
                    }
                }

                
                if(hulp != "" && lptr && (*lptr).size() != 0)
                    paramList.insert({hulp, (*lptr)});
            }
            else{
                cout << "Error: parser failed, root of xml not found."; //TODO exception throwing
                return -1;
            }
            return 1;
        }

    
    public:

        std::unordered_map<string, list<string>> parseFromFile(std::string filename, std::string parseTo, int & err){
            //read file into buffer and make a string out of that
            ifstream theFile(filename);
            vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
            buffer.push_back('\0');
            std::string strC(buffer.begin(), buffer.end());
            err = parser(strC, parseTo);
            return paramList;
        }

        std::unordered_map<string, list<string>> parseFromString(std::string parseTo, std::string input, int & err){
            //std::cout << "begin string parsing" << endl;
            //printer = true;
            err = parser(input, parseTo);
            return paramList;
        }

        void clear(){
            paramList.clear();
        }

};