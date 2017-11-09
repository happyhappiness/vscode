static size_t discardfunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
  (void)ptr;
  (void)stream;
  return size * nmemb;
}