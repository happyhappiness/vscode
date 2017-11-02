CURLcode easysrc_cleanup(void)
{
  CHKRET(easysrc_add(&easysrc_code, "curl_easy_cleanup(hnd);"));
  CHKRET(easysrc_add(&easysrc_code, "hnd = NULL;"));

  return CURLE_OK;
}