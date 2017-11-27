static meta_entry_t *md_entry_alloc (const char *key) /* {{{ */
{
  meta_entry_t *e;

  e = (meta_entry_t *) malloc (sizeof (*e));
  if (e == NULL)
  {
    ERROR ("md_entry_alloc: malloc failed.");
    return (NULL);
  }
  memset (e, 0, sizeof (*e));

  e->key = md_strdup (key);
  if (e->key == NULL)
  {
    free (e);
    ERROR ("md_entry_alloc: md_strdup failed.");
    return (NULL);
  }

  e->type = 0;
  e->next = NULL;

  return (e);
}