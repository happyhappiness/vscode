static int csnmp_config_add_host_interval (host_definition_t *hd, oconfig_item_t *ci)
{
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_NUMBER))
  {
    WARNING ("snmp plugin: The `Interval' config option needs exactly one number argument.");
    return (-1);
  }

  hd->interval = ci->values[0].value.number >= 0
    ? (uint32_t) ci->values[0].value.number
    : 0;

  return (0);
}