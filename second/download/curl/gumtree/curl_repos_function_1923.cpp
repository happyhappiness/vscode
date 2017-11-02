int Curl_bundle_remove_conn(struct connectbundle *cb_ptr,
                            struct connectdata *conn)
{
  struct curl_llist_element *curr;

  curr = cb_ptr->conn_list->head;
  while(curr) {
    if(curr->ptr == conn) {
      Curl_llist_remove(cb_ptr->conn_list, curr, NULL);
      cb_ptr->num_connections--;
      conn->bundle = NULL;
      return 1; /* we removed a handle */
    }
    curr = curr->next;
  }
  return 0;
}