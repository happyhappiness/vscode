static int ut_config_plugin (const threshold_t *th_orig, oconfig_item_t *ci)
{
  int i;
  threshold_t th;
  int status = 0;

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("threshold values: The `Plugin' block needs exactly one string "
	"argument.");
    return (-1);
  }

  if (ci->children_num < 1)
  {
    WARNING ("threshold values: The `Plugin' block needs at least one nested "
	"block.");
    return (-1);
  }

  memcpy (&th, th_orig, sizeof (th));
  sstrncpy (th.plugin, ci->values[0].value.string, sizeof (th.plugin));

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;
    status = 0;

    if (strcasecmp ("Type", option->key) == 0)
      status = ut_config_type (&th, option);
    else if (strcasecmp ("Instance", option->key) == 0)
      status = ut_config_plugin_instance (&th, option);
    else
    {
      WARNING ("threshold values: Option `%s' not allowed inside a `Plugin' "
	  "block.", option->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  return (status);
}