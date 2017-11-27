static int gmond_config_set_string(oconfig_item_t *ci, char **str) /* {{{ */
{
  char *tmp;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("gmond plugin: The `%s' option needs "
            "exactly one string argument.",
            ci->key);
    return (-1);
  }

  tmp = strdup(ci->values[0].value.string);
  if (tmp == NULL) {
    ERROR("gmond plugin: strdup failed.");
    return (-1);
  }

  sfree(*str);
  *str = tmp;
  return (0);
}