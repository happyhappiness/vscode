static int cj_config_set_boolean (const char *name, int *dest, /* {{{ */
                                       oconfig_item_t *ci)
{
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_BOOLEAN))
  {
    WARNING ("curl_json plugin: `%s' needs exactly one boolean argument.", name);
    return (-1);
  }

  *dest = ci->values[0].value.boolean ? 1 : 0;

  return (0);
}