static int llist_strcmp(llentry_t *e, void *ud) {
  if ((e == NULL) || (ud == NULL))
    return -1;
  return strcmp(e->key, (const char *)ud);
}