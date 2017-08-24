f(flags & COMMENT) {
    /* Skip over NUL-terminated comment */
    while(len && *data) {
      --len;
      ++data;
    }
    if(!len || *data)
      return GZIP_UNDERFLOW;

    /* Skip over the NUL */
    --len;
  }