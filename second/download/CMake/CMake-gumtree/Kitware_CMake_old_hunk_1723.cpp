  int retVal = 0;

  CURL *curl;

  CURLcode res;

  curl = curl_easy_init();

  if(curl) 

    {

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

    curl_easy_setopt(curl, CURLOPT_HEADER, 1);



    /* get the first document */

    curl_easy_setopt(curl, CURLOPT_URL, "http://www.cmake.org/page1.html");

    res = curl_easy_perform(curl);

