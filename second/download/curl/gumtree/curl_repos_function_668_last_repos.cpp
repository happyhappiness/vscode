static CURLcode unit_setup(void)
{
  int res = CURLE_OK;

  global_init(CURL_GLOBAL_ALL);
  return res;
}