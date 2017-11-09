static bool pipe_head(struct Curl_easy *data,
                      struct curl_llist *pipeline)
{
  if(pipeline) {
    struct curl_llist_element *curr = pipeline->head;
    if(curr)
      return (curr->ptr == data) ? TRUE : FALSE;
  }
  return FALSE;
}