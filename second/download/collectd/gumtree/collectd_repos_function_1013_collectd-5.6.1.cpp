static int cc_config (oconfig_item_t *ci) /* {{{ */
{
  int success;
  int errors;
  int status;

  success = 0;
  errors = 0;

  for (int i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Page", child->key) == 0)
    {
      status = cc_config_add_page (child);
      if (status == 0)
        success++;
      else
        errors++;
    }
    else
    {
      WARNING ("curl plugin: Option `%s' not allowed here.", child->key);
      errors++;
    }
  }

  if ((success == 0) && (errors > 0))
  {
    ERROR ("curl plugin: All statements failed.");
    return (-1);
  }

  return (0);
}