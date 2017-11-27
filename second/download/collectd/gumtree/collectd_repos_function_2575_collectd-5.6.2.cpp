static void destroy_all_callbacks(llist_t **list) /* {{{ */
{
  llentry_t *le;

  if (*list == NULL)
    return;

  le = llist_head(*list);
  while (le != NULL) {
    llentry_t *le_next;

    le_next = le->next;

    sfree(le->key);
    destroy_callback(le->value);
    le->value = NULL;

    le = le_next;
  }

  llist_destroy(*list);
  *list = NULL;
}