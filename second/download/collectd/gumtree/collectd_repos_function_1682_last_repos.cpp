static int snmp_agent_form_reply(struct netsnmp_request_info_s *requests,
                                 data_definition_t *dd, char *instance,
                                 int oid_index) {
  char name[DATA_MAX_NAME_LEN];
  format_name(name, sizeof(name), hostname_g, dd->plugin,
              instance ? instance : dd->plugin_instance, dd->type,
              dd->type_instance);
  DEBUG(PLUGIN_NAME ": Identifier '%s'", name);

  value_t *values;
  size_t values_num;
  const data_set_t *ds = plugin_get_ds(dd->type);
  if (ds == NULL) {
    ERROR(PLUGIN_NAME ": Data set not found for '%s' type", dd->type);
    return SNMP_NOSUCHINSTANCE;
  }

  int ret = uc_get_value_by_name(name, &values, &values_num);

  if (ret != 0) {
    ERROR(PLUGIN_NAME ": Failed to get value for '%s'", name);
    return SNMP_NOSUCHINSTANCE;
  }

  assert(ds->ds_num == values_num);
  assert(oid_index < (int)values_num);

  char data[DATA_MAX_NAME_LEN];
  size_t data_len = sizeof(data);
  ret = snmp_agent_set_vardata(
      data, &data_len, dd->oids[oid_index].type, dd->scale, dd->shift,
      &values[oid_index], sizeof(values[oid_index]), ds->ds[oid_index].type);

  sfree(values);

  if (ret != 0) {
    ERROR(PLUGIN_NAME ": Failed to convert '%s' value to snmp data", name);
    return SNMP_NOSUCHINSTANCE;
  }

  requests->requestvb->type = dd->oids[oid_index].type;
  snmp_set_var_typed_value(requests->requestvb, requests->requestvb->type,
                           (const u_char *)data, data_len);

  return SNMP_ERR_NOERROR;
}