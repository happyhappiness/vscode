  }
  ds = plugin_get_ds(notification.type);
  if (ds == NULL) {
    PyErr_Format(PyExc_TypeError, "Dataset %s not found", notification.type);
    return NULL;
  }

  if (notification.time == 0)
    notification.time = cdtime();
  if (notification.host[0] == 0)
    sstrncpy(notification.host, hostname_g, sizeof(notification.host));
  if (notification.plugin[0] == 0)
    sstrncpy(notification.plugin, "python", sizeof(notification.plugin));
  Py_BEGIN_ALLOW_THREADS;
  ret = plugin_dispatch_notification(&notification);
  Py_END_ALLOW_THREADS;
  if (ret != 0) {
    PyErr_SetString(PyExc_RuntimeError,
                    "error dispatching notification, read the logs");
    return NULL;
  }
