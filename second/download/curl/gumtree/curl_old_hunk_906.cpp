  if(!config)
    return failure;

#ifdef DEBUGBUILD
  if(config->include_headers) {
    if(sz * nmemb > (size_t)CURL_MAX_HTTP_HEADER) {
      warnf(config, "Header data size exceeds single call write limit!\n");
      return failure;
    }
  }
  else {
    if(sz * nmemb > (size_t)CURL_MAX_WRITE_SIZE) {
      warnf(config, "Data size exceeds single call write limit!\n");
      return failure;
    }
  }

  {
    /* Some internal congruency checks on received OutStruct */
