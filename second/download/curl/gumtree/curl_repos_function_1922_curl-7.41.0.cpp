CURLcode Curl_bundle_add_conn(struct connectbundle *cb_ptr,
                              struct connectdata *conn)
{
  if(!Curl_llist_insert_next(cb_ptr->conn_list, cb_ptr->conn_list->tail, conn))
    return CURLE_OUT_OF_MEMORY;

  conn->bundle = cb_ptr;

  cb_ptr->num_connections++;
  return CURLE_OK;
}