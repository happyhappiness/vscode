int
Curl_llist_insert_next(struct curl_llist *list, struct curl_llist_element *e,
                       const void *p)
{
  struct curl_llist_element *ne =
    (struct curl_llist_element *) malloc(sizeof(struct curl_llist_element));
  if(!ne)
    return 0;

  ne->ptr = (void *) p;
  if (list->size == 0) {
    list->head = ne;
    list->head->prev = NULL;
    list->head->next = NULL;
    list->tail = ne;
  }
  else {
    ne->next = e->next;
    ne->prev = e;
    if (e->next) {
      e->next->prev = ne;
    }
    else {
      list->tail = ne;
    }
    e->next = ne;
  }

  ++list->size;

  return 1;
}