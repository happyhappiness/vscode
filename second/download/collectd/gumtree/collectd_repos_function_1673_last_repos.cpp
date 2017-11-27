static int snmp_agent_validate_data(void) {

  snmp_agent_dump_data();

  for (llentry_t *te = llist_head(g_agent->tables); te != NULL; te = te->next) {
    table_definition_t *td = te->value;

    for (llentry_t *de = llist_head(td->columns); de != NULL; de = de->next) {
      data_definition_t *dd = de->value;

      if (!dd->plugin) {
        ERROR(PLUGIN_NAME ": Plugin not defined for '%s'.'%s'", td->name,
              dd->name);
        return -EINVAL;
      }

      if (dd->plugin_instance) {
        ERROR(PLUGIN_NAME ": PluginInstance should not be defined for table "
                          "data type '%s'.'%s'",
              td->name, dd->name);
        return -EINVAL;
      }

      if (dd->oids_len == 0) {
        ERROR(PLUGIN_NAME ": No OIDs defined for '%s'.'%s'", td->name,
              dd->name);
        return -EINVAL;
      }

      if (dd->is_instance) {

        if (dd->type || dd->type_instance) {
          ERROR(PLUGIN_NAME ": Type and TypeInstance are not valid for "
                            "instance data '%s'.'%s'",
                td->name, dd->name);
          return -EINVAL;
        }

        if (dd->oids_len > 1) {
          ERROR(
              PLUGIN_NAME
              ": Only one OID should be specified for instance data '%s'.'%s'",
              td->name, dd->name);
          return -EINVAL;
        }
      } else {

        if (!dd->type) {
          ERROR(PLUGIN_NAME ": Type not defined for data '%s'.'%s'", td->name,
                dd->name);
          return -EINVAL;
        }
      }
    }
  }

  for (llentry_t *e = llist_head(g_agent->scalars); e != NULL; e = e->next) {
    data_definition_t *dd = e->value;

    if (!dd->plugin) {
      ERROR(PLUGIN_NAME ": Plugin not defined for '%s'", dd->name);
      return -EINVAL;
    }

    if (dd->oids_len == 0) {
      ERROR(PLUGIN_NAME ": No OIDs defined for '%s'", dd->name);
      return -EINVAL;
    }

    if (dd->is_instance) {
      ERROR(PLUGIN_NAME
            ": Instance flag can't be specified for scalar data '%s'",
            dd->name);
      return -EINVAL;
    }

    if (!dd->type) {
      ERROR(PLUGIN_NAME ": Type not defined for data '%s'", dd->name);
      return -EINVAL;
    }
  }

  return 0;
}