static void ps_tune_instance(oconfig_item_t *ci, procstat_t *ps) {
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *c = ci->children + i;

    if (strcasecmp(c->key, "CollectContextSwitch") == 0)
      cf_util_get_boolean(c, &ps->report_ctx_switch);
    else if (strcasecmp(c->key, "CollectFileDescriptor") == 0)
      cf_util_get_boolean(c, &ps->report_fd_num);
    else if (strcasecmp(c->key, "CollectMemoryMaps") == 0)
      cf_util_get_boolean(c, &ps->report_maps_num);
    else {
      ERROR("processes plugin: Option `%s' not allowed here.", c->key);
    }
  } /* for (ci->children) */
}