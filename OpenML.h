//OpenML.h
//Thomas Wink


#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <curl/curl.h>
#include "src/XMLParser.h"
#include "src/HttpConnection.h"
#include "src/Tagged.h"
#include "src/File.h"
#include "xml/DatasetDescription.h"
#include "xml/QualitiesList.h"
#include "xml/DatasetList.h"
#include "xml/FlowList.h"
#include "xml/TaskList.h"
#include "xml/EvaluationList.h"
#include "xml/RunList.h"
#include "xml/Dataupload.h"

 
//using namespace rapidxml;
using namespace std;


const string OPENML_URL = "https://www.openml.org";
const string TEST = "https://test.openml.org";
const string API = "/api/v1";

class OpenML
{
    private:

	public:

		OpenML(){

		};

		Dataupload uploadDataset(std::string dataset, std::string description, std::string format, std::string userkey){
			//https://test.openml.org/api/v1/json/data?api_key=e741744ea8874e0393fd3494f067a405

			string url = OPENML_URL + API + "/data?api_key=" + userkey;
			//File f = File("upload.xml");
			//f.makeDataset(dataset, description, format);
			HttpConnection Httpcon;
			//url = "http://localhost:8000/";
			Httpcon.uploadDataset(url.c_str(), "upload.xml", dataset, "output.txt"); //TODO errors afvangen
			XMLParser Xmlpars;
			int err;
			std::unordered_map<string, list<string>> params = Xmlpars.parseFromFile("output.txt", "oml:upload_data_set", err);
			//if( remove( "output.txt" ) != 0 )
			//	perror( "Error deleting file" );
			Dataupload d;
			if (err>0)
				d = Dataupload(params);
			else
				d = Dataupload();
			return d;
		}

		RunList getRunList(std::list<string> filter, std::list<string> value){
			
			if(filter.size() != value.size() || filter.empty()){
				//TODO exception thrown, invalid argument
				return RunList();
			}
			std::string url = OPENML_URL + API + "/run/list";
			while(!filter.empty()){
				url = url + "/" + filter.front() + "/" + value.front();
				filter.pop_front();
				value.pop_front();
			}
			std::string filename = "runList.xml";
			HttpConnection Httpcon;
			Httpcon.downloadToFile(url.c_str(), filename);
			XMLParser Xmlpars;
			int err;
			std::unordered_map<string, list<string>> params = Xmlpars.parseFromFile(filename, "oml:runs", err);
			RunList r;
			if (err>0)
				r = RunList(params);
			else
				r = RunList();
			return r;
		};


		EvaluationList getEvaluationList(std::list<string> filter, std::list<string> value){
			
			if(filter.size() != value.size() || filter.empty()){
				//TODO exception thrown, invalid argument
				return EvaluationList();
			}
			std::string url = OPENML_URL + API + "/evaluation/list";
			while(!filter.empty()){
				url = url + "/" + filter.front() + "/" + value.front();
				filter.pop_front();
				value.pop_front();
			}
			std::string filename = "evaluationList.xml";
			HttpConnection Httpcon;
			Httpcon.downloadToFile(url.c_str(), filename);
			XMLParser Xmlpars;
			int err;
			std::unordered_map<string, list<string>> params = Xmlpars.parseFromFile(filename, "oml:evaluations", err);
			EvaluationList e;
			if (err>0)
				e = EvaluationList(params);
			else
				e = EvaluationList();
			return e;
		};


		TaskList getTaskList(std::list<string> filter, std::list<string> value){
			
			if(filter.size() != value.size() || filter.empty()){
				//TODO exception thrown, invalid argument
				return TaskList();
			}
			std::string url = OPENML_URL + API + "/task/list";
			while(!filter.empty()){
				url = url + "/" + filter.front() + "/" + value.front();
				filter.pop_front();
				value.pop_front();
			}
			std::string filename = "downloaded.xml";
			HttpConnection Httpcon;
			Httpcon.downloadToFile(url.c_str(), filename);
			XMLParser Xmlpars;
			int err;
			std::unordered_map<string, list<string>> params = Xmlpars.parseFromFile(filename, "oml:tasks", err);
			TaskList t;
			if (err>0)
				t = TaskList(params);
			else
				t = TaskList();
			return t;
		};

