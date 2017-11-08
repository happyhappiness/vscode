CURLcode Curl_conncache_add_conn(struct conncache *connc,
                                 struct connectdata *conn)
{
  CURLcode result;
  struct connectbundle *bundle;
  struct connectbundle *new_bundle = NULL;
  struct SessionHandle *data = conn->data;

  bundle = Curl_conncache_find_bundle(data->state.conn_cache,
                                      conn->host.name);
  if(!bundle) {
    result = Curl_bundle_create(data, &new_bundle);
    if(result != CURLE_OK)
      return result;

    if(!conncache_add_bundle(data->state.conn_cache,
                             conn->host.name, new_bundle)) {
      Curl_bundle_destroy(new_bundle);
      return CURLE_OUT_OF_MEMORY;
    }
    bundle = new_bundle;
  }

  result = Curl_bundle_add_conn(bundle, conn);
  if(result != CURLE_OK) {
    if(new_bundle)
      conncache_remove_bundle(data->state.conn_cache, new_bundle);
    return result;
  }

  connc->num_connections++;

  return CURLE_OK;
}