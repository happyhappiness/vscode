struct curl_hash *Curl_mk_dnscache(void)
{
  return Curl_hash_alloc(7, freednsentry);
}