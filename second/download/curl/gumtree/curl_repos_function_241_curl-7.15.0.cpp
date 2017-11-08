struct curl_llist *
Curl_llist_alloc(curl_llist_dtor dtor)
{
  struct curl_llist *list;

  list = (struct curl_llist *)malloc(sizeof(struct curl_llist));
  if(NULL == list)
    return NULL;

  Curl_llist_init(list, dtor);

  return list;
}