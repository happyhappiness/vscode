struct curl_llist *
Curl_llist_alloc(curl_llist_dtor dtor)
{
  struct curl_llist *list;

  list = malloc(sizeof(struct curl_llist));
  if(!list)
    return NULL;

  llist_init(list, dtor);

  return list;
}