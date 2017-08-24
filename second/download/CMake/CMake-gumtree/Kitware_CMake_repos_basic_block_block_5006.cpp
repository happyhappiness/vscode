{
    void *tenbytes = ((libdata_t *) data)->tenbytes;

    free(tenbytes);
    free(data);
  }