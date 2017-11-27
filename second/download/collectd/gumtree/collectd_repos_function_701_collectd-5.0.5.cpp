static int bind_config (oconfig_item_t *ci) /* {{{ */
{
  int i;

  for (i = 0; i < ci->children_num; i++)
  {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp ("Url", child->key) == 0) {
      if ((child->values_num != 1) || (child->values[0].type != OCONFIG_TYPE_STRING))
      {
        WARNING ("bind plugin: The `Url' option needs "
                 "exactly one string argument.");
        return (-1);
      }

      url = strdup (child->values[0].value.string);
    } else if (strcasecmp ("OpCodes", child->key) == 0)
      bind_config_set_bool ("OpCodes", &global_opcodes, child);
    else if (strcasecmp ("QTypes", child->key) == 0)
      bind_config_set_bool ("QTypes", &global_qtypes, child);
    else if (strcasecmp ("ServerStats", child->key) == 0)
      bind_config_set_bool ("ServerStats", &global_server_stats, child);
    else if (strcasecmp ("ZoneMaintStats", child->key) == 0)
      bind_config_set_bool ("ZoneMaintStats", &global_zone_maint_stats, child);
    else if (strcasecmp ("ResolverStats", child->key) == 0)
      bind_config_set_bool ("ResolverStats", &global_resolver_stats, child);
    else if (strcasecmp ("MemoryStats", child->key) == 0)
      bind_config_set_bool ("MemoryStats", &global_memory_stats, child);
    else if (strcasecmp ("View", child->key) == 0)
      bind_config_add_view (child);
    else
    {
      WARNING ("bind plugin: Unknown configuration option "
          "`%s' will be ignored.", child->key);
    }
  }

  return (0);
}