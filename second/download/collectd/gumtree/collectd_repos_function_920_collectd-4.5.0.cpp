int plugin_flush (const char *plugin, int timeout, const char *identifier)
{
  int (*callback) (int timeout, const char *identifier);
  llentry_t *le;

  if (list_flush == NULL)
    return (0);

  le = llist_head (list_flush);
  while (le != NULL)
  {
    if ((plugin != NULL)
        && (strcmp (plugin, le->key) != 0))
    {
      le = le->next;
      continue;
    }

    callback = (int (*) (int, const char *)) le->value;
    (*callback) (timeout, identifier);

    le = le->next;
  }
  return (0);
}