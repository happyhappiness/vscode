{
  struct curl_llist_element *curr = pipeline->head;
  if(curr) {
    return (struct Curl_easy *) curr->ptr;
  }

  return NULL;
}