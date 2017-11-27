static int tbl_result_dispatch(tbl_t *tbl, tbl_result_t *res, char **fields,
                               size_t fields_num) {
  value_list_t vl = VALUE_LIST_INIT;
  value_t values[res->values_num];

  assert(NULL != res->ds);
  assert(res->values_num == res->ds->ds_num);

  for (size_t i = 0; i < res->values_num; ++i) {
    char *value;

    assert(res->values[i] < fields_num);
    value = fields[res->values[i]];

    if (0 != parse_value(value, &values[i], res->ds->ds[i].type))
      return -1;
  }

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);

  sstrncpy(vl.plugin, "table", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, tbl->instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, res->type, sizeof(vl.type));

  if (0 == res->instances_num) {
    if (NULL != res->instance_prefix)
      sstrncpy(vl.type_instance, res->instance_prefix,
               sizeof(vl.type_instance));
  } else {
    char *instances[res->instances_num];
    char instances_str[DATA_MAX_NAME_LEN];

    for (size_t i = 0; i < res->instances_num; ++i) {
      assert(res->instances[i] < fields_num);
      instances[i] = fields[res->instances[i]];
    }

    strjoin(instances_str, sizeof(instances_str), instances,
            STATIC_ARRAY_SIZE(instances), "-");
    instances_str[sizeof(instances_str) - 1] = '\0';

    vl.type_instance[sizeof(vl.type_instance) - 1] = '\0';
    if (NULL == res->instance_prefix)
      strncpy(vl.type_instance, instances_str, sizeof(vl.type_instance));
    else
      snprintf(vl.type_instance, sizeof(vl.type_instance), "%s-%s",
               res->instance_prefix, instances_str);

    if ('\0' != vl.type_instance[sizeof(vl.type_instance) - 1]) {
      vl.type_instance[sizeof(vl.type_instance) - 1] = '\0';
      log_warn("Truncated type instance: %s.", vl.type_instance);
    }
  }

  plugin_dispatch_values(&vl);
  return 0;
}