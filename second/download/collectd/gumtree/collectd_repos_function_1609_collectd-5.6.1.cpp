static void cx_list_free (llist_t *list) /* {{{ */
{
  llentry_t *le;

  le = llist_head (list);
  while (le != NULL)
  {
    llentry_t *le_next;

    le_next = le->next;

    sfree (le->key);
    cx_xpath_free (le->value);

    le = le_next;
  }

  llist_destroy (list);
}