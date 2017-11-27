static int csnmp_config_add_data_instance_prefix (data_definition_t *dd,
    oconfig_item_t *ci)
{
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("snmp plugin: `InstancePrefix' needs exactly one string argument.");
    return (-1);
  }

  if (!dd->is_table)
  {
    WARNING ("snmp plugin: data %s: InstancePrefix is ignored when `Table' "
        "is set to `false'.", dd->name);
    return (-1);
  }

  sfree (dd->instance_prefix);
  dd->instance_prefix = strdup (ci->values[0].value.string);
  if (dd->instance_prefix == NULL)
    return (-1);

  return (0);
}