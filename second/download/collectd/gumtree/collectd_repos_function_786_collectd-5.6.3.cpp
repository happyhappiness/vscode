static int fc_config_add_dir_name(fc_directory_conf_t *dir,
                                  oconfig_item_t *ci) {
  char *temp;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("filecount plugin: The `Name' config option needs exactly one "
            "string argument.");
    return (-1);
  }

  temp = strdup(ci->values[0].value.string);
  if (temp == NULL) {
    ERROR("filecount plugin: strdup failed.");
    return (-1);
  }

  sfree(dir->name);
  dir->name = temp;

  return (0);
}