static int tcsv_submit(instance_definition_t *id, metric_definition_t *md,
                       value_t v, cdtime_t t) {
  /* Registration variables */
  value_list_t vl = VALUE_LIST_INIT;

  /* Register */
  vl.values_len = 1;
  vl.values = &v;

  sstrncpy(vl.plugin, (id->plugin_name != NULL) ? id->plugin_name : "tail_csv",
           sizeof(vl.plugin));
  if (id->instance != NULL)
    sstrncpy(vl.plugin_instance, id->instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, md->type, sizeof(vl.type));
  if (md->instance != NULL)
    sstrncpy(vl.type_instance, md->instance, sizeof(vl.type_instance));

  vl.time = t;
  vl.interval = id->interval;

  return plugin_dispatch_values(&vl);
}