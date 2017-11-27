static int cj_cb_start (void *ctx)
{
  cj_t *db = (cj_t *)ctx;
  if (++db->depth >= YAJL_MAX_DEPTH)
  {
    ERROR ("curl_json plugin: %s depth exceeds max, aborting.", db->url);
    return 0;
  }
  return 1;
}