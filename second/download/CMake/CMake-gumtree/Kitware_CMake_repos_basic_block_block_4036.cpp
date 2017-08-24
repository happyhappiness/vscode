{
        /* failed to store, cleanup and return error */
        Curl_freeaddrinfo(ai);
        result = CURLE_OUT_OF_MEMORY;
      }