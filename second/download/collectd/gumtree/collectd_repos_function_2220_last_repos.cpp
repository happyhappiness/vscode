static int cpy_notification_callback(const notification_t *notification,
                                     user_data_t *data) {
  cpy_callback_t *c = data->data;
  PyObject *ret, *notify;
  Notification *n;

  CPY_LOCK_THREADS
  PyObject *dict = PyDict_New(); /* New reference. */
  for (notification_meta_t *meta = notification->meta; meta != NULL;
       meta = meta->next) {
    PyObject *temp = NULL;
    if (meta->type == NM_TYPE_STRING) {
      temp = cpy_string_to_unicode_or_bytes(
          meta->nm_value.nm_string); /* New reference. */
      PyDict_SetItemString(dict, meta->name, temp);
      Py_XDECREF(temp);
    } else if (meta->type == NM_TYPE_SIGNED_INT) {
      PyObject *sival = PyLong_FromLongLong(meta->nm_value.nm_signed_int);
      temp = PyObject_CallFunctionObjArgs((void *)&SignedType, sival,
                                          (void *)0); /* New reference. */
      PyDict_SetItemString(dict, meta->name, temp);
      Py_XDECREF(temp);
      Py_XDECREF(sival);
    } else if (meta->type == NM_TYPE_UNSIGNED_INT) {
      PyObject *uval =
          PyLong_FromUnsignedLongLong(meta->nm_value.nm_unsigned_int);
      temp = PyObject_CallFunctionObjArgs((void *)&UnsignedType, uval,
                                          (void *)0); /* New reference. */
      PyDict_SetItemString(dict, meta->name, temp);
      Py_XDECREF(temp);
      Py_XDECREF(uval);
    } else if (meta->type == NM_TYPE_DOUBLE) {
      temp = PyFloat_FromDouble(meta->nm_value.nm_double); /* New reference. */
      PyDict_SetItemString(dict, meta->name, temp);
      Py_XDECREF(temp);
    } else if (meta->type == NM_TYPE_BOOLEAN) {
      PyDict_SetItemString(dict, meta->name,
                           meta->nm_value.nm_boolean ? Py_True : Py_False);
    }
  }
  notify = Notification_New(); /* New reference. */
  n = (Notification *)notify;
  sstrncpy(n->data.host, notification->host, sizeof(n->data.host));
  sstrncpy(n->data.type, notification->type, sizeof(n->data.type));
  sstrncpy(n->data.type_instance, notification->type_instance,
           sizeof(n->data.type_instance));
  sstrncpy(n->data.plugin, notification->plugin, sizeof(n->data.plugin));
  sstrncpy(n->data.plugin_instance, notification->plugin_instance,
           sizeof(n->data.plugin_instance));
  n->data.time = CDTIME_T_TO_DOUBLE(notification->time);
  sstrncpy(n->message, notification->message, sizeof(n->message));
  n->severity = notification->severity;
  Py_CLEAR(n->meta);
  n->meta = dict; /* Steals a reference. */
  ret = PyObject_CallFunctionObjArgs(c->callback, n, c->data,
                                     (void *)0); /* New reference. */
  Py_XDECREF(notify);
  if (ret == NULL) {
    cpy_log_exception("notification callback");
  } else {
    Py_DECREF(ret);
  }
  CPY_RELEASE_THREADS
  return 0;
}