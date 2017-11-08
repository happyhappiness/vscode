static size_t
write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  (void)contents;
  (void)userp;

  return realsize;
}