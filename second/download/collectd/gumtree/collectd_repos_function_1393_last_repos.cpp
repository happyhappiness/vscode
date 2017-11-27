static int wr_config_node(oconfig_item_t *ci) /* {{{ */
{
  wr_node_t *node;
  int timeout;
  int status;

  node = calloc(1, sizeof(*node));
  if (node == NULL)
    return ENOMEM;
  node->host = NULL;
  node->port = 0;
  node->timeout.tv_sec = 0;
  node->timeout.tv_usec = 1000;
  node->conn = NULL;
  node->prefix = NULL;
  node->database = 0;
  node->max_set_size = -1;
  node->max_set_duration = -1;
  node->store_rates = 1;
  pthread_mutex_init(&node->lock, /* attr = */ NULL);

  status = cf_util_get_string_buffer(ci, node->name, sizeof(node->name));
  if (status != 0) {
    sfree(node);
    return status;
  }

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Host", child->key) == 0)
      status = cf_util_get_string(child, &node->host);
    else if (strcasecmp("Port", child->key) == 0) {
      status = cf_util_get_port_number(child);
      if (status > 0) {
        node->port = status;
        status = 0;
      }
    } else if (strcasecmp("Timeout", child->key) == 0) {
      status = cf_util_get_int(child, &timeout);
      if (status == 0)
        node->timeout.tv_usec = timeout;
    } else if (strcasecmp("Prefix", child->key) == 0) {
      status = cf_util_get_string(child, &node->prefix);
    } else if (strcasecmp("Database", child->key) == 0) {
      status = cf_util_get_int(child, &node->database);
    } else if (strcasecmp("MaxSetSize", child->key) == 0) {
      status = cf_util_get_int(child, &node->max_set_size);
    } else if (strcasecmp("MaxSetDuration", child->key) == 0) {
      status = cf_util_get_int(child, &node->max_set_duration);
    } else if (strcasecmp("StoreRates", child->key) == 0) {
      status = cf_util_get_boolean(child, &node->store_rates);
    } else
      WARNING("write_redis plugin: Ignoring unknown config option \"%s\".",
              child->key);

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  if (status == 0) {
    char cb_name[sizeof("write_redis/") + DATA_MAX_NAME_LEN];

    snprintf(cb_name, sizeof(cb_name), "write_redis/%s", node->name);

    status =
        plugin_register_write(cb_name, wr_write,
                              &(user_data_t){
                                  .data = node, .free_func = wr_config_free,
                              });
  }

  if (status != 0)
    wr_config_free(node);

  return status;
}