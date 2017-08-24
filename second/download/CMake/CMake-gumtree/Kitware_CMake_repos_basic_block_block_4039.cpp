f(ai) {
      struct Curl_easy *data = conn->data;

      if(data->share)
        Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

      dns = Curl_cache_addr(data, ai,
                            conn->async.hostname,
                            conn->async.port);
      if(!dns) {
        /* failed to store, cleanup and return error */
        Curl_freeaddrinfo(ai);
        result = CURLE_OUT_OF_MEMORY;
      }

      if(data->share)
        Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
    }
    else {
      result = CURLE_OUT_OF_MEMORY;
    }