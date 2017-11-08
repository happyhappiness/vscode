static int moveHandleFromSendToRecvPipeline(struct SessionHandle *handle,
                                            struct connectdata *conn)
{
  struct curl_llist_element *curr;

  curr = conn->send_pipe->head;
  while(curr) {
    if(curr->ptr == handle) {
      Curl_llist_move(conn->send_pipe, curr,
                      conn->recv_pipe, conn->recv_pipe->tail);
      return 1; /* we moved a handle */
    }
    curr = curr->next;
  }

  return 0;
}