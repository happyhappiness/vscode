int 
Curl_llist_remove_next(curl_llist *list, curl_llist_element *e, void *user)
{
  return Curl_llist_remove(list, e->next, user);
}