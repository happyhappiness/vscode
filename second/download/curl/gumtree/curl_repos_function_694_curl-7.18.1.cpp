CURLcode Curl_addHandleToPipeline(struct SessionHandle *data,
                                  struct curl_llist *pipeline)
{
#ifdef CURLDEBUG
  if(!IsPipeliningPossible(data)) {
    /* when not pipelined, there MUST be no handle in the list already */
    if(pipeline->head)
      infof(data, "PIPE when no PIPE supposed!\n");
  }
#endif
  if(!Curl_llist_insert_next(pipeline, pipeline->tail, data))
    return CURLE_OUT_OF_MEMORY;
  return CURLE_OK;
}