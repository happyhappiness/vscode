static CURLcode addHandleToPipeline(struct Curl_easy *data,
                                    struct curl_llist *pipeline)
{
  Curl_llist_insert_next(pipeline, pipeline->tail, data,
                         &data->pipeline_queue);
  return CURLE_OK;
}