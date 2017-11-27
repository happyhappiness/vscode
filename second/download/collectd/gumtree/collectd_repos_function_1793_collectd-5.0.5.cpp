static int ts_config_add_string (char **dest, /* {{{ */
    const oconfig_item_t *ci, int may_be_empty)
{
  char *temp;

  if (dest == NULL)
    return (-EINVAL);

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    ERROR ("Target `set': The `%s' option requires exactly one string "
        "argument.", ci->key);
    return (-1);
  }

  if ((!may_be_empty) && (ci->values[0].value.string[0] == 0))
  {
    ERROR ("Target `set': The `%s' option does not accept empty strings.",
        ci->key);
    return (-1);
  }

  temp = ts_strdup (ci->values[0].value.string);
  if (temp == NULL)
  {
    ERROR ("ts_config_add_string: ts_strdup failed.");
    return (-1);
  }

  free (*dest);
  *dest = temp;

  return (0);
}