    curl_easy_setopt(curl, CURLOPT_HEADER, 1);



    /* get the first document */

    curl_easy_setopt(curl, CURLOPT_URL, "http://www.cmake.org/");

    res = curl_easy_perform(curl);

    if ( res != 0 )

      {

      printf("Error fetching: http://www.cmake.org/\n");

      retVal = 1;

      }


