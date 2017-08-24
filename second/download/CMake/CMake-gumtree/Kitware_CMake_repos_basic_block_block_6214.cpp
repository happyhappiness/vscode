f(prot_missing) {
    /* We're guessing prefixes here and if we're told to use a proxy or if
       we're gonna follow a Location: later or... then we need the protocol
       part added so that we have a valid URL. */
    char *reurl;
    char *ch_lower;

    reurl = aprintf("%s://%s", conn->handler->scheme, data->change.url);

    if(!reurl) {
      result = CURLE_OUT_OF_MEMORY;
      goto out;
    }

    /* Change protocol prefix to lower-case */
    for(ch_lower = reurl; *ch_lower != ':'; ch_lower++)
      *ch_lower = (char)TOLOWER(*ch_lower);

    if(data->change.url_alloc) {
      Curl_safefree(data->change.url);
      data->change.url_alloc = FALSE;
    }

    data->change.url = reurl;
    data->change.url_alloc = TRUE; /* free this later */
  }