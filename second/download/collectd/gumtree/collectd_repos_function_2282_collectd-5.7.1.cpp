static void ts_key_list_free(ts_key_list_t *l) /* {{{ */
{
  if (l == NULL)
    return;

  sfree(l->key);

  if (l->next != NULL)
    ts_key_list_free(l->next);

  sfree(l);
}