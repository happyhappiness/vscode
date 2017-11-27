static const char *config_get_string (oconfig_item_t *ci)
{
  if ((ci->children_num != 0) || (ci->values_num != 1)
      || ((ci->values[0].type != OCONFIG_TYPE_STRING)
        && (ci->values[0].type != OCONFIG_TYPE_BOOLEAN)))
  {
    ERROR ("rrdcached plugin: %s expects a single string argument.",
        ci->key);
    return (NULL);
  }

  if (ci->values[0].type == OCONFIG_TYPE_BOOLEAN) {
    if (ci->values[0].value.boolean)
      return "true";
    else
      return "false";
  }
  return (ci->values[0].value.string);
}