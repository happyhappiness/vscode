static int snmp_agent_write(value_list_t const *vl) {

  if (vl == NULL)
    return -EINVAL;

  for (llentry_t *te = llist_head(g_agent->tables); te != NULL; te = te->next) {
    table_definition_t *td = te->value;

    for (llentry_t *de = llist_head(td->columns); de != NULL; de = de->next) {
      data_definition_t *dd = de->value;

      if (!dd->is_instance) {
        if (CHECK_DD_TYPE(dd, vl->plugin, vl->plugin_instance, vl->type,
                          vl->type_instance)) {
          snmp_agent_update_index(td, vl->plugin_instance);
          return 0;
        }
      }
    }
  }

  return 0;
}