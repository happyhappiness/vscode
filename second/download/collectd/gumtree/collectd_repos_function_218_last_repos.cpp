static int rdt_config(oconfig_item_t *ci) {
  if (rdt_preinit() != 0) {
    g_state = CONFIGURATION_ERROR;
    /* if we return -1 at this point collectd
      reports a failure in configuration and
      aborts
    */
    return (0);
  }

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Cores", child->key) == 0) {
      if (rdt_config_cgroups(child) != 0) {
        g_state = CONFIGURATION_ERROR;
        /* if we return -1 at this point collectd
           reports a failure in configuration and
           aborts
         */
        return (0);
      }

#if COLLECT_DEBUG
      rdt_dump_cgroups();
#endif /* COLLECT_DEBUG */
    } else {
      ERROR(RDT_PLUGIN ": Unknown configuration parameter \"%s\".", child->key);
    }
  }

  return 0;
}