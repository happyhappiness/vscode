static int udb_config_set_string (char **ret_string, /* {{{ */
    oconfig_item_t *ci)
{
  char *string;

  if ((ci->values_num != 1)
      || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("db query utils: The `%s' config option "
        "needs exactly one string argument.", ci->key);
    return (-1);
  }

  string = strdup (ci->values[0].value.string);
  if (string == NULL)
  {
    ERROR ("db query utils: strdup failed.");
    return (-1);
  }

  if (*ret_string != NULL)
    free (*ret_string);
  *ret_string = string;

  return (0);
}