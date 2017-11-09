static void bundle_destroy(struct connectbundle *cb_ptr)
{
  if(!cb_ptr)
    return;

  Curl_llist_destroy(&cb_ptr->conn_list, NULL);

  free(cb_ptr);
}