int plugin_write(const char *plugin, /* {{{ */
                 const data_set_t *ds, const value_list_t *vl) {
  llentry_t *le;
  int status;

  if (vl == NULL)
    return EINVAL;

  if (list_write == NULL)
    return ENOENT;

  if (ds == NULL) {
    ds = plugin_get_ds(vl->type);
    if (ds == NULL) {
      ERROR("plugin_write: Unable to lookup type `%s'.", vl->type);
      return ENOENT;
    }
  }

  if (plugin == NULL) {
    int success = 0;
    int failure = 0;

    le = llist_head(list_write);
    while (le != NULL) {
      callback_func_t *cf = le->value;
      plugin_write_cb callback;

      /* do not switch plugin context; rather keep the context (interval)
       * information of the calling read plugin */

      DEBUG("plugin: plugin_write: Writing values via %s.", le->key);
      callback = cf->cf_callback;
      status = (*callback)(ds, vl, &cf->cf_udata);
      if (status != 0)
        failure++;
      else
        success++;

      le = le->next;
    }

    if ((success == 0) && (failure != 0))
      status = -1;
    else
      status = 0;
  } else /* plugin != NULL */
  {
    callback_func_t *cf;
    plugin_write_cb callback;

    le = llist_head(list_write);
    while (le != NULL) {
      if (strcasecmp(plugin, le->key) == 0)
        break;

      le = le->next;
    }

    if (le == NULL)
      return ENOENT;

    cf = le->value;

    /* do not switch plugin context; rather keep the context (interval)
     * information of the calling read plugin */

    DEBUG("plugin: plugin_write: Writing values via %s.", le->key);
    callback = cf->cf_callback;
    status = (*callback)(ds, vl, &cf->cf_udata);
  }

  return status;
}