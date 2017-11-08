int 
Curl_llist_insert_prev(curl_llist *list, curl_llist_element *e, const void *p)
{
  curl_llist_element *ne;

  ne = (curl_llist_element *) malloc(sizeof(curl_llist_element));
  ne->ptr = (void *) p;
  if (list->size == 0) {
    list->head = ne;
    list->head->prev = NULL;
    list->head->next = NULL;
    list->tail = ne;
  } else {
    ne->next = e;
    ne->prev = e->prev;
    if (e->prev)
      e->prev->next = ne;
    else
      list->head = ne;
    e->prev = ne;
  }

  ++list->size;

  return 1;
}