int plugin_read_all_once(void) {
  int status;
  int return_status = 0;

  if (read_heap == NULL) {
    NOTICE("No read-functions are registered.");
    return 0;
  }

  while (42) {
    read_func_t *rf;
    plugin_ctx_t old_ctx;

    rf = c_heap_get_root(read_heap);
    if (rf == NULL)
      break;

    old_ctx = plugin_set_ctx(rf->rf_ctx);

    if (rf->rf_type == RF_SIMPLE) {
      int (*callback)(void);

      callback = rf->rf_callback;
      status = (*callback)();
    } else {
      plugin_read_cb callback;

      callback = rf->rf_callback;
      status = (*callback)(&rf->rf_udata);
    }

    plugin_set_ctx(old_ctx);

    if (status != 0) {
      NOTICE("read-function of plugin `%s' failed.", rf->rf_name);
      return_status = -1;
    }

    sfree(rf->rf_name);
    destroy_callback((void *)rf);
  }

  return return_status;
}