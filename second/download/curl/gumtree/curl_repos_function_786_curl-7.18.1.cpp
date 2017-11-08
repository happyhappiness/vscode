static int checkPendPipeline(struct connectdata *conn)
{
  int result = 0;

  if (conn->server_supports_pipelining) {
    size_t pipeLen = conn->send_pipe->size + conn->recv_pipe->size;
    struct curl_llist_element *curr = conn->pend_pipe->head;

    while(pipeLen < MAX_PIPELINE_LENGTH && curr) {
      Curl_llist_move(conn->pend_pipe, curr,
                      conn->send_pipe, conn->send_pipe->tail);
      Curl_pgrsTime(curr->ptr, TIMER_CONNECT);
      ++result; /* count how many handles we moved */
      curr = conn->pend_pipe->head;
      ++pipeLen;
    }
    if (result > 0)
      conn->now = Curl_tvnow();
  }

  return result;
}