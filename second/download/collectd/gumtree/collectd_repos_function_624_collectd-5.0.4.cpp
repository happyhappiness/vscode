static int redis_config_node (oconfig_item_t *ci) /* {{{ */
{
  redis_node_t rn;
  int i;
  int status;

  memset (&rn, 0, sizeof (rn));
  sstrncpy (rn.host, REDIS_DEF_HOST, sizeof (rn.host));
  rn.port = REDIS_DEF_PORT;
  rn.timeout = REDIS_DEF_TIMEOUT;

  status = cf_util_get_string_buffer (ci, rn.name, sizeof (rn.name));
  if (status != 0)
    return (status);

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp ("Host", option->key) == 0)
      status = cf_util_get_string_buffer (option, rn.host, sizeof (rn.host));
    else if (strcasecmp ("Port", option->key) == 0)
    {
      status = cf_util_get_port_number (option);
      if (status > 0)
      {
        rn.port = status;
        status = 0;
      }
    }
    else if (strcasecmp ("Timeout", option->key) == 0)
      status = cf_util_get_int (option, &rn.timeout);
    else
      WARNING ("redis plugin: Option `%s' not allowed inside a `Node' "
          "block. I'll ignore this option.", option->key);

    if (status != 0)
      break;
  }

  if (status != 0)
    return (status);

  return (redis_node_add (&rn));
}