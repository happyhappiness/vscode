static int fc_config_add_dir_instance (fc_directory_conf_t *dir,
    oconfig_item_t *ci)
{
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("filecount plugin: The `Instance' config option needs exactly "
        "one string argument.");
    return (-1);
  }

  return (fc_config_set_instance (dir, ci->values[0].value.string));
}