CURLM *curl_multi_init(void)
{
  struct Curl_multi *multi = (void *)calloc(sizeof(struct Curl_multi), 1);

  if(!multi)
    return NULL;

  multi->type = CURL_MULTI_HANDLE;

  multi->hostcache = Curl_mk_dnscache();
  if(!multi->hostcache) {
    /* failure, free mem and bail out */
    free(multi);
    return NULL;
  }

  multi->sockhash = sh_init();
  if(!multi->sockhash) {
    /* failure, free mem and bail out */
    Curl_hash_destroy(multi->hostcache);
    free(multi);
    return NULL;
  }

  multi->connc = Curl_mk_connc(CONNCACHE_MULTI, -1);
  if(!multi->connc) {
    Curl_hash_destroy(multi->sockhash);
    Curl_hash_destroy(multi->hostcache);
    free(multi);
    return NULL;
  }

  /* Let's make the doubly-linked list a circular list.  This makes
     the linked list code simpler and allows inserting at the end
     with less work (we didn't keep a tail pointer before). */
  multi->easy.next = &multi->easy;
  multi->easy.prev = &multi->easy;

  return (CURLM *) multi;
}