static plugin_ctx_t *plugin_ctx_create(void) {
  plugin_ctx_t *ctx;

  ctx = malloc(sizeof(*ctx));
  if (ctx == NULL) {
    char errbuf[1024];
    ERROR("Failed to allocate plugin context: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return NULL;
  }

  *ctx = ctx_init;
  assert(plugin_ctx_key_initialized);
  pthread_setspecific(plugin_ctx_key, ctx);
  DEBUG("Created new plugin context.");
  return (ctx);
}