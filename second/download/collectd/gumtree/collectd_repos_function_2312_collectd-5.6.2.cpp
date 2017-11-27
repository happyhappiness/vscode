void llist_append(llist_t *l, llentry_t *e) {
  e->next = NULL;

  if (l->tail == NULL)
    l->head = e;
  else
    l->tail->next = e;

  l->tail = e;

  ++(l->size);
}