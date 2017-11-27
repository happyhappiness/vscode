static int csnmp_config (oconfig_item_t *ci)
{
  int i;

  call_snmp_init_once ();

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp ("Data", child->key) == 0)
      csnmp_config_add_data (child);
    else if (strcasecmp ("Host", child->key) == 0)
      csnmp_config_add_host (child);
    else
    {
      WARNING ("snmp plugin: Ignoring unknown config option `%s'.", child->key);
    }
  } /* for (ci->children) */

  return (0);
}