static int fc_config_add_dir_option(fc_directory_conf_t *dir,
                                    oconfig_item_t *ci, int bit) {
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN)) {
    WARNING("filecount plugin: The `Recursive' config options needs exactly "
            "one boolean argument.");
    return (-1);
  }

  if (ci->values[0].value.boolean)
    dir->options |= bit;
  else
    dir->options &= ~bit;

  return (0);
}