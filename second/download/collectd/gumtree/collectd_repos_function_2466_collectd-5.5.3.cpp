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
    plugin_ctx_t old_ctx;
    int status;

    cf = le->value;
    old_ctx = plugin_set_ctx (cf->cf_ctx);
    callback = cf->cf_callback;

    status = (*callback) (vl, &cf->cf_udata);
    plugin_set_ctx (old_ctx);
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