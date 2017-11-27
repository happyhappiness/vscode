int plugin_shutdown_all(void) {
  llentry_t *le;
  int ret = 0; // Assume success.

  destroy_all_callbacks(&list_init);

  stop_read_threads();

  pthread_mutex_lock(&read_lock);
  llist_destroy(read_list);
  read_list = NULL;
  pthread_mutex_unlock(&read_lock);

  destroy_read_heap();

  /* blocks until all write threads have shut down. */
  stop_write_threads();

  /* ask all plugins to write out the state they kept. */
  plugin_flush(/* plugin = */ NULL,
               /* timeout = */ 0,
               /* identifier = */ NULL);

  le = NULL;
  if (list_shutdown != NULL)
    le = llist_head(list_shutdown);

  while (le != NULL) {
    callback_func_t *cf;
    plugin_shutdown_cb callback;
    plugin_ctx_t old_ctx;

    cf = le->value;
    old_ctx = plugin_set_ctx(cf->cf_ctx);
    callback = cf->cf_callback;

    /* Advance the pointer before calling the callback allows
     * shutdown functions to unregister themselves. If done the
     * other way around the memory `le' points to will be freed
     * after callback returns. */
    le = le->next;

    if ((*callback)() != 0)
      ret = -1;

    plugin_set_ctx(old_ctx);
  }

  /* Write plugins which use the `user_data' pointer usually need the
   * same data available to the flush callback. If this is the case, set
   * the free_function to NULL when registering the flush callback and to
   * the real free function when registering the write callback. This way
   * the data isn't freed twice. */
  destroy_all_callbacks(&list_flush);
  destroy_all_callbacks(&list_missing);
  destroy_all_callbacks(&list_write);

  destroy_all_callbacks(&list_notification);
  destroy_all_callbacks(&list_shutdown);
  destroy_all_callbacks(&list_log);

  plugin_free_loaded();
  plugin_free_data_sets();
  return (ret);
}