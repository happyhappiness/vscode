static value_list_t *
plugin_value_list_clone(value_list_t const *vl_orig) /* {{{ */
{
  value_list_t *vl;

  if (vl_orig == NULL)
    return (NULL);

  vl = malloc(sizeof(*vl));
  if (vl == NULL)
    return (NULL);
  memcpy(vl, vl_orig, sizeof(*vl));

  vl->values = calloc(vl_orig->values_len, sizeof(*vl->values));
  if (vl->values == NULL) {
    plugin_value_list_free(vl);
    return (NULL);
  }
  memcpy(vl->values, vl_orig->values,
         vl_orig->values_len * sizeof(*vl->values));

  vl->meta = meta_data_clone(vl->meta);
  if ((vl_orig->meta != NULL) && (vl->meta == NULL)) {
    plugin_value_list_free(vl);
    return (NULL);
  }

  if (vl->time == 0)
    vl->time = cdtime();

  /* Fill in the interval from the thread context, if it is zero. */
  if (vl->interval == 0) {
    plugin_ctx_t ctx = plugin_get_ctx();

    if (ctx.interval != 0)
      vl->interval = ctx.interval;
    else {
      char name[6 * DATA_MAX_NAME_LEN];
      FORMAT_VL(name, sizeof(name), vl);
      ERROR("plugin_value_list_clone: Unable to determine "
            "interval from context for "
            "value list \"%s\". "
            "This indicates a broken plugin. "
            "Please report this problem to the "
            "collectd mailing list or at "
            "<http://collectd.org/bugs/>.",
            name);
      vl->interval = cf_get_default_interval();
    }
  }

  return (vl);
}