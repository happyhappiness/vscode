void Curl_resolv_unlock(struct SessionHandle *data, struct Curl_dns_entry *dns)
{
  DEBUGASSERT(dns && (dns->inuse>0));

  if(data && data->share)
    Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

  dns->inuse--;
  /* only free if nobody is using AND it is not in hostcache (timestamp ==
     0) */
  if(dns->inuse == 0 && dns->timestamp == 0) {
    Curl_freeaddrinfo(dns->addr);
    free(dns);
  }

  if(data && data->share)
    Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
}