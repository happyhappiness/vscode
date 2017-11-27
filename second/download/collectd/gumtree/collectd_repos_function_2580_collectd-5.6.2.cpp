static int plugin_unregister(llist_t *list, const char *name) /* {{{ */
{
  llentry_t *e;

  if (list == NULL)
    return (-1);

  e = llist_search(list, name);
  if (e == NULL)
    return (-1);

  llist_remove(list, e);

  sfree(e->key);
  destroy_callback(e->value);

  llentry_destroy(e);

  return (0);
}