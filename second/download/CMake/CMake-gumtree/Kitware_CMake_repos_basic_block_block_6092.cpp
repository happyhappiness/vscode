{
    obuf = malloc(olen + 1);
    if(!obuf) {
      free(pbuf);
      free(ubuf);
      result = CURLE_OUT_OF_MEMORY;
    }
  }