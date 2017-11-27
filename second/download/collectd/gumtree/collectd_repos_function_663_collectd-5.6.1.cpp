static int cjni_config_perform (oconfig_item_t *ci) /* {{{ */
{
  int success;
  int errors;
  int status;

  success = 0;
  errors = 0;

  for (int i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("JVMArg", child->key) == 0)
    {
      status = cjni_config_add_jvm_arg (child);
      if (status == 0)
        success++;
      else
        errors++;
    }
    else if (strcasecmp ("LoadPlugin", child->key) == 0)
    {
      status = cjni_config_load_plugin (child);
      if (status == 0)
        success++;
      else
        errors++;
    }
    else if (strcasecmp ("Plugin", child->key) == 0)
    {
      status = cjni_config_plugin_block (child);
      if (status == 0)
        success++;
      else
        errors++;
    }
    else
    {
      WARNING ("java plugin: Option `%s' not allowed here.", child->key);
      errors++;
    }
  }

  DEBUG ("java plugin: jvm_argc = %zu;", jvm_argc);
  DEBUG ("java plugin: java_classes_list_len = %zu;", java_classes_list_len);

  if ((success == 0) && (errors > 0))
  {
    ERROR ("java plugin: All statements failed.");
    return (-1);
  }

  return (0);
}