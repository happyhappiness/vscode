static CURLcode addHandleToSendOrPendPipeline(struct SessionHandle *handle,
                                              struct connectdata *conn)
{
  size_t pipeLen = conn->send_pipe->size + conn->recv_pipe->size;
  struct curl_llist *pipeline;

  if(!Curl_isPipeliningEnabled(handle) ||
     pipeLen == 0)
    pipeline = conn->send_pipe;
  else {
    if(conn->server_supports_pipelining &&
       pipeLen < MAX_PIPELINE_LENGTH)
      pipeline = conn->send_pipe;
    else
      pipeline = conn->pend_pipe;
  }

  return Curl_addHandleToPipeline(handle, pipeline);
}