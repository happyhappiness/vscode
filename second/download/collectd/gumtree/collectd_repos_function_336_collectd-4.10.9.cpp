static int csnmp_config_add_data_instance (data_definition_t *dd, oconfig_item_t *ci)
{
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("snmp plugin: `Instance' needs exactly one string argument.");
    return (-1);
  }

  if (dd->is_table)
  {
    /* Instance is an OID */
    dd->instance.oid.oid_len = MAX_OID_LEN;

    if (!read_objid (ci->values[0].value.string,
          dd->instance.oid.oid, &dd->instance.oid.oid_len))
    {
      ERROR ("snmp plugin: read_objid (%s) failed.",
          ci->values[0].value.string);
      return (-1);
    }
  }
  else
  {
    /* Instance is a simple string */
    sstrncpy (dd->instance.string, ci->values[0].value.string,
        sizeof (dd->instance.string));
  }

  return (0);
}