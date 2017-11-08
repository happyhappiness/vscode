CURLcode Curl_add_handle_to_pipeline(struct SessionHandle *handle,
                                     struct connectdata *conn)
{
  struct curl_llist_element *sendhead = conn->send_pipe->head;
  struct curl_llist *pipeline;
  CURLcode result;

  pipeline = conn->send_pipe;

  result = Curl_addHandleToPipeline(handle, pipeline);

  if(pipeline == conn->send_pipe && sendhead != conn->send_pipe->head) {
    /* this is a new one as head, expire it */
    conn->writechannel_inuse = FALSE; /* not in use yet */
    Curl_expire(conn->send_pipe->head->ptr, 1);
  }

#if 0 /* enable for pipeline debugging */
  print_pipeline(conn);
#endif

  return result;
}