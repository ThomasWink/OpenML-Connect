//HttpConnection.h
//Thomas Wink

#pragma once
#include <iostream>
#include <string.h>
#include <array>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <curl/curl.h>

using namespace std;

int writer(char *data, size_t size, size_t nmemb, string *buffer){
	int result = 0;
	if(buffer != NULL) {
		buffer -> append(data, size * nmemb);
		result = size * nmemb;
	}
	return result;
}

/// <summary> Class tries to connect to server. Upon succes, a file is downloaded and stored in the current executive directory. </summary>
class HttpConnection {
    private:


    public:

    HttpConnection(){
        
    }


    void uploadDataset(const char * url, std::string description, std::string dataset, std::string output){
        
        CURL *curl;
        CURLcode res;
        std::string buffer;

        curl_mime *form = NULL;
        curl_mimepart *field = NULL;
        struct curl_slist *headerlist = NULL;
        static const char buf[] = "Expect:";

        curl_global_init(CURL_GLOBAL_ALL);

        curl = curl_easy_init();
        if(curl) {
            /* Create the form */ 
            form = curl_mime_init(curl);

            /* Fill in the file upload field */ 
            field = curl_mime_addpart(form);
            curl_mime_name(field, "description");
            curl_mime_filedata(field, description.c_str());

            /* Fill in the filename field */ 
            field = curl_mime_addpart(form);
            curl_mime_name(field, "dataset");
            curl_mime_filedata(field, dataset.c_str());
    
            /* initialize custom header list (stating that Expect: 100-continue is not
               wanted */ 
            headerlist = curl_slist_append(headerlist, buf);
            /* what URL that receives this POST */ 
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false); //TODO test if this is needed or not (ignores certificates)
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);

            // Hide perform output
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);	/* Function Pointer "writer" manages the required buffer size */
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer );
            /* Perform the request, res will get the return code */ 
            res = curl_easy_perform(curl);
            
            /* Check for errors */ 
            if(res == CURLE_OK){
                std::ofstream out(output);
                out << buffer;
                out.close();
            }else 
              fprintf(stderr, "curl_easy_perform() failed: %s\n",
                      curl_easy_strerror(res));

            /* always cleanup */ 
            curl_easy_cleanup(curl);
 
            /* then cleanup the form */ 
            curl_mime_free(form);
            /* free slist */ 
            curl_slist_free_all(headerlist);
        }    
    } //uploadDataset

    void downloadToFile(const char * url, std::string filename){

        CURL *curl;
        CURLcode res;
        string buffer;
        /* In windows, this will init the winsock stuff */ 
        curl_global_init(CURL_GLOBAL_ALL);
        
        /* get a curl handle */ 
        curl = curl_easy_init();
        if(curl) {
            /* First set the URL that is about to receive our POST. This URL can
            just as well be a https:// URL if that is what should receive the
            data. */ 
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_HEADER, 0);	 /* No we don't need the Header of the web content. Set to 0 and curl ignores the first line */
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);	/* Function Pointer "writer" manages the required buffer size */
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer );
            /* Perform the request, res will get the return code */ 
            res = curl_easy_perform(curl);
            /* Check for errors */ 
            
            if(res == CURLE_OK){
                std::ofstream out(filename);
                out << buffer;
                out.close();
            }
            else{ //TODO exception throwing
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
            	    curl_easy_strerror(res));
            }
            curl_easy_cleanup(curl);
        }
		else{
      		fprintf(stderr, "curl_easy_perform() failed: %s\n",
            	curl_easy_strerror(res));
	
		}
	    curl_global_cleanup();

    }


};

