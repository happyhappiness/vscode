static bool conncache_add_bundle(struct conncache *connc,
                                 char *key,
                                 struct connectbundle *bundle)
{
  void *p = Curl_hash_add(&connc->hash, key, strlen(key), bundle);

  return p?TRUE:FALSE;
}