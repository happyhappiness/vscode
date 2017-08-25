f(!data->state.headerbuff) {
    DEBUGF(fprintf(stderr, "Error: malloc of headerbuff failed\n"));
    result = CURLE_OUT_OF_MEMORY;
  }
  else {
    result = Curl_init_userdefined(&data->set);

    data->state.headersize=HEADERSIZE;

    Curl_convert_init(data);

    Curl_initinfo(data);

    /* most recent connection is not yet defined */
    data->state.lastconnect = NULL;

    data->progress.flags |= PGRS_HIDE;
    data->state.current_speed = -1; /* init to negative == impossible */

    data->wildcard.state = CURLWC_INIT;
    data->wildcard.filelist = NULL;
    data->set.fnmatch = ZERO_NULL;
    data->set.maxconnects = DEFAULT_CONNCACHE_SIZE; /* for easy handles */

    Curl_http2_init_state(&data->state);
  }