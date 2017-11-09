size_t WriteHeader(void *ptr, size_t size, size_t nmemb, void *stream)
{
  (void)ptr;
  (void)stream;

  realHeaderSize += curlx_uztoul(size * nmemb);

  return nmemb * size;
}