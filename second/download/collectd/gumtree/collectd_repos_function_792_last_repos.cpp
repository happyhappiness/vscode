static int fc_config_add_dir(oconfig_item_t *ci) {
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("filecount plugin: `Directory' needs exactly one string "
            "argument.");
    return -1;
  }

  /* Initialize `dir' */
  fc_directory_conf_t *dir = calloc(1, sizeof(*dir));
  if (dir == NULL) {
    ERROR("filecount plugin: calloc failed.");
    return -1;
  }

  dir->path = strdup(ci->values[0].value.string);
  if (dir->path == NULL) {
    ERROR("filecount plugin: strdup failed.");
    fc_free_dir(dir);
    return -1;
  }

  dir->options = FC_RECURSIVE | FC_REGULAR;

  dir->name = NULL;
  dir->plugin_name = strdup("filecount");
  dir->instance = NULL;
  dir->type_instance = NULL;
  dir->mtime = 0;
  dir->size = 0;

  dir->files_size_type = strdup("bytes");
  dir->files_num_type = strdup("files");

  if (dir->plugin_name == NULL || dir->files_size_type == NULL ||
      dir->files_num_type == NULL) {
    ERROR("filecount plugin: strdup failed.");
    fc_free_dir(dir);
    return -1;
  }

  int status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp("Plugin", option->key) == 0)
      status = cf_util_get_string(option, &dir->plugin_name);
    else if (strcasecmp("Instance", option->key) == 0)
      status = fc_config_add_dir_instance(dir, option);
    else if (strcasecmp("Name", option->key) == 0)
      status = fc_config_add_dir_name(dir, option);
    else if (strcasecmp("MTime", option->key) == 0)
      status = fc_config_add_dir_mtime(dir, option);
    else if (strcasecmp("Size", option->key) == 0)
      status = fc_config_add_dir_size(dir, option);
    else if (strcasecmp("Recursive", option->key) == 0)
      status = fc_config_add_dir_option(dir, option, FC_RECURSIVE);
    else if (strcasecmp("IncludeHidden", option->key) == 0)
      status = fc_config_add_dir_option(dir, option, FC_HIDDEN);
    else if (strcasecmp("RegularOnly", option->key) == 0)
      status = fc_config_add_dir_option(dir, option, FC_REGULAR);
    else if (strcasecmp("FilesSizeType", option->key) == 0)
      status = cf_util_get_string(option, &dir->files_size_type);
    else if (strcasecmp("FilesCountType", option->key) == 0)
      status = cf_util_get_string(option, &dir->files_num_type);
    else if (strcasecmp("TypeInstance", option->key) == 0)
      status = cf_util_get_string(option, &dir->type_instance);
    else {
      WARNING("filecount plugin: fc_config_add_dir: "
              "Option `%s' not allowed here.",
              option->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (ci->children) */

  if (status != 0) {
    fc_free_dir(dir);
    return -1;
  }

  /* Set default plugin instance */
  if (dir->instance == NULL) {
    fc_config_set_instance(dir, dir->path);
    if (dir->instance == NULL || strlen(dir->instance) == 0) {
      ERROR("filecount plugin: failed to build plugin instance name.");
      fc_free_dir(dir);
      return -1;
    }
  }

  /* Handle disabled types */
  if (strlen(dir->instance) == 0)
    sfree(dir->instance);

  if (strlen(dir->files_size_type) == 0)
    sfree(dir->files_size_type);

  if (strlen(dir->files_num_type) == 0)
    sfree(dir->files_num_type);

  if (dir->files_size_type == NULL && dir->files_num_type == NULL) {
    WARNING("filecount plugin: Both `FilesSizeType' and `FilesCountType ' "
            "are disabled for '%s'. There's no types to report.",
            dir->path);
    fc_free_dir(dir);
    return -1;
  }

  /* Ready to add it to list */
  fc_directory_conf_t **temp =
      realloc(directories, sizeof(*directories) * (directories_num + 1));
  if (temp == NULL) {
    ERROR("filecount plugin: realloc failed.");
    fc_free_dir(dir);
    return -1;
  }

  directories = temp;
  directories[directories_num] = dir;
  directories_num++;

  return 0;
}