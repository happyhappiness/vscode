void llist_destroy(llist_t *l) {
  llentry_t *e_this;
  llentry_t *e_next;

  if (l == NULL)
    return;

  for (e_this = l->head; e_this != NULL; e_this = e_next) {
    e_next = e_this->next;
    llentry_destroy(e_this);
  }

  free(l);
}