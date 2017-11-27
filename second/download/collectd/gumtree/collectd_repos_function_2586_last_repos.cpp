llist_t *llist_create(void) {
  llist_t *ret;

  ret = calloc(1, sizeof(*ret));
  if (ret == NULL)
    return NULL;

  return ret;
}