f(res->temp_ai) {
        Curl_freeaddrinfo(res->temp_ai);
        res->temp_ai = NULL;
      }