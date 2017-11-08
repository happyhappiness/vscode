static bool isHandleAtHead(struct SessionHandle *handle,
                           struct curl_llist *pipeline)
{
  struct curl_llist_element *curr = pipeline->head;
  if(curr)
    return (curr->ptr == handle) ? TRUE : FALSE;

  return FALSE;
}