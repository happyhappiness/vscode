static int ut_config_type_invert (threshold_t *th, oconfig_item_t *ci)
{
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN))
  {
    WARNING ("threshold values: The `Invert' option needs exactly one "
	"boolean argument.");
    return (-1);
  }

  if (ci->values[0].value.boolean)
    th->flags |= UT_FLAG_INVERT;
  else
    th->flags &= ~UT_FLAG_INVERT;

  return (0);
}