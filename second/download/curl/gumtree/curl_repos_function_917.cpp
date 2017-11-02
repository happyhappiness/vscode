int
Curl_llist_remove(struct curl_llist *list, struct curl_llist_element *e,
                  void *user)
{
  if(e == NULL || list->size == 0)
    return 1;

  if(e == list->head) {
    list->head = e->next;

    if(list->head == NULL)
      list->tail = NULL;
    else
      e->next->prev = NULL;
  }
  else {
    e->prev->next = e->next;
    if(!e->next)
      list->tail = e->prev;
    else
      e->next->prev = e->prev;
  }

  list->dtor(user, e->ptr);

  e->ptr  = NULL;
  e->prev = NULL;
  e->next = NULL;

  free(e);
  --list->size;

  return 1;
}