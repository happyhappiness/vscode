f(curl) 
    {
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);

    /* get the first document */
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.cmake.org/page1.html");
    res = curl_easy_perform(curl);
    if ( res != 0 )
      {
      printf("Error fetching: http://www.cmake.org/page1.html\n");
      retVal = 1;
      }


    /* get another document from the same server using the same
       connection */
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.cmake.org/page2.html");
    res = curl_easy_perform(curl);
    if ( res != 0 )
      {
      printf("Error fetching: http://www.cmake.org/page2.html\n");
      retVal = 1;
      }

    /* always cleanup */
    curl_easy_cleanup(curl);
    }
  else
    {
    printf("Cannot create curl object\n");
    retVal = 1;
    }