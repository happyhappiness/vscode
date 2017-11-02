CURLcode Curl_wildcard_init(struct WildcardData *wc)
{
  DEBUGASSERT(wc->filelist == NULL);
  /* now allocate only wc->filelist, everything else
     will be allocated if it is needed. */
  wc->filelist = Curl_llist_alloc(Curl_fileinfo_dtor);
  if(!wc->filelist) {;
    return CURLE_OUT_OF_MEMORY;
  }
  return CURLE_OK;
}