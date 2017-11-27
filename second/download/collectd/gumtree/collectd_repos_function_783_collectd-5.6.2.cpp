static void fc_submit_dir(const fc_directory_conf_t *dir) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge = (gauge_t)dir->files_num;

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "filecount", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, dir->instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "files", sizeof(vl.type));

  plugin_dispatch_values(&vl);

  values[0].gauge = (gauge_t)dir->files_size;
  sstrncpy(vl.type, "bytes", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}