		Task getTask(int tid){
			string sDID = to_string(tid);
			string url = OPENML_URL + API + "/task/inputs/" + sDID;
			string filename = "downloaded.xml";
			HttpConnection Httpcon;
			Httpcon.downloadToFile(url.c_str(), filename);
			//string filename = "taskdown.xml";
			XMLParser Xmlpars;
			int err;
			std::unordered_map<string, list<string>> params = Xmlpars.parseFromFile(filename, "oml:task_inputs", err);
			Task t;
			if (err>0)
				t = Task(params);
			else
				t = Task();
			return t;
		};

		FlowList getFlowList(std::list<string> filter, std::list<string> value){
			
			if(filter.size() != value.size() || filter.empty()){
				//TODO exception thrown, invalid argument
				return FlowList();
			}
			std::string url = OPENML_URL + API + "/flow/list";
			while(!filter.empty()){
				url = url + "/" + filter.front() + "/" + value.front();
				filter.pop_front();
				value.pop_front();
			}
			std::string filename = "downloaded.xml";
			HttpConnection Httpcon;
			Httpcon.downloadToFile(url.c_str(), filename);
			
			XMLParser Xmlpars;
			int err;
			//std::string filename = "flowlistdown.xml"; 
			std::unordered_map<string, list<string>> params = Xmlpars.parseFromFile(filename, "oml:flows", err);
			FlowList f;
			if(err>0)
				f = FlowList(params);
			else
				f = FlowList();
			return f;

		};

		Flow getFlow(int fid){
			string sFID = to_string(fid);
			string url = OPENML_URL + API + "/flow/" + sFID;
			string filename = "flowlistdown.xml";
			HttpConnection Httpcon;
			Httpcon.downloadToFile(url.c_str(), filename);
			XMLParser Xmlpars;
			int err;
			std::unordered_map<string, list<string>> params = Xmlpars.parseFromFile(filename, "oml:flow", err);
			Flow f;
			if (err>0)
				f = Flow(params);
			else
				f = Flow();
			return f;
		};

		DatasetList getDatasetList(std::list<string> filter, std::list<string> value){
			if(filter.size() != value.size() || filter.empty()){
				//TODO exception thrown, invalid argument
				return DatasetList();
			}
			std::string url = OPENML_URL + API + "/data/list";
			while(!filter.empty()){
				url = url + "/" + filter.front() + "/" + value.front();
				filter.pop_front();
				value.pop_front();
			}
			std::string filename = "downloaded.xml";
			HttpConnection Httpcon;
			Httpcon.downloadToFile(url.c_str(), filename);
			XMLParser Xmlpars;
			int err;
			//std::string filename = "datasetdown.xml"; 
			std::unordered_map<string, list<string>> params = Xmlpars.parseFromFile(filename, "oml:data", err);
			DatasetList d;
			if(err>0)
				d = DatasetList(params);
			else
				d = DatasetList();
			return d;

		};

		QualitiesList getQualitiesList(int did){
			string sDID = to_string(did);
			string url = OPENML_URL + API + "/data/qualities/" + sDID;
			string filename = "downloaded.xml";
			HttpConnection Httpcon;
			Httpcon.downloadToFile(url.c_str(), filename);
			//string filename = "qualitylistdown.xml";
			XMLParser Xmlpars;
			int err;
			std::unordered_map<string, list<string>> params = Xmlpars.parseFromFile(filename, "oml:data_qualities", err);
			QualitiesList q;
			if (err>0)
				q = QualitiesList(params);
			else
				q = QualitiesList();
			return q;
		};

		DatasetDescription getDatasetDescription (int did){
			string sDID = to_string(did);
			string url = OPENML_URL + API + "/data/" + sDID;
			string filename = "downloaded.xml";
			HttpConnection Httpcon;
			Httpcon.downloadToFile(url.c_str(), filename);
			XMLParser Xmlpars;
			int err;
			std::unordered_map<string, list<string>> params = Xmlpars.parseFromFile(filename, "oml:data_set_description", err);
			DatasetDescription d;
			if (err>0)
				d = DatasetDescription(params);
			else
				d = DatasetDescription();
			return d;
		};
};