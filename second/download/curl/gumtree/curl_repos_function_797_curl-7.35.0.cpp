CURLcode easysrc_add(struct curl_slist **plist, const char *line)
{
  CURLcode ret = CURLE_OK;
  struct curl_slist *list =
    curl_slist_append(*plist, line);
  if(!list) {
    easysrc_free();
    ret = CURLE_OUT_OF_MEMORY;
  }
  else
    *plist = list;
  return ret;
}