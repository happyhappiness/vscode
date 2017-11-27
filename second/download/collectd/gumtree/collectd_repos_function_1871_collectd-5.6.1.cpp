static int mb_config (oconfig_item_t *ci) /* {{{ */
{
  if (ci == NULL)
    return (EINVAL);

  for (int i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Data", child->key) == 0)
      mb_config_add_data (child);
    else if (strcasecmp ("Host", child->key) == 0)
      mb_config_add_host (child);
    else
      ERROR ("Modbus plugin: Unknown configuration option: %s", child->key);
  }

  return (0);
}