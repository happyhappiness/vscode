static int config_query_param_add(udb_query_t *q, oconfig_item_t *ci) {
  c_psql_user_data_t *data;
  const char *param_str;

  c_psql_param_t *tmp;

  data = udb_query_get_user_data(q);
  if (NULL == data) {
    data = calloc(1, sizeof(*data));
    if (NULL == data) {
      log_err("Out of memory.");
      return -1;
    }
    data->params = NULL;
    data->params_num = 0;

    udb_query_set_user_data(q, data);
  }

  tmp = realloc(data->params, (data->params_num + 1) * sizeof(*data->params));
  if (NULL == tmp) {
    log_err("Out of memory.");
    return -1;
  }
  data->params = tmp;

  param_str = ci->values[0].value.string;
  if (0 == strcasecmp(param_str, "hostname"))
    data->params[data->params_num] = C_PSQL_PARAM_HOST;
  else if (0 == strcasecmp(param_str, "database"))
    data->params[data->params_num] = C_PSQL_PARAM_DB;
  else if (0 == strcasecmp(param_str, "username"))
    data->params[data->params_num] = C_PSQL_PARAM_USER;
  else if (0 == strcasecmp(param_str, "interval"))
    data->params[data->params_num] = C_PSQL_PARAM_INTERVAL;
  else if (0 == strcasecmp(param_str, "instance"))
    data->params[data->params_num] = C_PSQL_PARAM_INSTANCE;
  else {
    log_err("Invalid parameter \"%s\".", param_str);
    return 1;
  }

  data->params_num++;
  return (0);
}