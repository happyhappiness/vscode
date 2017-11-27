  NotificationType.tp_base = &PluginDataType;
  PyType_Ready(&NotificationType);
  SignedType.tp_base = &PyLong_Type;
  PyType_Ready(&SignedType);
  UnsignedType.tp_base = &PyLong_Type;
  PyType_Ready(&UnsignedType);
  errordict = PyDict_New();
  PyDict_SetItemString(
      errordict, "__doc__",
      cpy_string_to_unicode_or_bytes(CollectdError_doc)); /* New reference. */
  CollectdError = PyErr_NewException("collectd.CollectdError", NULL, errordict);
  sys = PyImport_ImportModule("sys"); /* New reference. */
  if (sys == NULL) {
    cpy_log_exception("python initialization");
    return 1;
  }
  sys_path = PyObject_GetAttrString(sys, "path"); /* New reference. */
