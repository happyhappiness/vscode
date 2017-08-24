{
    /* Skip over NUL-terminated file name */
    while(len && *data) {
      --len;
      ++data;
    }
    if(!len || *data)
      return GZIP_UNDERFLOW;

    /* Skip over the NUL */
    --len;
    ++data;
  }