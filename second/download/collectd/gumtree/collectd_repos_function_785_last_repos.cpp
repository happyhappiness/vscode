static void fc_submit_dir(const fc_directory_conf_t *dir) {
  value_list_t vl = VALUE_LIST_INIT;

  sstrncpy(vl.plugin, dir->plugin_name, sizeof(vl.plugin));
  if (dir->instance != NULL)
    sstrncpy(vl.plugin_instance, dir->instance, sizeof(vl.plugin_instance));
  if (dir->type_instance != NULL)
    sstrncpy(vl.type_instance, dir->type_instance, sizeof(vl.type_instance));

  vl.values_len = 1;

  if (dir->files_num_type != NULL) {
    vl.values = &(value_t){.gauge = (gauge_t)dir->files_num};
    sstrncpy(vl.type, dir->files_num_type, sizeof(vl.type));
    plugin_dispatch_values(&vl);
  }

  if (dir->files_size_type != NULL) {
    vl.values = &(value_t){.gauge = (gauge_t)dir->files_size};
    sstrncpy(vl.type, dir->files_size_type, sizeof(vl.type));
    plugin_dispatch_values(&vl);
  }
}