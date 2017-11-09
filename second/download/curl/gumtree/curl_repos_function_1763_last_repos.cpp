int Curl_mk_dnscache(struct curl_hash *hash)
{
  return Curl_hash_init(hash, 7, Curl_hash_str, Curl_str_key_compare,
                        freednsentry);
}