void 
Curl_llist_destroy(curl_llist *list, void *user)
{
  while (list->size > 0) {
    Curl_llist_remove(list, CURL_LLIST_TAIL(list), user);
  }

  free(list);
  list = NULL;
}