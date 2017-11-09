static CURLcode unit_setup(void)
{
  int res = CURLE_OK;

  global_init(CURL_GLOBAL_ALL);
  easy = curl_easy_init();
  if(!easy)
    return CURLE_OUT_OF_MEMORY;
  return res;
}