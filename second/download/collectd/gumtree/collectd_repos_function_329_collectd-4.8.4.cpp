static int csnmp_config_add_host_version (host_definition_t *hd, oconfig_item_t *ci)
{
  int version;

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_NUMBER))
  {
    WARNING ("snmp plugin: The `Version' config option needs exactly one number argument.");
    return (-1);
  }

  version = (int) ci->values[0].value.number;
  if ((version != 1) && (version != 2))
  {
    WARNING ("snmp plugin: `Version' must either be `1' or `2'.");
    return (-1);
  }

  hd->version = version;

  return (0);
}