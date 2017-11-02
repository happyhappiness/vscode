struct curl_hash *Curl_mk_dnscache(void)
{
  return Curl_hash_alloc(7, Curl_hash_str, Curl_str_key_compare, freednsentry);
}