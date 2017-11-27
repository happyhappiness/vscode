int ut_config (const oconfig_item_t *ci)
{
  int i;
  int status = 0;

  threshold_t th;

  if (ci->values_num != 0)
  {
    ERROR ("threshold values: The `Threshold' block may not have any "
	"arguments.");
    return (-1);
  }

  if (threshold_tree == NULL)
  {
    threshold_tree = c_avl_create ((void *) strcmp);
    if (threshold_tree == NULL)
    {
      ERROR ("ut_config: c_avl_create failed.");
      return (-1);
    }
  }

  memset (&th, '\0', sizeof (th));
  th.warning_min = NAN;
  th.warning_max = NAN;
  th.failure_min = NAN;
  th.failure_max = NAN;

  th.hits = 0;
  th.hysteresis = 0;
    
  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;
    status = 0;

    if (strcasecmp ("Type", option->key) == 0)
      status = ut_config_type (&th, option);
    else if (strcasecmp ("Plugin", option->key) == 0)
      status = ut_config_plugin (&th, option);
    else if (strcasecmp ("Host", option->key) == 0)
      status = ut_config_host (&th, option);
    else
    {
      WARNING ("threshold values: Option `%s' not allowed here.", option->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  return (status);
}