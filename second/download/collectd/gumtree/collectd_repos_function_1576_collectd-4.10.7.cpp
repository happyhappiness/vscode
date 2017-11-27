static int ut_config_type_persist (threshold_t *th, oconfig_item_t *ci)
{
  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN))
  {
    WARNING ("threshold values: The `Persist' option needs exactly one "
	"boolean argument.");
    return (-1);
  }

  if (ci->values[0].value.boolean)
    th->flags |= UT_FLAG_PERSIST;
  else
    th->flags &= ~UT_FLAG_PERSIST;

  return (0);
}