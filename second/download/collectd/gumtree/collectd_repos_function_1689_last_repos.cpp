static int snmp_agent_config_data_oids(data_definition_t *dd,
                                       oconfig_item_t *ci) {
  if (ci->values_num < 1) {
    WARNING(PLUGIN_NAME ": `OIDs' needs at least one argument");
    return -EINVAL;
  }

  for (int i = 0; i < ci->values_num; i++)
    if (ci->values[i].type != OCONFIG_TYPE_STRING) {
      WARNING(PLUGIN_NAME ": `OIDs' needs only string argument");
      return -EINVAL;
    }

  if (dd->oids != NULL)
    sfree(dd->oids);
  dd->oids_len = 0;
  dd->oids = calloc(ci->values_num, sizeof(*dd->oids));
  if (dd->oids == NULL)
    return -ENOMEM;
  dd->oids_len = (size_t)ci->values_num;

  for (int i = 0; i < ci->values_num; i++) {
    dd->oids[i].oid_len = MAX_OID_LEN;

    if (NULL == snmp_parse_oid(ci->values[i].value.string, dd->oids[i].oid,
                               &dd->oids[i].oid_len)) {
      ERROR(PLUGIN_NAME ": snmp_parse_oid (%s) failed",
            ci->values[i].value.string);
      sfree(dd->oids);
      dd->oids_len = 0;
      return -1;
    }
  }

  return 0;
}