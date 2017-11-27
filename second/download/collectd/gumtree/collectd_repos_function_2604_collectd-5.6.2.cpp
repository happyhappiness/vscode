static void plugin_flush_timeout_callback_free(void *data) {
  flush_callback_t *cb = data;

  if (cb == NULL)
    return;

  sfree(cb->name);
  sfree(cb);
}