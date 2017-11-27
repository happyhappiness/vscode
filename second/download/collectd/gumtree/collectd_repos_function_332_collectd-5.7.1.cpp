static int rdt_config(oconfig_item_t *ci) {
  int ret = 0;

  ret = rdt_preinit();
  if (ret != 0)
    return ret;

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Cores", child->key) == 0) {

      ret = rdt_config_cgroups(child);
      if (ret != 0)
        return ret;

#if COLLECT_DEBUG
      rdt_dump_cgroups();
#endif /* COLLECT_DEBUG */

    } else {
      ERROR(RDT_PLUGIN ": Unknown configuration parameter \"%s\".", child->key);
    }
  }

  return (0);
}