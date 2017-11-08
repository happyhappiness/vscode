size_t WriteHeader(void *ptr, size_t size, size_t nmemb, void *stream)
{
  (void)ptr;
  (void)stream;
  realHeaderSize += size * nmemb;

  return nmemb * size;
}