plugin_ctx_t plugin_set_ctx(plugin_ctx_t ctx) {
  plugin_ctx_t prev = mock_context;
  mock_context = ctx;
  return prev;
}