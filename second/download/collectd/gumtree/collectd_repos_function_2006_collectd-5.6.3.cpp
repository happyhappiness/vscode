static PyObject *cpy_unregister_notification(PyObject *self, PyObject *arg) {
  return cpy_unregister_generic_userdata(plugin_unregister_notification, arg,
                                         "notification");
}