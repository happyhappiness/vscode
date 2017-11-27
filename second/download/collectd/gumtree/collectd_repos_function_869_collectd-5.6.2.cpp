static int ethstat_config(oconfig_item_t *ci) /* {{{ */
{
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Interface", child->key) == 0)
      ethstat_add_interface(child);
    else if (strcasecmp("Map", child->key) == 0)
      ethstat_add_map(child);
    else if (strcasecmp("MappedOnly", child->key) == 0)
      (void)cf_util_get_boolean(child, &collect_mapped_only);
    else
      WARNING("ethstat plugin: The config option \"%s\" is unknown.",
              child->key);
  }

  return (0);
}