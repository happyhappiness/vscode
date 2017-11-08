static bool conncache_add_bundle(struct conncache *connc,
                                 char *hostname,
                                 struct connectbundle *bundle)
{
  void *p;

  p = Curl_hash_add(connc->hash, hostname, strlen(hostname)+1, bundle);

  return p?TRUE:FALSE;
}