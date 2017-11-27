static int cj_config_add_string (const char *name, char **dest, /* {{{ */
                                      oconfig_item_t *ci)
{
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING))
  {
    WARNING ("curl_json plugin: `%s' needs exactly one string argument.", name);
    return (-1);
  }

  sfree (*dest);
  *dest = strdup (ci->values[0].value.string);
  if (*dest == NULL)
    return (-1);

  return (0);
}