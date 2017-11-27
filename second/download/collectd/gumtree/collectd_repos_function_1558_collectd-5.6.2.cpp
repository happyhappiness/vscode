static int c_notify_config(oconfig_item_t *ci) {
  for (int i = 0; i < ci->children_num; ++i) {
    oconfig_item_t *c = ci->children + i;

    if (0 == strcasecmp(c->key, "OkayTimeout"))
      set_timeout(c, &okay_timeout);
    else if (0 == strcasecmp(c->key, "WarningTimeout"))
      set_timeout(c, &warn_timeout);
    else if (0 == strcasecmp(c->key, "FailureTimeout"))
      set_timeout(c, &fail_timeout);
  }
  return 0;
}