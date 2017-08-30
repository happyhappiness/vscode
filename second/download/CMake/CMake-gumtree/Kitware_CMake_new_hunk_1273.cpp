      }



    /* get the first document */

    curl_easy_setopt(curl, CURLOPT_URL, url1);

    res = curl_easy_perform(curl);

    if ( res != 0 )

      {

      printf("Error fetching: %s\n", url1);

      retVal = 1;

      }



    /* get another document from the same server using the same

       connection */

    /* avoid warnings about url2 since below block is commented out: */

    (void) url2;

    /*

      curl_easy_setopt(curl, CURLOPT_URL, url2);

      res = curl_easy_perform(curl);

      if ( res != 0 )

      {

      printf("Error fetching: %s\n", url2);

      retVal = 1;

      }

    */

