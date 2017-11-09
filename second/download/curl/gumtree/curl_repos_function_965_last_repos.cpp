CURLcode easysrc_init(void)
{
  CHKRET(easysrc_add(&easysrc_code,
                     "hnd = curl_easy_init();"));
  return CURLE_OK;
}