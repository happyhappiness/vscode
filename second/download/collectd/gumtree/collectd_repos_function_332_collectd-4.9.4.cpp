static int csnmp_config_add_data_scale (data_definition_t *dd, oconfig_item_t *ci)
{
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_NUMBER))
  {
    WARNING ("snmp plugin: The `Scale' config option needs exactly one number argument.");
    return (-1);
  }

  dd->scale = ci->values[0].value.number;

  return (0);
}