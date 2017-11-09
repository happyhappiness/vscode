CURLcode Curl_add_handle_to_pipeline(struct Curl_easy *handle,
                                     struct connectdata *conn)
{
  struct curl_llist_element *sendhead = conn->send_pipe.head;
  struct curl_llist *pipeline;
  CURLcode result;

  pipeline = &conn->send_pipe;

  result = addHandleToPipeline(handle, pipeline);

  if(pipeline == &conn->send_pipe && sendhead != conn->send_pipe.head) {
    /* this is a new one as head, expire it */
    Curl_pipeline_leave_write(conn); /* not in use yet */
    Curl_expire(conn->send_pipe.head->ptr, 0, EXPIRE_RUN_NOW);
  }

#if 0 /* enable for pipeline debugging */
  print_pipeline(conn);
#endif

  return result;
}