int plugin_flush (const char *plugin, cdtime_t timeout, const char *identifier)
{
  llentry_t *le;

  if (list_flush == NULL)
    return (0);

  le = llist_head (list_flush);
  while (le != NULL)
  {
    callback_func_t *cf;
    plugin_flush_cb callback;

    if ((plugin != NULL)
        && (strcmp (plugin, le->key) != 0))
    {
      le = le->next;
      continue;
    }

    cf = le->value;
    callback = cf->cf_callback;

    (*callback) (timeout, identifier, &cf->cf_udata);

    le = le->next;
  }
  return (0);
}