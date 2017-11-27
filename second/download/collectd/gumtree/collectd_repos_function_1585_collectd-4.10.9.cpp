static int ut_config_type_percentage(threshold_t *th, oconfig_item_t *ci)
{
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN))
  {
    WARNING ("threshold values: The `Percentage' option needs exactly one "
	"boolean argument.");
    return (-1);
  }

  if (ci->values[0].value.boolean)
    th->flags |= UT_FLAG_PERCENTAGE;
  else
    th->flags &= ~UT_FLAG_PERCENTAGE;

  return (0);
}