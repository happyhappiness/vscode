static char *metric_family_name(data_set_t const *ds, value_list_t const *vl,
                                size_t ds_index) {
  char const *fields[5] = {"collectd"};
  size_t fields_num = 1;

  if (strcmp(vl->plugin, vl->type) != 0) {
    fields[fields_num] = vl->plugin;
    fields_num++;
  }
  fields[fields_num] = vl->type;
  fields_num++;

  if (strcmp("value", ds->ds[ds_index].name) != 0) {
    fields[fields_num] = ds->ds[ds_index].name;
    fields_num++;
  }

  /* Prometheus best practices:
   * cumulative metrics should have a "total" suffix. */
  if ((ds->ds[ds_index].type == DS_TYPE_COUNTER) ||
      (ds->ds[ds_index].type == DS_TYPE_DERIVE)) {
    fields[fields_num] = "total";
    fields_num++;
  }

  char name[5 * DATA_MAX_NAME_LEN];
  strjoin(name, sizeof(name), (char **)fields, fields_num, "_");
  return strdup(name);
}