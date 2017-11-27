static void md_entry_free(meta_entry_t *e) /* {{{ */
{
  if (e == NULL)
    return;

  free(e->key);

  if (e->type == MD_TYPE_STRING)
    free(e->value.mv_string);

  if (e->next != NULL)
    md_entry_free(e->next);

  free(e);
}