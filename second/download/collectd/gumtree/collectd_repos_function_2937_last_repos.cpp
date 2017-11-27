static void *plugin_thread_start(void *arg) {
  plugin_thread_t *plugin_thread = arg;

  void *(*start_routine)(void *) = plugin_thread->start_routine;
  void *plugin_arg = plugin_thread->arg;

  plugin_set_ctx(plugin_thread->ctx);

  sfree(plugin_thread);

  return start_routine(plugin_arg);
}