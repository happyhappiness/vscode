static void snmp_agent_dump_data(void) {
#if COLLECT_DEBUG
  char oid_str[DATA_MAX_NAME_LEN];

  for (llentry_t *te = llist_head(g_agent->tables); te != NULL; te = te->next) {
    table_definition_t *td = te->value;

    DEBUG(PLUGIN_NAME ": Table:");
    DEBUG(PLUGIN_NAME ":   Name: %s", td->name);
    if (td->index_oid.oid_len != 0) {
      snmp_agent_oid_to_string(oid_str, sizeof(oid_str), &td->index_oid);
      DEBUG(PLUGIN_NAME ":   IndexOID: %s", oid_str);
    }
    if (td->size_oid.oid_len != 0) {
      snmp_agent_oid_to_string(oid_str, sizeof(oid_str), &td->size_oid);
      DEBUG(PLUGIN_NAME ":   SizeOID: %s", oid_str);
    }

    for (llentry_t *de = llist_head(td->columns); de != NULL; de = de->next) {
      data_definition_t *dd = de->value;

      DEBUG(PLUGIN_NAME ":   Column:");
      DEBUG(PLUGIN_NAME ":     Name: %s", dd->name);
      if (dd->plugin)
        DEBUG(PLUGIN_NAME ":     Plugin: %s", dd->plugin);
      if (dd->plugin_instance)
        DEBUG(PLUGIN_NAME ":     PluginInstance: %s", dd->plugin_instance);
      if (dd->is_instance)
        DEBUG(PLUGIN_NAME ":     Instance: true");
      if (dd->type)
        DEBUG(PLUGIN_NAME ":     Type: %s", dd->type);
      if (dd->type_instance)
        DEBUG(PLUGIN_NAME ":     TypeInstance: %s", dd->type_instance);
      for (size_t i = 0; i < dd->oids_len; i++) {
        snmp_agent_oid_to_string(oid_str, sizeof(oid_str), &dd->oids[i]);
        DEBUG(PLUGIN_NAME ":     OID[%zu]: %s", i, oid_str);
      }
      DEBUG(PLUGIN_NAME ":   Scale: %g", dd->scale);
      DEBUG(PLUGIN_NAME ":   Shift: %g", dd->shift);
    }
  }

  for (llentry_t *e = llist_head(g_agent->scalars); e != NULL; e = e->next) {
    data_definition_t *dd = e->value;

    DEBUG(PLUGIN_NAME ": Scalar:");
    DEBUG(PLUGIN_NAME ":   Name: %s", dd->name);
    if (dd->plugin)
      DEBUG(PLUGIN_NAME ":   Plugin: %s", dd->plugin);
    if (dd->plugin_instance)
      DEBUG(PLUGIN_NAME ":   PluginInstance: %s", dd->plugin_instance);
    if (dd->is_instance)
      DEBUG(PLUGIN_NAME ":   Instance: true");
    if (dd->type)
      DEBUG(PLUGIN_NAME ":   Type: %s", dd->type);
    if (dd->type_instance)
      DEBUG(PLUGIN_NAME ":   TypeInstance: %s", dd->type_instance);
    for (size_t i = 0; i < dd->oids_len; i++) {
      snmp_agent_oid_to_string(oid_str, sizeof(oid_str), &dd->oids[i]);
      DEBUG(PLUGIN_NAME ":   OID[%zu]: %s", i, oid_str);
    }
    DEBUG(PLUGIN_NAME ":   Scale: %g", dd->scale);
    DEBUG(PLUGIN_NAME ":   Shift: %g", dd->shift);
  }
#endif /* COLLECT_DEBUG */
}