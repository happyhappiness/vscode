  curl_off_t size = (curl_off_t)(sz * nmemb); /* typecast to prevent
                                                 warnings when converting from
                                                 unsigned to signed */
  if(out && !out->stream) {
    /* open file for writing */
    out->stream=fopen(out->filename, "wb");
    if(!out->stream)
      return -1; /* failure */
  }

  if(config->recvpersecond) {
    /*
     * We know when we received data the previous time. We know how much data
     * we get now. Make sure that this is not faster than we are told to run.
