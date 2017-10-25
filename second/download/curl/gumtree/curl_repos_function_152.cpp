static CURLcode main_init(void)
{
  return curl_global_init(CURL_GLOBAL_DEFAULT);
}