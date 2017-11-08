static CURLcode addHandleToPipeline(struct Curl_easy *data,
                                    struct curl_llist *pipeline)
{
  if(!Curl_llist_insert_next(pipeline, pipeline->tail, data))
    return CURLE_OUT_OF_MEMORY;
  return CURLE_OK;
}