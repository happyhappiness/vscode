static int fc_config_add_dir_recursive (fc_directory_conf_t *dir,
    oconfig_item_t *ci)
{
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN))
  {
    WARNING ("filecount plugin: The `Recursive' config options needs exactly "
        "one boolean argument.");
    return (-1);
  }

  if (ci->values[0].value.boolean)
    dir->options |= FC_RECURSIVE;
  else
    dir->options &= ~FC_RECURSIVE;

  return (0);
}