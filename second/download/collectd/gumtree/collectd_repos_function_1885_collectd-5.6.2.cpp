int udb_query_create(udb_query_t ***ret_query_list, /* {{{ */
                     size_t *ret_query_list_len, oconfig_item_t *ci,
                     udb_query_create_callback_t cb) {
  udb_query_t **query_list;
  size_t query_list_len;

  udb_query_t *q;
  int status;

  if ((ret_query_list == NULL) || (ret_query_list_len == NULL))
    return (-EINVAL);
  query_list = *ret_query_list;
  query_list_len = *ret_query_list_len;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("db query utils: The `Query' block "
            "needs exactly one string argument.");
    return (-1);
  }

  q = calloc(1, sizeof(*q));
  if (q == NULL) {
    ERROR("db query utils: calloc failed.");
    return (-1);
  }
  q->min_version = 0;
  q->max_version = UINT_MAX;
  q->statement = NULL;
  q->results = NULL;
  q->plugin_instance_from = NULL;

  status = udb_config_set_string(&q->name, ci);
  if (status != 0) {
    sfree(q);
    return (status);
  }

  /* Fill the `udb_query_t' structure.. */
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Statement", child->key) == 0)
      status = udb_config_set_string(&q->statement, child);
    else if (strcasecmp("Result", child->key) == 0)
      status = udb_result_create(q->name, &q->results, child);
    else if (strcasecmp("MinVersion", child->key) == 0)
      status = udb_config_set_uint(&q->min_version, child);
    else if (strcasecmp("MaxVersion", child->key) == 0)
      status = udb_config_set_uint(&q->max_version, child);
    else if (strcasecmp("PluginInstanceFrom", child->key) == 0)
      status = udb_config_set_string(&q->plugin_instance_from, child);

    /* Call custom callbacks */
    else if (cb != NULL) {
      status = (*cb)(q, child);
      if (status != 0) {
        WARNING("db query utils: The configuration callback failed "
                "to handle `%s'.",
                child->key);
      }
    } else {
      WARNING("db query utils: Query `%s': Option `%s' not allowed here.",
              q->name, child->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  /* Check that all necessary options have been given. */
  if (status == 0) {
    if (q->statement == NULL) {
      WARNING("db query utils: Query `%s': No `Statement' given.", q->name);
      status = -1;
    }
    if (q->results == NULL) {
      WARNING("db query utils: Query `%s': No (valid) `Result' block given.",
              q->name);
      status = -1;
    }
  } /* if (status == 0) */

  /* If all went well, add this query to the list of queries within the
   * database structure. */
  if (status == 0) {
    udb_query_t **temp;

    temp = realloc(query_list, sizeof(*query_list) * (query_list_len + 1));
    if (temp == NULL) {
      ERROR("db query utils: realloc failed");
      status = -1;
    } else {
      query_list = temp;
      query_list[query_list_len] = q;
      query_list_len++;
    }
  }

  if (status != 0) {
    udb_query_free_one(q);
    return (-1);
  }

  *ret_query_list = query_list;
  *ret_query_list_len = query_list_len;

  return (0);
}