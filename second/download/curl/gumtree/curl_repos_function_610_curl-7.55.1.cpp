static CURLcode unit_setup(void)
{
  easy = curl_easy_init();
  return easy ? CURLE_OK : CURLE_OUT_OF_MEMORY;
}