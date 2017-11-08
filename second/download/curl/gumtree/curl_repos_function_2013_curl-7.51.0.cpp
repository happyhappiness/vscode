bool Curl_pp_moredata(struct pingpong *pp)
{
  return (!pp->sendleft && pp->cache && pp->nread_resp < pp->cache_size) ?
         TRUE : FALSE;
}