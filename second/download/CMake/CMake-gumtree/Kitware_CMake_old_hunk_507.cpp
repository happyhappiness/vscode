  idna_init();
#endif

  if(Curl_resolver_global_init() != CURLE_OK) {
    DEBUGF(fprintf(stderr, "Error: resolver_global_init failed\n"));
    return CURLE_FAILED_INIT;
  }
