void Curl_bundle_destroy(struct connectbundle *cb_ptr)
{
  if(!cb_ptr)
    return;

  if(cb_ptr->conn_list) {
    Curl_llist_destroy(cb_ptr->conn_list, NULL);
    cb_ptr->conn_list = NULL;
  }
  Curl_safefree(cb_ptr);
}