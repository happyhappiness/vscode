static int csnmp_config_add_data_type (data_definition_t *dd, oconfig_item_t *ci)
{
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("snmp plugin: `Type' needs exactly one string argument.");
    return (-1);
  }

  sfree (dd->type);
  dd->type = strdup (ci->values[0].value.string);
  if (dd->type == NULL)
    return (-1);

  return (0);
}