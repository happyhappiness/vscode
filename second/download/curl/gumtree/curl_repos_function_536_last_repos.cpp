static size_t header_callback(void *ptr, size_t size, size_t nmemb,
                              void *userp)
{
  size_t len = size * nmemb;
  (void)userp;
  (void)fwrite(ptr, size, nmemb, stdout);
  return len;
}