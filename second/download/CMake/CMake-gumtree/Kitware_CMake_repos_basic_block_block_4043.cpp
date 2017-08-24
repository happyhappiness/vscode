{
    rc = Curl_hash_init(&hostname_cache, 7, Curl_hash_str,
                        Curl_str_key_compare, freednsentry);
    if(!rc)
      host_cache_initialized = 1;
  }