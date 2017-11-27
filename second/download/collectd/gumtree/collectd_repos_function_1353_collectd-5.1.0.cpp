static int ut_config_type (const threshold_t *th_orig, oconfig_item_t *ci)
{
  int i;
  threshold_t th;
  int status = 0;

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("threshold values: The `Type' block needs exactly one string "
	"argument.");
    return (-1);
  }

  if (ci->children_num < 1)
  {
    WARNING ("threshold values: The `Type' block needs at least one option.");
    return (-1);
  }

  memcpy (&th, th_orig, sizeof (th));
  sstrncpy (th.type, ci->values[0].value.string, sizeof (th.type));

  th.warning_min = NAN;
  th.warning_max = NAN;
  th.failure_min = NAN;
  th.failure_max = NAN;
  th.hits = 0;
  th.hysteresis = 0;
  th.flags = UT_FLAG_INTERESTING; /* interesting by default */

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *option = ci->children + i;
    status = 0;

    if (strcasecmp ("Instance", option->key) == 0)
      status = ut_config_type_instance (&th, option);
    else if (strcasecmp ("DataSource", option->key) == 0)
      status = ut_config_type_datasource (&th, option);
    else if ((strcasecmp ("WarningMax", option->key) == 0)
	|| (strcasecmp ("FailureMax", option->key) == 0))
      status = ut_config_type_max (&th, option);
    else if ((strcasecmp ("WarningMin", option->key) == 0)
	|| (strcasecmp ("FailureMin", option->key) == 0))
      status = ut_config_type_min (&th, option);
    else if (strcasecmp ("Interesting", option->key) == 0)
      status = cf_util_get_flag (option, &th.flags, UT_FLAG_INTERESTING);
    else if (strcasecmp ("Invert", option->key) == 0)
      status = cf_util_get_flag (option, &th.flags, UT_FLAG_INVERT);
    else if (strcasecmp ("Persist", option->key) == 0)
      status = cf_util_get_flag (option, &th.flags, UT_FLAG_PERSIST);
    else if (strcasecmp ("PersistOK", option->key) == 0)
      status = cf_util_get_flag (option, &th.flags, UT_FLAG_PERSIST_OK);
    else if (strcasecmp ("Percentage", option->key) == 0)
      status = cf_util_get_flag (option, &th.flags, UT_FLAG_PERCENTAGE);
    else if (strcasecmp ("Hits", option->key) == 0)
      status = ut_config_type_hits (&th, option);
    else if (strcasecmp ("Hysteresis", option->key) == 0)
      status = ut_config_type_hysteresis (&th, option);
    else
    {
      WARNING ("threshold values: Option `%s' not allowed inside a `Type' "
	  "block.", option->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  if (status == 0)
  {
    status = ut_threshold_add (&th);
  }

  return (status);
}