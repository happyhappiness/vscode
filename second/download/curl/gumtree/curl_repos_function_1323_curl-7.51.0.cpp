int Curl_conncache_init(struct conncache *connc, int size)
{
  return Curl_hash_init(&connc->hash, size, Curl_hash_str,
                        Curl_str_key_compare, free_bundle_hash_entry);
}