{
    free(proxy);  /* Don't bother with an empty proxy string or if the
                     protocol doesn't work with network */
    proxy = NULL;
  }