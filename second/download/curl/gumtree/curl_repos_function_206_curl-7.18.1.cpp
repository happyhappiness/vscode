static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
  printf("%.*s", (int)(size * nmemb), (char *)ptr);
  (void)stream;
  return size * nmemb;
}