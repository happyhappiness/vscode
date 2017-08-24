{
  if(!wc)
    return;

  if(wc->tmp_dtor) {
    wc->tmp_dtor(wc->tmp);
    wc->tmp_dtor = ZERO_NULL;
    wc->tmp = NULL;
  }
  DEBUGASSERT(wc->tmp == NULL);

  Curl_llist_destroy(&wc->filelist, NULL);


  free(wc->path);
  wc->path = NULL;
  free(wc->pattern);
  wc->pattern = NULL;

  wc->customptr = NULL;
  wc->state = CURLWC_INIT;
}