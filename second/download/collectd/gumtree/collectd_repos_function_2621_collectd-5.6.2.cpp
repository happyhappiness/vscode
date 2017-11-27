int plugin_unregister_flush(const char *name) {
  plugin_ctx_t ctx = plugin_get_ctx();

  if (ctx.flush_interval != 0) {
    char *flush_name;

    flush_name = plugin_flush_callback_name(name);
    if (flush_name != NULL) {
      plugin_unregister_read(flush_name);
      sfree(flush_name);
    }
  }

  return plugin_unregister(list_flush, name);
}