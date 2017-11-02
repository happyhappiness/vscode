static int hostcache_inuse(void *data, void *hc)
{
  struct Curl_dns_entry *c = (struct Curl_dns_entry *) hc;

  if(c->inuse == 1)
    Curl_resolv_unlock(data, c);

  return 1; /* free all entries */
}