void Curl_conncache_remove_conn(struct conncache *connc,
                                struct connectdata *conn)
{
  struct connectbundle *bundle = conn->bundle;

  /* The bundle pointer can be NULL, since this function can be called
     due to a failed connection attempt, before being added to a bundle */
  if(bundle) {
    Curl_bundle_remove_conn(bundle, conn);
    if(bundle->num_connections == 0) {
      conncache_remove_bundle(connc, bundle);
    }

    if(connc) {
      connc->num_connections--;

      DEBUGF(infof(conn->data, "The cache now contains %"
                   CURL_FORMAT_CURL_OFF_TU " members\n",
                   (curl_off_t) connc->num_connections));
    }
  }
}