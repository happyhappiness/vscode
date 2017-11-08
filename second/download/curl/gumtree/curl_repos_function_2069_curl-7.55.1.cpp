CURLcode Curl_pp_disconnect(struct pingpong *pp)
{
  free(pp->cache);
  pp->cache = NULL;
  return CURLE_OK;
}