static bool isHandleAtHead(struct SessionHandle *handle,
                           struct curl_llist *pipeline)
{
  struct curl_llist_element *curr = pipeline->head;
  if(curr)
    return (bool)(curr->ptr == handle);

  return FALSE;
}