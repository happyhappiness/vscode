static CURLcode bundle_create(struct Curl_easy *data,
                              struct connectbundle **cb_ptr)
{
  (void)data;
  DEBUGASSERT(*cb_ptr == NULL);
  *cb_ptr = malloc(sizeof(struct connectbundle));
  if(!*cb_ptr)
    return CURLE_OUT_OF_MEMORY;

  (*cb_ptr)->num_connections = 0;
  (*cb_ptr)->multiuse = BUNDLE_UNKNOWN;

  Curl_llist_init(&(*cb_ptr)->conn_list, (curl_llist_dtor) conn_llist_dtor);
  return CURLE_OK;
}