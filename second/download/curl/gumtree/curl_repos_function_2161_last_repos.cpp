CURLcode Curl_wildcard_init(struct WildcardData *wc)
{
  Curl_llist_init(&wc->filelist, Curl_fileinfo_dtor);
  wc->state = CURLWC_INIT;

  return CURLE_OK;
}