CURLcode Curl_pp_disconnect(struct pingpong *pp)
{
  if(pp->cache) {
    free(pp->cache);
    pp->cache = NULL;
  }
  return CURLE_OK;
}