static int fc_config_add_dir(oconfig_item_t *ci) {
  fc_directory_conf_t *dir;
  int status;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("filecount plugin: `Directory' needs exactly one string "
            "argument.");
    return (-1);
  }

  /* Initialize `dir' */
  dir = calloc(1, sizeof(*dir));
  if (dir == NULL) {
    ERROR("filecount plugin: calloc failed.");
    return (-1);
  }

  dir->path = strdup(ci->values[0].value.string);
  if (dir->path == NULL) {
    ERROR("filecount plugin: strdup failed.");
    sfree(dir);
    return (-1);
  }

  fc_config_set_instance(dir, dir->path);

  dir->options = FC_RECURSIVE;

  dir->name = NULL;
  dir->mtime = 0;
  dir->size = 0;

  status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp("Instance", option->key) == 0)
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
    else {
      WARNING("filecount plugin: fc_config_add_dir: "
              "Option `%s' not allowed here.",
              option->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (ci->children) */

  if (status == 0) {
    fc_directory_conf_t **temp;

    temp = realloc(directories, sizeof(*directories) * (directories_num + 1));
    if (temp == NULL) {
      ERROR("filecount plugin: realloc failed.");
      status = -1;
    } else {
      directories = temp;
      directories[directories_num] = dir;
      directories_num++;
    }
  }

  if (status != 0) {
    sfree(dir->name);
    sfree(dir->instance);
    sfree(dir->path);
    sfree(dir);
    return (-1);
  }

  return (0);
}