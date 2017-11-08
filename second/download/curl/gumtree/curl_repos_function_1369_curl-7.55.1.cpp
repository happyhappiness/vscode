struct connectbundle *Curl_conncache_find_bundle(struct connectdata *conn,
                                                 struct conncache *connc)
{
  struct connectbundle *bundle = NULL;
  if(connc) {
    char key[128];
    hashkey(conn, key, sizeof(key));
    bundle = Curl_hash_pick(&connc->hash, key, strlen(key));
  }

  return bundle;
}