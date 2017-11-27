static void submit(const char *type, const char *type_instance, value_t *values,
                   size_t values_len, mysql_database_t *db) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = values;
  vl.values_len = values_len;

  set_host(db, vl.host, sizeof(vl.host));

  sstrncpy(vl.plugin, "mysql", sizeof(vl.plugin));

  /* Assured by "mysql_config_database" */
  assert(db->instance != NULL);
  sstrncpy(vl.plugin_instance, db->instance, sizeof(vl.plugin_instance));

  sstrncpy(vl.type, type, sizeof(vl.type));
  if (type_instance != NULL)
    sstrncpy(vl.type_instance, type_instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}