struct connectbundle *Curl_conncache_find_bundle(struct conncache *connc,
                                                 char *hostname)
{
  struct connectbundle *bundle = NULL;

  if(connc)
    bundle = Curl_hash_pick(connc->hash, hostname, strlen(hostname)+1);

  return bundle;
}