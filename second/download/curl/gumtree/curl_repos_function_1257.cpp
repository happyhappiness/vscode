struct conncache *Curl_conncache_init(int size)
{
  struct conncache *connc;

  connc = calloc(1, sizeof(struct conncache));
  if(!connc)
    return NULL;

  connc->hash = Curl_hash_alloc(size, Curl_hash_str,
                                Curl_str_key_compare, free_bundle_hash_entry);

  if(!connc->hash) {
    free(connc);
    return NULL;
  }

  return connc;
}