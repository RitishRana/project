/*
*	Name	    :	Ritish
*	Assignment  :	Connecting to Redis Server. If the input cities are present in the Redis Cache Server, then get the data from it
*			else get the data from the api of travelyaari for the input cities and then add the data to redis for future.
*	Date	    :	13-June-2015
*/

#include <iostream>
#include <string>
#include<fstream>
#include <curl/curl.h>
#include <algorithm>
#include "../include/hiredis.h"
using namespace std;

string readBuffer;     // Contain the result of api

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)		// helping the curl 
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int Getting_data_travelyaari(string from_city,string to_city,string date)
{
    CURL *curl;
    CURLcode res;
    string url;
    url="http://www.travelyaari.com//api/search/?mode=oneway&hop=direct&fromCity="+from_city+"&toCity="+to_city+"&departDate="+date;
    //cout<<"Getting Data from url"<<endl;
    curl = curl_easy_init();
    if(curl) {
    	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);		// read the page of url and store the data to string readBuffer 
    	res = curl_easy_perform(curl);
    	curl_easy_cleanup(curl);
	// cout << readBuffer << endl;
     }
}

/*
	Function for searching the redis server: whether input cities are present or not
*/
int Search_Redis(string key,redisReply *reply,redisContext *c)
{
    reply = (redisReply*)redisCommand(c,"GET %s", key.c_str());	 	// get data from redis server 	
    if(reply->type!=REDIS_REPLY_NIL)
        {
	    cout<<reply->str<<endl;
	    //cout<<"Found the required cities in Redis Cache Server"<<endl;
	    return 1;
	}
    //cout<<"Not Found the required cities in Redis Cache Server"<<endl;
    freeReplyObject(reply);
    return 0;

}

int feed_redis(redisReply *reply,redisContext *c,string key)
{
    //cout<<"Feeding Data to Redis ...."<<endl;
    reply = (redisReply*)redisCommand(c,"SET %s %s", key.c_str(),readBuffer.c_str()); // add data to redis server 
    if(reply->type!=REDIS_REPLY_ERROR)
        {
	    //cout<<"Successfully Added Data to Redis.... :D"<<endl;
	    return 1;
	}
    //cout<<"Unable to Add Data to Redis .... :("<<endl;
    freeReplyObject(reply);
    return 0;
}
int main(int argc, char* argv[])
{
  
	redisReply *reply;
 	redisContext *c = redisConnect("127.0.0.1", 6379);//connect to redis server localhost
	if (c->err) {
        	//printf("Error: %s\n", c->errstr);
		return 0;
    	}else{
        	//printf("Connected Successfully ! \n");
    	}
	if (argc!=4){
	    //cout<<"Please specify from city:to city:date(DD-MM-YYYY) as command line argument !!"<<endl;
	    return 0;
	}
	string city1=argv[1];
	transform(city1.begin(), city1.end(), city1.begin(), ::tolower);
	string city2=argv[2];
	transform(city2.begin(), city2.end(), city2.begin(), ::tolower);
	string date=argv[3];
	string key=city1+"_"+city2;
	if(Search_Redis(key.c_str(),reply,c))		// if data present in redis server print the data and return
	    return 0;
	Getting_data_travelyaari(city1,city2,date);     // get the data from api
	if(feed_redis(reply,c,key))
	    Search_Redis(key.c_str(),reply,c);
  return 0;
}


