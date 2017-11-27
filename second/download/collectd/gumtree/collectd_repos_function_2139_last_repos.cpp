int udb_query_prepare_result(udb_query_t const *q, /* {{{ */
                             udb_query_preparation_area_t *prep_area,
                             const char *host, const char *plugin,
                             const char *db_name, char **column_names,
                             size_t column_num, cdtime_t interval) {
  udb_result_preparation_area_t *r_area;
  udb_result_t *r;
  int status;

  if ((q == NULL) || (prep_area == NULL))
    return -EINVAL;

  udb_query_finish_result(q, prep_area);

  prep_area->column_num = column_num;
  prep_area->host = strdup(host);
  prep_area->plugin = strdup(plugin);
  prep_area->db_name = strdup(db_name);

  prep_area->interval = interval;

  if ((prep_area->host == NULL) || (prep_area->plugin == NULL) ||
      (prep_area->db_name == NULL)) {
    ERROR("db query utils: Query `%s': Prepare failed: Out of memory.",
          q->name);
    udb_query_finish_result(q, prep_area);
    return -ENOMEM;
  }

#if defined(COLLECT_DEBUG) && COLLECT_DEBUG
  do {
    for (size_t i = 0; i < column_num; i++) {
      DEBUG("db query utils: udb_query_prepare_result: "
            "query = %s; column[%zu] = %s;",
            q->name, i, column_names[i]);
    }
  } while (0);
#endif

  /* Determine the position of the PluginInstance column {{{ */
  if (q->plugin_instance_from != NULL) {
    size_t i;

    for (i = 0; i < column_num; i++) {
      if (strcasecmp(q->plugin_instance_from, column_names[i]) == 0) {
        prep_area->plugin_instance_pos = i;
        break;
      }
    }

    if (i >= column_num) {
      ERROR("db query utils: udb_query_prepare_result: "
            "Column `%s' from `PluginInstanceFrom' could not be found.",
            q->plugin_instance_from);
      udb_query_finish_result(q, prep_area);
      return -ENOENT;
    }
  }
  /* }}} */

  for (r = q->results, r_area = prep_area->result_prep_areas; r != NULL;
       r = r->next, r_area = r_area->next) {
    if (!r_area) {
      ERROR("db query utils: Query `%s': Invalid number of result "
            "preparation areas.",
            q->name);
      udb_query_finish_result(q, prep_area);
      return -EINVAL;
    }

    status = udb_result_prepare_result(r, r_area, column_names, column_num);
    if (status != 0) {
      udb_query_finish_result(q, prep_area);
      return status;
    }
  }

  return 0;
}