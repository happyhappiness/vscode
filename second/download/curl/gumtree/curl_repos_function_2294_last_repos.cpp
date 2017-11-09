int DisposeLibraryData(void *data)
{
  if(data) {
    void *tenbytes = ((libdata_t *) data)->tenbytes;

    free(tenbytes);
    free(data);
  }

  return 0;
}