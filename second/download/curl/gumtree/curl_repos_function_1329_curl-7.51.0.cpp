CURLcode Curl_conncache_add_conn(struct conncache *connc,
                                 struct connectdata *conn)
{
  CURLcode result;
  struct connectbundle *bundle;
  struct connectbundle *new_bundle = NULL;
  struct Curl_easy *data = conn->data;

  bundle = Curl_conncache_find_bundle(conn, data->state.conn_cache);
  if(!bundle) {
    char *key;
    int rc;

    result = bundle_create(data, &new_bundle);
    if(result)
      return result;

    key = hashkey(conn);
    if(!key) {
      bundle_destroy(new_bundle);
      return CURLE_OUT_OF_MEMORY;
    }

    rc = conncache_add_bundle(data->state.conn_cache, key, new_bundle);
    free(key);
    if(!rc) {
      bundle_destroy(new_bundle);
      return CURLE_OUT_OF_MEMORY;
    }
    bundle = new_bundle;
  }

  result = bundle_add_conn(bundle, conn);
  if(result) {
    if(new_bundle)
      conncache_remove_bundle(data->state.conn_cache, new_bundle);
    return result;
  }

  conn->connection_id = connc->next_connection_id++;
  connc->num_connections++;

  DEBUGF(infof(conn->data, "Added connection %ld. "
               "The cache now contains %" CURL_FORMAT_CURL_OFF_TU " members\n",
               conn->connection_id, (curl_off_t) connc->num_connections));

  return CURLE_OK;
}