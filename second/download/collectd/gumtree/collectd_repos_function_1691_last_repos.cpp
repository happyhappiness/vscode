static int snmp_agent_config_table_index_oid(table_definition_t *td,
                                             oconfig_item_t *ci) {

  if (ci->values_num < 1) {
    WARNING(PLUGIN_NAME ": `IndexOID' is empty");
    return -EINVAL;
  }

  if (ci->values[0].type != OCONFIG_TYPE_STRING) {
    WARNING(PLUGIN_NAME ": `IndexOID' needs only string argument");
    return -EINVAL;
  }

  td->index_oid.oid_len = MAX_OID_LEN;

  if (NULL == snmp_parse_oid(ci->values[0].value.string, td->index_oid.oid,
                             &td->index_oid.oid_len)) {
    ERROR(PLUGIN_NAME ": Failed to parse table index OID (%s)",
          ci->values[0].value.string);
    td->index_oid.oid_len = 0;
    return -EINVAL;
  }

  return 0;
}