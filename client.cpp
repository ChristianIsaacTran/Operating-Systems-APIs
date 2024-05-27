#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std; //library call to not have to call std::


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void init_put(int input_int) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
	    struct curl_slist *headers = NULL;
        // Set the request data to the integer value 1024
        //std::string data = "1024"; //sending the integer 3360 to /initialize via PUT
        std::string data = std::to_string(input_int); //sending the integer 3360 to /initialize via PUT

	    headers = curl_slist_append(headers, "Content-Type: application/json");

        //Reference fields by name
	    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/initialize");  //if working with modify, change /initialize to /modify
	    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT"); //tells what kind of command this is
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str()); //tells what data that we want to send to the api

        // Perform the PUT request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) { //Test for error. It shouldn't return an error since its all local host.
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup the curl handle
        curl_easy_cleanup(curl);
    } //Note: calls both curl_easy_cleanup and curl_global_cleanup to "clean" it from memory so that we can immediately use it again.
    curl_global_cleanup();
}
 

int init_get() {  
 
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // Create a new curl handle for the GET request
    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/initialize");
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); //Overrides the writefuntion to use the writecallback function above

        // Create a string buffer to hold the response data
        std::string buffer;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	
        // Perform the GET request
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup the curl handle
        curl_easy_cleanup(curl);

        // Print the response body
        std::cout << "\nResponse body: " << buffer << std::endl; //"buffer" is the data that was "get"

        //added return for int storage 
        return stoi(buffer);
        
    }

    // Cleanup libcurl
    curl_global_cleanup();
}

void modi_put(int input_int) {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
	    struct curl_slist *headers = NULL;
        // Set the request data to the integer value 1024
        //std::string data = "1024"; //sending the integer 3360 to /initialize via PUT
        std::string data = std::to_string(input_int); //sending the integer 3360 to /initialize via PUT

	    headers = curl_slist_append(headers, "Content-Type: application/json");

        //Reference fields by name
	    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/modify");  //if working with modify, change /initialize to /modify
	    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT"); //tells what kind of command this is
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str()); //tells what data that we want to send to the api

        // Perform the PUT request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) { //Test for error. It shouldn't return an error since its all local host.
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup the curl handle
        curl_easy_cleanup(curl);
    } //Note: calls both curl_easy_cleanup and curl_global_cleanup to "clean" it from memory so that we can immediately use it again.
    curl_global_cleanup();
}
 

int modi_get() {  
 
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    // Create a new curl handle for the GET request
    // Create a curl handle
    CURL* curl = curl_easy_init();
    if (curl) {
        // Set the URL for the GET request
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:5000/modify");
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); //Overrides the writefuntion to use the writecallback function above

        // Create a string buffer to hold the response data
        std::string buffer;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	
        // Perform the GET request
        CURLcode res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup the curl handle
        curl_easy_cleanup(curl);

        // Print the response body
        std::cout << "\nResponse body: " << buffer << std::endl; //"buffer" is the data that was "get"
        
        //added return for int storage 
        return stoi(buffer);

    }

    // Cleanup libcurl
    curl_global_cleanup();
}




int main() {
    //Note: the output file should have 6 lines, 2 lines for name and r number, then 4 lines for the times I called the "get" function (4 integers)
    //Print out name to standard output (stdout) on its own line
    cout << "Christian Tran\n";

    //Print out your R# to standard out (stdout) on its own line
    cout << "R11641653\n";

    //Send the integer 3360 to /initialize via PUT 
    init_put(3360); //put is "set". Giving you information.

    //Send the integer 4 to /modify via PUT
    modi_put(4);

    //retrieve the data in /initialize via GET command and store the value as an integer
    int init_data1 = init_get(); //get of course, is retrieving information back.
    //print value to stdout
    cout << init_data1 << std::endl;

    //retrieve the data in /modify via GET command and store the value as an integer
    int modi_data1 = modi_get(); 
    //print value to stdout
    cout << modi_data1 << std::endl;

    //Send the value received from /modify from (step#6) to /initialize via PUT
    init_put(modi_data1);

    //Send the value received from /initialize from (step#5) to /modify via PUT
    modi_put(init_data1);

    //Retrieve the data in /initialize via a GET command and store value as an integer
    int init_data2 = init_get();
    //print value to stdout
    cout << init_data2 << std::endl;

    //Retrieve the data in /modify via a GET comman and store the value as an integer
    int modi_data2 = modi_get();
    //print value to stdout
    cout << modi_data2 << std::endl;

    return 0;
}
