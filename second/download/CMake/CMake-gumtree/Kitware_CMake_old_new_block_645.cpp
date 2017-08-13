{
      Curl_safefree(*allocuserpwd);
      *allocuserpwd = aprintf("%sAuthorization: NTLM %s\r\n",
                              proxy ? "Proxy-" : "",
                              base64);
      free(base64);
      if(!*allocuserpwd)
        return CURLE_OUT_OF_MEMORY;
      DEBUG_OUT(fprintf(stderr, "**** Header %s\n ", *allocuserpwd));
    }