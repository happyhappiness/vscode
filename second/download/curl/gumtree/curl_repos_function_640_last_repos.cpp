static CURLcode unit_setup(void)
{
  int rc;
  data = curl_easy_init();
  if(!data)
    return CURLE_OUT_OF_MEMORY;

  rc = Curl_mk_dnscache(&hp);
  if(rc) {
    curl_easy_cleanup(data);
    curl_global_cleanup();
    return CURLE_OUT_OF_MEMORY;
  }
  return CURLE_OK;
}