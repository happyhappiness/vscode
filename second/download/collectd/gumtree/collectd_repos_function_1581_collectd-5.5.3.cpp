static int ut_config_host (const threshold_t *th_orig, oconfig_item_t *ci)
{
  int i;
  threshold_t th;
  int status = 0;

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("threshold values: The `Host' block needs exactly one string "
	"argument.");
    return (-1);
  }

  if (ci->children_num < 1)
  {
    WARNING ("threshold values: The `Host' block needs at least one nested "
	"block.");
    return (-1);
  }

  memcpy (&th, th_orig, sizeof (th));
  sstrncpy (th.host, ci->values[0].value.string, sizeof (th.host));

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;

    if (strcasecmp ("Type", option->key) == 0)
      status = ut_config_type (&th, option);
    else if (strcasecmp ("Plugin", option->key) == 0)
      status = ut_config_plugin (&th, option);
    else
    {
      WARNING ("threshold values: Option `%s' not allowed inside a `Host' "
	  "block.", option->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  return (status);
}