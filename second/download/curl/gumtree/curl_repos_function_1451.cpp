struct Curl_multi *Curl_multi_handle(int hashsize, /* socket hash */
                                     int chashsize) /* connection hash */
{
  struct Curl_multi *multi = calloc(1, sizeof(struct Curl_multi));

  if(!multi)
    return NULL;

  multi->type = CURL_MULTI_HANDLE;

  multi->hostcache = Curl_mk_dnscache();
  if(!multi->hostcache)
    goto error;

  multi->sockhash = sh_init(hashsize);
  if(!multi->sockhash)
    goto error;

  multi->conn_cache = Curl_conncache_init(chashsize);
  if(!multi->conn_cache)
    goto error;

  multi->msglist = Curl_llist_alloc(multi_freeamsg);
  if(!multi->msglist)
    goto error;

  multi->pending = Curl_llist_alloc(multi_freeamsg);
  if(!multi->pending)
    goto error;

  /* allocate a new easy handle to use when closing cached connections */
  multi->closure_handle = curl_easy_init();
  if(!multi->closure_handle)
    goto error;

  multi->closure_handle->multi = multi;
  multi->closure_handle->state.conn_cache = multi->conn_cache;

  multi->max_pipeline_length = 5;

  /* -1 means it not set by user, use the default value */
  multi->maxconnects = -1;
  return (CURLM *) multi;

  error:

  Curl_hash_destroy(multi->sockhash);
  multi->sockhash = NULL;
  Curl_hash_destroy(multi->hostcache);
  multi->hostcache = NULL;
  Curl_conncache_destroy(multi->conn_cache);
  multi->conn_cache = NULL;
  Curl_close(multi->closure_handle);
  multi->closure_handle = NULL;
  Curl_llist_destroy(multi->msglist, NULL);
  Curl_llist_destroy(multi->pending, NULL);

  free(multi);
  return NULL;
}