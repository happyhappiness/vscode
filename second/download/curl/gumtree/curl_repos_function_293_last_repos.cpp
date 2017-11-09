static size_t getcontentlengthfunc(void *ptr, size_t size, size_t nmemb,
                                   void *stream)
{
  int r;
  long len = 0;

  r = sscanf(ptr, "Content-Length: %ld\n", &len);
  if(r)
    *((long *) stream) = len;

  return size * nmemb;
}