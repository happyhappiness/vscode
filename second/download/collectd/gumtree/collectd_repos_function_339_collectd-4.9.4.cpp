static int csnmp_config_add_host (oconfig_item_t *ci)
{
  host_definition_t *hd;
  int status = 0;
  int i;

  /* Registration stuff. */
  char cb_name[DATA_MAX_NAME_LEN];
  user_data_t cb_data;
  struct timespec cb_interval;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("snmp plugin: `Host' needs exactly one string argument.");
    return (-1);
  }

  hd = (host_definition_t *) malloc (sizeof (host_definition_t));
  if (hd == NULL)
    return (-1);
  memset (hd, '\0', sizeof (host_definition_t));
  hd->version = 2;
  C_COMPLAIN_INIT (&hd->complaint);

  hd->name = strdup (ci->values[0].value.string);
  if (hd->name == NULL)
  {
    free (hd);
    return (-1);
  }

  hd->sess_handle = NULL;
  hd->interval = 0;

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;
    status = 0;

    if (strcasecmp ("Address", option->key) == 0)
      status = csnmp_config_add_host_address (hd, option);
    else if (strcasecmp ("Community", option->key) == 0)
      status = csnmp_config_add_host_community (hd, option);
    else if (strcasecmp ("Version", option->key) == 0)
      status = csnmp_config_add_host_version (hd, option);
    else if (strcasecmp ("Collect", option->key) == 0)
      csnmp_config_add_host_collect (hd, option);
    else if (strcasecmp ("Interval", option->key) == 0)
      csnmp_config_add_host_interval (hd, option);
    else
    {
      WARNING ("snmp plugin: csnmp_config_add_host: Option `%s' not allowed here.", option->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (ci->children) */

  while (status == 0)
  {
    if (hd->address == NULL)
    {
      WARNING ("snmp plugin: `Address' not given for host `%s'", hd->name);
      status = -1;
      break;
    }
    if (hd->community == NULL)
    {
      WARNING ("snmp plugin: `Community' not given for host `%s'", hd->name);
      status = -1;
      break;
    }

    break;
  } /* while (status == 0) */

  if (status != 0)
  {
    csnmp_host_definition_destroy (hd);
    return (-1);
  }

  DEBUG ("snmp plugin: hd = { name = %s, address = %s, community = %s, version = %i }",
      hd->name, hd->address, hd->community, hd->version);

  ssnprintf (cb_name, sizeof (cb_name), "snmp-%s", hd->name);

  memset (&cb_data, 0, sizeof (cb_data));
  cb_data.data = hd;
  cb_data.free_func = csnmp_host_definition_destroy;

  memset (&cb_interval, 0, sizeof (cb_interval));
  if (hd->interval != 0)
    cb_interval.tv_sec = (time_t) hd->interval;

  status = plugin_register_complex_read (cb_name, csnmp_read_host,
      /* interval = */ &cb_interval, /* user_data = */ &cb_data);
  if (status != 0)
  {
    ERROR ("snmp plugin: Registering complex read function failed.");
    csnmp_host_definition_destroy (hd);
    return (-1);
  }

  return (0);
}