void fc_free_dir(fc_directory_conf_t *dir) {
  sfree(dir->path);
  sfree(dir->plugin_name);
  sfree(dir->instance);
  sfree(dir->files_size_type);
  sfree(dir->files_num_type);
  sfree(dir->type_instance);
  sfree(dir->name);

  sfree(dir);
}