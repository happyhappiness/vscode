static int ut_config_type_max (threshold_t *th, oconfig_item_t *ci)
{
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_NUMBER))
  {
    WARNING ("threshold values: The `%s' option needs exactly one "
	"number argument.", ci->key);
    return (-1);
  }

  if (strcasecmp (ci->key, "WarningMax") == 0)
    th->warning_max = ci->values[0].value.number;
  else
    th->failure_max = ci->values[0].value.number;

  return (0);
}