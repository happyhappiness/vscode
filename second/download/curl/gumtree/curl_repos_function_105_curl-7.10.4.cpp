curl_llist *
Curl_llist_alloc(curl_llist_dtor dtor)
{
  curl_llist *list;

  list = (curl_llist *)malloc(sizeof(curl_llist));
  if(NULL == list)
    return NULL;

  Curl_llist_init(list, dtor);

  return list;
}