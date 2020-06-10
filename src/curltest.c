/*************************************************************************
    > File Name: src/curltest.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Thu 23 Apr 2020 08:01:48 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<curl/curl.h>

int main(int argc, char **argv)
{
	CURL *curl = curl_easy_init();

	if(curl)
	{
		CURLcode res;
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
}
