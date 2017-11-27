static int wr_config_node (oconfig_item_t *ci) /* {{{ */
{
  wr_node_t *node;
  int timeout;
  int status;
  int i;

  node = malloc (sizeof (*node));
  if (node == NULL)
    return (ENOMEM);
  memset (node, 0, sizeof (*node));
  node->host = NULL;
  node->port = 0;
  node->timeout.tv_sec = 0;
  node->timeout.tv_usec = 1000;
  node->conn = NULL;
  pthread_mutex_init (&node->lock, /* attr = */ NULL);

  status = cf_util_get_string_buffer (ci, node->name, sizeof (node->name));
  if (status != 0)
  {
    sfree (node);
    return (status);
  }

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Host", child->key) == 0)
      status = cf_util_get_string (child, &node->host);
    else if (strcasecmp ("Port", child->key) == 0)
    {
      status = cf_util_get_port_number (child);
      if (status > 0)
      {
        node->port = status;
        status = 0;
      }
    }
    else if (strcasecmp ("Timeout", child->key) == 0) {
      status = cf_util_get_int (child, &timeout);
      if (status == 0) node->timeout.tv_usec = timeout;
    }
    else
      WARNING ("write_redis plugin: Ignoring unknown config option \"%s\".",
          child->key);

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  if (status == 0)
  {
    char cb_name[DATA_MAX_NAME_LEN];
    user_data_t ud;

    ssnprintf (cb_name, sizeof (cb_name), "write_redis/%s", node->name);

    ud.data = node;
    ud.free_func = wr_config_free;

    status = plugin_register_write (cb_name, wr_write, &ud);
  }

  if (status != 0)
    wr_config_free (node);

  return (status);
}