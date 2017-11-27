static int gmond_config_set_address (oconfig_item_t *ci, /* {{{ */
    char **ret_addr, char **ret_port)
{
  char *addr;
  char *port;

  if ((ci->values_num != 1) && (ci->values_num != 2))
  {
    WARNING ("gmond plugin: The `%s' config option needs "
        "one or two string arguments.",
        ci->key);
    return (-1);
  }
  if ((ci->values[0].type != OCONFIG_TYPE_STRING)
      || ((ci->values_num == 2)
        && (ci->values[1].type != OCONFIG_TYPE_STRING)))
  {
    WARNING ("gmond plugin: The `%s' config option needs "
        "one or two string arguments.",
        ci->key);
    return (-1);
  }

  addr = strdup (ci->values[0].value.string);
  if (ci->values_num == 2)
    port = strdup (ci->values[1].value.string);
  else
    port = NULL;

  if ((addr == NULL) || ((ci->values_num == 2) && (port == NULL)))
  {
    ERROR ("gmond plugin: strdup failed.");
    sfree (addr);
    sfree (port);
    return (-1);
  }

  sfree (*ret_addr);
  sfree (*ret_port);

  *ret_addr = addr;
  *ret_port = port;

  return (0);
}