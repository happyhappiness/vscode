static CURLcode unit_setup( void )
{
  data = curl_easy_init();
  if(!data)
    return CURLE_OUT_OF_MEMORY;
  return CURLE_OK;
}