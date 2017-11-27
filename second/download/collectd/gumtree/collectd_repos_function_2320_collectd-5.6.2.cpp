llentry_t *llist_tail(llist_t *l) {
  if (l == NULL)
    return (NULL);
  return (l->tail);
}