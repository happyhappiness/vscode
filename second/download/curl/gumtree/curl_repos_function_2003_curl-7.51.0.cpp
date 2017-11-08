void Curl_wildcard_dtor(struct WildcardData *wc)
{
  if(!wc)
    return;

  if(wc->tmp_dtor) {
    wc->tmp_dtor(wc->tmp);
    wc->tmp_dtor = ZERO_NULL;
    wc->tmp = NULL;
  }
  DEBUGASSERT(wc->tmp == NULL);

  if(wc->filelist) {
    Curl_llist_destroy(wc->filelist, NULL);
    wc->filelist = NULL;
  }

  free(wc->path);
  wc->path = NULL;
  free(wc->pattern);
  wc->pattern = NULL;

  wc->customptr = NULL;
  wc->state = CURLWC_INIT;
}