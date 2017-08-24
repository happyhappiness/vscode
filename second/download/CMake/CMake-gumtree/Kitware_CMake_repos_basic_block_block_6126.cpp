{
    conn->options = strdup(options);

    if(!conn->options)
      result = CURLE_OUT_OF_MEMORY;
  }