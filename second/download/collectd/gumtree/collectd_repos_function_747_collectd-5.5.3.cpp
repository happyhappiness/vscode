static int redis_config_node (oconfig_item_t *ci) /* {{{ */
{
  redis_node_t rn;
  redis_query_t *rq;
  int i;
  int status;
  int timeout;

  memset (&rn, 0, sizeof (rn));
  sstrncpy (rn.host, REDIS_DEF_HOST, sizeof (rn.host));
  rn.port = REDIS_DEF_PORT;
  rn.timeout.tv_usec = REDIS_DEF_TIMEOUT;
  rn.queries = NULL;

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
    else if (strcasecmp ("Query", option->key) == 0)
    {
      rq = redis_config_query(option);
      if (rq == NULL) {
          status =1;
      } else {
          rq->next = rn.queries;
          rn.queries = rq;
      }
    }
    else if (strcasecmp ("Timeout", option->key) == 0)
    {
      status = cf_util_get_int (option, &timeout);
      if (status == 0) rn.timeout.tv_usec = timeout;
    }
    else if (strcasecmp ("Password", option->key) == 0)
      status = cf_util_get_string_buffer (option, rn.passwd, sizeof (rn.passwd));
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