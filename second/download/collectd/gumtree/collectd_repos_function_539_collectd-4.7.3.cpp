static int fc_config (oconfig_item_t *ci)
{
  int i;

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp ("Directory", child->key) == 0)
      fc_config_add_dir (child);
    else
    {
      WARNING ("filecount plugin: Ignoring unknown config option `%s'.",
          child->key);
    }
  } /* for (ci->children) */

  return (0);
}