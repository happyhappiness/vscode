
  snprintf(buf, size, "python.%p", callback);
  PyErr_Clear();
}

void cpy_log_exception(const char *context) {
  int l = 0, collectd_error;
  const char *typename = NULL, *message = NULL;
  PyObject *type, *value, *traceback, *tn, *m, *list;

  PyErr_Fetch(&type, &value, &traceback);
  PyErr_NormalizeException(&type, &value, &traceback);
  if (type == NULL)
    return;
  collectd_error = PyErr_GivenExceptionMatches(value, CollectdError);
  tn = PyObject_GetAttrString(type, "__name__"); /* New reference. */
  m = PyObject_Str(value);                       /* New reference. */
  if (tn != NULL)
    typename = cpy_unicode_or_bytes_to_string(&tn);
  if (m != NULL)
    message = cpy_unicode_or_bytes_to_string(&m);
  if (typename == NULL)
    typename = "NamelessException";
  if (message == NULL)
    message = "N/A";
  Py_BEGIN_ALLOW_THREADS;
  if (collectd_error) {
    WARNING("%s in %s: %s", typename, context, message);
  } else {
    ERROR("Unhandled python exception in %s: %s: %s", context, typename,
          message);
  }
  Py_END_ALLOW_THREADS;
  Py_XDECREF(tn);
  Py_XDECREF(m);
  if (!cpy_format_exception || !traceback || collectd_error) {
    PyErr_Clear();
    Py_DECREF(type);
    Py_XDECREF(value);
    Py_XDECREF(traceback);
    return;
  }
