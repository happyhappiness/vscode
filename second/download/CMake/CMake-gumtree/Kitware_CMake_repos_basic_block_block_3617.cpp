{
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1);

    /* Using proxy */
    if ( proxy_type > 0 )
      {
      curl_easy_setopt(curl, CURLOPT_PROXY, proxy); 
      switch (proxy_type)
        {
        case 2:
          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
          break;
        case 3:
          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
          break;
        default:
          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);           
        }
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

    /* always cleanup */
    curl_easy_cleanup(curl);
    }