{
    ssize_t extra_len;

    if(len < 2)
      return GZIP_UNDERFLOW;

    extra_len = (data[1] << 8) | data[0];

    if(len < (extra_len+2))
      return GZIP_UNDERFLOW;

    len -= (extra_len + 2);
    data += (extra_len + 2);
  }