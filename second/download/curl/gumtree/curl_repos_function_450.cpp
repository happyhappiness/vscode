CURLM *curl_multi_init(void)
{
  struct Curl_multi *multi;

  multi = (void *)malloc(sizeof(struct Curl_multi));

  if(multi) {
    memset(multi, 0, sizeof(struct Curl_multi));
    multi->type = CURL_MULTI_HANDLE;
  }
  else
    return NULL;

  multi->hostcache = Curl_mk_dnscache();
  if(!multi->hostcache) {
    /* failure, free mem and bail out */
    free(multi);
    multi = NULL;
  }
  return (CURLM *) multi;
}