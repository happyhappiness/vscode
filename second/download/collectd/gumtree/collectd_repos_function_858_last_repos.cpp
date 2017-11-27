static void cpy_build_notification_meta(notification_t *n, PyObject *meta) {
  cpy_build_meta_generic(meta, &cpy_plugin_notification_meta, (void *)n);
}