static int plugin_dispatch_values_internal(value_list_t *vl) {
  int status;
  static c_complain_t no_write_complaint = C_COMPLAIN_INIT_STATIC;

  data_set_t *ds;

  _Bool free_meta_data = 0;

  assert(vl != NULL);

  /* These fields are initialized by plugin_value_list_clone() if needed: */
  assert(vl->host[0] != 0);
  assert(vl->time != 0); /* The time is determined at _enqueue_ time. */
  assert(vl->interval != 0);

  if (vl->type[0] == 0 || vl->values == NULL || vl->values_len < 1) {
    ERROR("plugin_dispatch_values: Invalid value list "
          "from plugin %s.",
          vl->plugin);
    return (-1);
  }

  /* Free meta data only if the calling function didn't specify any. In
   * this case matches and targets may add some and the calling function
   * may not expect (and therefore free) that data. */
  if (vl->meta == NULL)
    free_meta_data = 1;

  if (list_write == NULL)
    c_complain_once(LOG_WARNING, &no_write_complaint,
                    "plugin_dispatch_values: No write callback has been "
                    "registered. Please load at least one output plugin, "
                    "if you want the collected data to be stored.");

  if (data_sets == NULL) {
    ERROR("plugin_dispatch_values: No data sets registered. "
          "Could the types database be read? Check "
          "your `TypesDB' setting!");
    return (-1);
  }

  if (c_avl_get(data_sets, vl->type, (void *)&ds) != 0) {
    char ident[6 * DATA_MAX_NAME_LEN];

    FORMAT_VL(ident, sizeof(ident), vl);
    INFO("plugin_dispatch_values: Dataset not found: %s "
         "(from \"%s\"), check your types.db!",
         vl->type, ident);
    return (-1);
  }

  DEBUG("plugin_dispatch_values: time = %.3f; interval = %.3f; "
        "host = %s; "
        "plugin = %s; plugin_instance = %s; "
        "type = %s; type_instance = %s;",
        CDTIME_T_TO_DOUBLE(vl->time), CDTIME_T_TO_DOUBLE(vl->interval),
        vl->host, vl->plugin, vl->plugin_instance, vl->type, vl->type_instance);

#if COLLECT_DEBUG
  assert(0 == strcmp(ds->type, vl->type));
#else
  if (0 != strcmp(ds->type, vl->type))
    WARNING("plugin_dispatch_values: (ds->type = %s) != (vl->type = %s)",
            ds->type, vl->type);
#endif

#if COLLECT_DEBUG
  assert(ds->ds_num == vl->values_len);
#else
  if (ds->ds_num != vl->values_len) {
    ERROR("plugin_dispatch_values: ds->type = %s: "
          "(ds->ds_num = %zu) != "
          "(vl->values_len = %zu)",
          ds->type, ds->ds_num, vl->values_len);
    return (-1);
  }
#endif

  escape_slashes(vl->host, sizeof(vl->host));
  escape_slashes(vl->plugin, sizeof(vl->plugin));
  escape_slashes(vl->plugin_instance, sizeof(vl->plugin_instance));
  escape_slashes(vl->type, sizeof(vl->type));
  escape_slashes(vl->type_instance, sizeof(vl->type_instance));

  if (pre_cache_chain != NULL) {
    status = fc_process_chain(ds, vl, pre_cache_chain);
    if (status < 0) {
      WARNING("plugin_dispatch_values: Running the "
              "pre-cache chain failed with "
              "status %i (%#x).",
              status, status);
    } else if (status == FC_TARGET_STOP)
      return (0);
  }

  /* Update the value cache */
  uc_update(ds, vl);

  if (post_cache_chain != NULL) {
    status = fc_process_chain(ds, vl, post_cache_chain);
    if (status < 0) {
      WARNING("plugin_dispatch_values: Running the "
              "post-cache chain failed with "
              "status %i (%#x).",
              status, status);
    }
  } else
    fc_default_action(ds, vl);

  if ((free_meta_data != 0) && (vl->meta != NULL)) {
    meta_data_destroy(vl->meta);
    vl->meta = NULL;
  }

  return (0);
}