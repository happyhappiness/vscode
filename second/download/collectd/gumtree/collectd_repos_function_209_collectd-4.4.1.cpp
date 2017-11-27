static int csnmp_config_add_data_table (data_definition_t *dd, oconfig_item_t *ci)
{
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN))
  {
    WARNING ("snmp plugin: `Table' needs exactly one boolean argument.");
    return (-1);
  }

  dd->is_table = ci->values[0].value.boolean ? 1 : 0;

  return (0);
}