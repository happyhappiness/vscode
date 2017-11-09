static CURLcode unit_setup(void)
{
  int res = CURLE_OK;

  global_init(CURL_GLOBAL_ALL);
  data = curl_easy_init();
  if(!data)
    return CURLE_OUT_OF_MEMORY;
  return res;
}