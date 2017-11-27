static int csnmp_config_add_host_address (host_definition_t *hd, oconfig_item_t *ci)
{
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("snmp plugin: The `Address' config option needs exactly one string argument.");
    return (-1);
  }

  if (hd->address == NULL)
    free (hd->address);

  hd->address = strdup (ci->values[0].value.string);
  if (hd->address == NULL)
    return (-1);

  DEBUG ("snmp plugin: host = %s; host->address = %s;",
      hd->name, hd->address);

  return (0);
}