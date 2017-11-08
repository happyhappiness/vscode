static CURLcode unit_setup(void)
{
  easy = curl_easy_init();
  return CURLE_OK;
}