int plugin_dispatch_missing (const value_list_t *vl) /* {{{ */
{
  llentry_t *le;

  if (list_missing == NULL)
    return (0);

  le = llist_head (list_missing);
  while (le != NULL)
  {
    callback_func_t *cf;
    plugin_missing_cb callback;
    int status;

    cf = le->value;
    callback = cf->cf_callback;

    status = (*callback) (vl, &cf->cf_udata);
    if (status != 0)
    {
      if (status < 0)
      {
        ERROR ("plugin_dispatch_missing: Callback function \"%s\" "
            "failed with status %i.",
            le->key, status);
        return (status);
      }
      else
      {
        return (0);
      }
    }

    le = le->next;
  }
  return (0);
}