{
    struct ResolverResults *res = (struct ResolverResults *)async->os_specific;
    if(res) {
      if(res->temp_ai) {
        Curl_freeaddrinfo(res->temp_ai);
        res->temp_ai = NULL;
      }
      free(res);
    }
    async->os_specific = NULL;
  }