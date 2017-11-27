static int dispatch_loadplugin(oconfig_item_t *ci) {
  const char *name;
  unsigned int flags = 0;
  plugin_ctx_t ctx = {0};
  plugin_ctx_t old_ctx;
  int ret_val;

  assert(strcasecmp(ci->key, "LoadPlugin") == 0);

  if (ci->values_num != 1)
    return (-1);
  if (ci->values[0].type != OCONFIG_TYPE_STRING)
    return (-1);

  name = ci->values[0].value.string;
  if (strcmp("libvirt", name) == 0)
    name = "virt";

  /* default to the global interval set before loading this plugin */
  ctx.interval = cf_get_default_interval();
  ctx.flush_interval = 0;
  ctx.flush_timeout = 0;

  for (int i = 0; i < ci->children_num; ++i) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Globals", child->key) == 0)
      cf_util_get_flag(child, &flags, PLUGIN_FLAGS_GLOBAL);
    else if (strcasecmp("Interval", child->key) == 0)
      cf_util_get_cdtime(child, &ctx.interval);
    else if (strcasecmp("FlushInterval", child->key) == 0)
      cf_util_get_cdtime(child, &ctx.flush_interval);
    else if (strcasecmp("FlushTimeout", child->key) == 0)
      cf_util_get_cdtime(child, &ctx.flush_timeout);
    else {
      WARNING("Ignoring unknown LoadPlugin option \"%s\" "
              "for plugin \"%s\"",
              child->key, ci->values[0].value.string);
    }
  }

  old_ctx = plugin_set_ctx(ctx);
  ret_val = plugin_load(name, (uint32_t)flags);
  /* reset to the "global" context */
  plugin_set_ctx(old_ctx);

  return (ret_val);
}