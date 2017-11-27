void plugin_init_ctx(void) {
  pthread_key_create(&plugin_ctx_key, plugin_ctx_destructor);
  plugin_ctx_key_initialized = 1;
}