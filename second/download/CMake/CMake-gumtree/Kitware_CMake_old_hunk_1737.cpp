    res = curl_easy_perform(curl);
    if ( res != 0 )
      {
      printf("Error fetching: http://www.cmake.org/\n");
      retVal = 1;
      }

