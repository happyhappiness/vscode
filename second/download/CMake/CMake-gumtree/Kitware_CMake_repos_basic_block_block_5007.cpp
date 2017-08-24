{
    void *twentybytes = ((libthreaddata_t *) data)->twentybytes;

    free(twentybytes);
    free(data);
  }