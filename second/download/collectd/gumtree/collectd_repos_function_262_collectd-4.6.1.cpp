static int csnmp_config_add_host_community (host_definition_t *hd, oconfig_item_t *ci)
{
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("snmp plugin: The `Community' config option needs exactly one string argument.");
    return (-1);
  }

  if (hd->community == NULL)
    free (hd->community);

  hd->community = strdup (ci->values[0].value.string);
  if (hd->community == NULL)
    return (-1);

  DEBUG ("snmp plugin: host = %s; host->community = %s;",
      hd->name, hd->community);

  return (0);
}