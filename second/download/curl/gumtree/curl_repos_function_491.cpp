void Curl_resolv_unlock(struct SessionHandle *data, struct Curl_dns_entry *dns)
{
  curlassert(dns && (dns->inuse>0));

  if(data->share)
    Curl_share_lock(data, CURL_LOCK_DATA_DNS, CURL_LOCK_ACCESS_SINGLE);

  dns->inuse--;

  if(data->share)
    Curl_share_unlock(data, CURL_LOCK_DATA_DNS);
}