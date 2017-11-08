CURLcode Curl_bundle_create(struct SessionHandle *data,
                            struct connectbundle **cb_ptr)
{
  (void)data;
  DEBUGASSERT(*cb_ptr == NULL);
  *cb_ptr = malloc(sizeof(struct connectbundle));
  if(!*cb_ptr)
    return CURLE_OUT_OF_MEMORY;

  (*cb_ptr)->num_connections = 0;
  (*cb_ptr)->server_supports_pipelining = FALSE;

  (*cb_ptr)->conn_list = Curl_llist_alloc((curl_llist_dtor) conn_llist_dtor);
  if(!(*cb_ptr)->conn_list) {
    Curl_safefree(*cb_ptr);
    return CURLE_OUT_OF_MEMORY;
  }
  return CURLE_OK;
}