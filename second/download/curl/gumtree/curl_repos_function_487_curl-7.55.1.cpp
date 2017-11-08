static size_t write_callback(void *ptr, size_t size, size_t nmemb,
                             void *stream)
{
  int amount = curlx_uztosi(size * nmemb);
  printf("%.*s", amount, (char *)ptr);
  (void)stream;
  return size * nmemb;
}