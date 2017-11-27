static void fc_submit_dir(const fc_directory_conf_t *dir) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = (gauge_t)dir->files_num};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "filecount", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, dir->instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "files", sizeof(vl.type));

  plugin_dispatch_values(&vl);

  vl.values = &(value_t){.gauge = (gauge_t)dir->files_size};
  sstrncpy(vl.type, "bytes", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}