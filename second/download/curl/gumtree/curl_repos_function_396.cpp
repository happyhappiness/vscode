static int debug_callback(CURL *curl, curl_infotype info, char *msg, size_t len, void *ptr)
{
  (void)curl;
  (void)ptr;

  if(info == CURLINFO_TEXT)
    fprintf(stderr, "debug: %.*s", (int) len, msg);

  return 0;
}