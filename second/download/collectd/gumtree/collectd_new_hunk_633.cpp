
/* Make sure to hold the GIL while modifying these. */
static int cpy_shutdown_triggered = 0;
static int cpy_num_callbacks = 0;

static void cpy_destroy_user_data(void *data) {
  cpy_callback_t *c = data;
  free(c->name);
  CPY_LOCK_THREADS
  Py_DECREF(c->callback);
  Py_XDECREF(c->data);
  free(c);
  --cpy_num_callbacks;
  if (!cpy_num_callbacks && cpy_shutdown_triggered) {
    Py_Finalize();
    return;
  }
  CPY_RELEASE_THREADS
}

/* You must hold the GIL to call this function!
 * But if you managed to extract the callback parameter then you probably
 * already do. */

static void cpy_build_name(char *buf, size_t size, PyObject *callback,
                           const char *name) {
  const char *module = NULL;
  PyObject *mod = NULL;

  if (name != NULL) {
    snprintf(buf, size, "python.%s", name);
    return;
  }

  mod = PyObject_GetAttrString(callback, "__module__"); /* New reference. */
  if (mod != NULL)
    module = cpy_unicode_or_bytes_to_string(&mod);

  if (module != NULL) {
    snprintf(buf, size, "python.%s", module);
    Py_XDECREF(mod);
    PyErr_Clear();
    return;
  }
  Py_XDECREF(mod);

  snprintf(buf, size, "python.%p", callback);
  PyErr_Clear();
}

void cpy_log_exception(const char *context) {
  int l = 0;
  const char *typename = NULL, *message = NULL;
  PyObject *type, *value, *traceback, *tn, *m, *list;

  PyErr_Fetch(&type, &value, &traceback);
  PyErr_NormalizeException(&type, &value, &traceback);
  if (type == NULL)
    return;
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
  Py_BEGIN_ALLOW_THREADS ERROR("Unhandled python exception in %s: %s: %s",
                               context, typename, message);
  Py_END_ALLOW_THREADS Py_XDECREF(tn);
  Py_XDECREF(m);
  if (!cpy_format_exception || !traceback) {
    PyErr_Clear();
    Py_DECREF(type);
    Py_XDECREF(value);
    Py_XDECREF(traceback);
    return;
  }
  list = PyObject_CallFunction(cpy_format_exception, "NNN", type, value,
                               traceback); /* New reference. Steals references
                                              from "type", "value" and
                                              "traceback". */
  if (list)
    l = PyObject_Length(list);

  for (int i = 0; i < l; ++i) {
    PyObject *line;
    char const *msg;
    char *cpy;

    line = PyList_GET_ITEM(list, i); /* Borrowed reference. */
    Py_INCREF(line);

    msg = cpy_unicode_or_bytes_to_string(&line);
    Py_DECREF(line);
    if (msg == NULL)
      continue;

    cpy = strdup(msg);
    if (cpy == NULL)
      continue;

    if (cpy[strlen(cpy) - 1] == '\n')
      cpy[strlen(cpy) - 1] = 0;

    Py_BEGIN_ALLOW_THREADS ERROR("%s", cpy);
    Py_END_ALLOW_THREADS

        free(cpy);
  }

  Py_XDECREF(list);
  PyErr_Clear();
}

static int cpy_read_callback(user_data_t *data) {
  cpy_callback_t *c = data->data;
  PyObject *ret;

  CPY_LOCK_THREADS
  ret = PyObject_CallFunctionObjArgs(c->callback, c->data,
                                     (void *)0); /* New reference. */
  if (ret == NULL) {
    cpy_log_exception("read callback");
  } else {
    Py_DECREF(ret);
  }
  CPY_RELEASE_THREADS
  if (ret == NULL)
    return 1;
  return 0;
}

static int cpy_write_callback(const data_set_t *ds,
                              const value_list_t *value_list,
                              user_data_t *data) {
  cpy_callback_t *c = data->data;
  PyObject *ret, *list, *temp, *dict = NULL;
  Values *v;

  CPY_LOCK_THREADS
  list = PyList_New(value_list->values_len); /* New reference. */
  if (list == NULL) {
    cpy_log_exception("write callback");
    CPY_RETURN_FROM_THREADS 0;
  }
  for (size_t i = 0; i < value_list->values_len; ++i) {
    if (ds->ds[i].type == DS_TYPE_COUNTER) {
      PyList_SetItem(
          list, i, PyLong_FromUnsignedLongLong(value_list->values[i].counter));
    } else if (ds->ds[i].type == DS_TYPE_GAUGE) {
      PyList_SetItem(list, i, PyFloat_FromDouble(value_list->values[i].gauge));
    } else if (ds->ds[i].type == DS_TYPE_DERIVE) {
      PyList_SetItem(list, i,
                     PyLong_FromLongLong(value_list->values[i].derive));
    } else if (ds->ds[i].type == DS_TYPE_ABSOLUTE) {
      PyList_SetItem(
          list, i, PyLong_FromUnsignedLongLong(value_list->values[i].absolute));
    } else {
      Py_BEGIN_ALLOW_THREADS ERROR("cpy_write_callback: Unknown value type %d.",
                                   ds->ds[i].type);
      Py_END_ALLOW_THREADS Py_DECREF(list);
      CPY_RETURN_FROM_THREADS 0;
    }
    if (PyErr_Occurred() != NULL) {
      cpy_log_exception("value building for write callback");
      Py_DECREF(list);
      CPY_RETURN_FROM_THREADS 0;
    }
  }
  dict = PyDict_New(); /* New reference. */
  if (value_list->meta) {
    char **table;
    meta_data_t *meta = value_list->meta;

    int num = meta_data_toc(meta, &table);
    for (int i = 0; i < num; ++i) {
      int type;
      char *string;
      int64_t si;
      uint64_t ui;
      double d;
      _Bool b;

      type = meta_data_type(meta, table[i]);
      if (type == MD_TYPE_STRING) {
        if (meta_data_get_string(meta, table[i], &string))
          continue;
        temp = cpy_string_to_unicode_or_bytes(string); /* New reference. */
        free(string);
        PyDict_SetItemString(dict, table[i], temp);
        Py_XDECREF(temp);
      } else if (type == MD_TYPE_SIGNED_INT) {
        if (meta_data_get_signed_int(meta, table[i], &si))
          continue;
        temp = PyObject_CallFunctionObjArgs((void *)&SignedType,
                                            PyLong_FromLongLong(si),
                                            (void *)0); /* New reference. */
        PyDict_SetItemString(dict, table[i], temp);
        Py_XDECREF(temp);
      } else if (type == MD_TYPE_UNSIGNED_INT) {
        if (meta_data_get_unsigned_int(meta, table[i], &ui))
          continue;
        temp = PyObject_CallFunctionObjArgs((void *)&UnsignedType,
                                            PyLong_FromUnsignedLongLong(ui),
                                            (void *)0); /* New reference. */
        PyDict_SetItemString(dict, table[i], temp);
        Py_XDECREF(temp);
      } else if (type == MD_TYPE_DOUBLE) {
        if (meta_data_get_double(meta, table[i], &d))
          continue;
        temp = PyFloat_FromDouble(d); /* New reference. */
        PyDict_SetItemString(dict, table[i], temp);
        Py_XDECREF(temp);
      } else if (type == MD_TYPE_BOOLEAN) {
        if (meta_data_get_boolean(meta, table[i], &b))
          continue;
        if (b)
          PyDict_SetItemString(dict, table[i], Py_True);
	else
          PyDict_SetItemString(dict, table[i], Py_False);
      }
      free(table[i]);
    }
    free(table);
  }
  v = (Values *)Values_New(); /* New reference. */
  sstrncpy(v->data.host, value_list->host, sizeof(v->data.host));
  sstrncpy(v->data.type, value_list->type, sizeof(v->data.type));
  sstrncpy(v->data.type_instance, value_list->type_instance,
           sizeof(v->data.type_instance));
  sstrncpy(v->data.plugin, value_list->plugin, sizeof(v->data.plugin));
  sstrncpy(v->data.plugin_instance, value_list->plugin_instance,
           sizeof(v->data.plugin_instance));
  v->data.time = CDTIME_T_TO_DOUBLE(value_list->time);
  v->interval = CDTIME_T_TO_DOUBLE(value_list->interval);
  Py_CLEAR(v->values);
  v->values = list;
  Py_CLEAR(v->meta);
  v->meta = dict; /* Steals a reference. */
  ret = PyObject_CallFunctionObjArgs(c->callback, v, c->data,
                                     (void *)0); /* New reference. */
  Py_XDECREF(v);
  if (ret == NULL) {
    cpy_log_exception("write callback");
  } else {
    Py_DECREF(ret);
  }
  CPY_RELEASE_THREADS
  return 0;
}

static int cpy_notification_callback(const notification_t *notification,
                                     user_data_t *data) {
  cpy_callback_t *c = data->data;
  PyObject *ret, *notify;
  Notification *n;

  CPY_LOCK_THREADS
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

static void cpy_log_callback(int severity, const char *message,
                             user_data_t *data) {
  cpy_callback_t *c = data->data;
  PyObject *ret, *text;

  CPY_LOCK_THREADS
  text = cpy_string_to_unicode_or_bytes(message); /* New reference. */
  if (c->data == NULL)
    ret = PyObject_CallFunction(
        c->callback, "iN", severity,
        text); /* New reference. Steals a reference from "text". */
  else
    ret = PyObject_CallFunction(
        c->callback, "iNO", severity, text,
        c->data); /* New reference. Steals a reference from "text". */

  if (ret == NULL) {
    /* FIXME */
    /* Do we really want to trigger a log callback because a log callback
     * failed?
     * Probably not. */
    PyErr_Print();
    /* In case someone wanted to be clever, replaced stderr and failed at that.
     */
    PyErr_Clear();
  } else {
    Py_DECREF(ret);
  }
  CPY_RELEASE_THREADS
}

static void cpy_flush_callback(int timeout, const char *id, user_data_t *data) {
  cpy_callback_t *c = data->data;
  PyObject *ret, *text;

  CPY_LOCK_THREADS
  if (id) {
    text = cpy_string_to_unicode_or_bytes(id);
  } else {
    text = Py_None;
    Py_INCREF(text);
  }
  if (c->data == NULL)
    ret = PyObject_CallFunction(c->callback, "iN", timeout,
                                text); /* New reference. */
  else
    ret = PyObject_CallFunction(c->callback, "iNO", timeout, text,
                                c->data); /* New reference. */

  if (ret == NULL) {
    cpy_log_exception("flush callback");
  } else {
    Py_DECREF(ret);
  }
  CPY_RELEASE_THREADS
}

static PyObject *cpy_register_generic(cpy_callback_t **list_head,
                                      PyObject *args, PyObject *kwds) {
  char buf[512];
  cpy_callback_t *c;
  char *name = NULL;
  PyObject *callback = NULL, *data = NULL, *mod = NULL;
  static char *kwlist[] = {"callback", "data", "name", NULL};

  if (PyArg_ParseTupleAndKeywords(args, kwds, "O|Oet", kwlist, &callback, &data,
                                  NULL, &name) == 0)
    return NULL;
  if (PyCallable_Check(callback) == 0) {
    PyMem_Free(name);
    PyErr_SetString(PyExc_TypeError, "callback needs a be a callable object.");
    return NULL;
  }
  cpy_build_name(buf, sizeof(buf), callback, name);

  Py_INCREF(callback);
  Py_XINCREF(data);

  c = calloc(1, sizeof(*c));
  if (c == NULL)
    return NULL;

  c->name = strdup(buf);
  c->callback = callback;
  c->data = data;
  c->next = *list_head;
  ++cpy_num_callbacks;
  *list_head = c;
  Py_XDECREF(mod);
  PyMem_Free(name);
  return cpy_string_to_unicode_or_bytes(buf);
}

static PyObject *float_or_none(float number) {
  if (isnan(number)) {
    Py_RETURN_NONE;
  }
  return PyFloat_FromDouble(number);
}

static PyObject *cpy_get_dataset(PyObject *self, PyObject *args) {
  char *name;
  const data_set_t *ds;
  PyObject *list, *tuple;

  if (PyArg_ParseTuple(args, "et", NULL, &name) == 0)
    return NULL;
  ds = plugin_get_ds(name);
  PyMem_Free(name);
  if (ds == NULL) {
    PyErr_Format(PyExc_TypeError, "Dataset %s not found", name);
    return NULL;
  }
  list = PyList_New(ds->ds_num); /* New reference. */
  for (size_t i = 0; i < ds->ds_num; ++i) {
    tuple = PyTuple_New(4);
    PyTuple_SET_ITEM(tuple, 0, cpy_string_to_unicode_or_bytes(ds->ds[i].name));
    PyTuple_SET_ITEM(tuple, 1, cpy_string_to_unicode_or_bytes(
                                   DS_TYPE_TO_STRING(ds->ds[i].type)));
    PyTuple_SET_ITEM(tuple, 2, float_or_none(ds->ds[i].min));
    PyTuple_SET_ITEM(tuple, 3, float_or_none(ds->ds[i].max));
    PyList_SET_ITEM(list, i, tuple);
  }
  return list;
}

static PyObject *cpy_flush(PyObject *self, PyObject *args, PyObject *kwds) {
  int timeout = -1;
  char *plugin = NULL, *identifier = NULL;
  static char *kwlist[] = {"plugin", "timeout", "identifier", NULL};

  if (PyArg_ParseTupleAndKeywords(args, kwds, "|etiet", kwlist, NULL, &plugin,
                                  &timeout, NULL, &identifier) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS plugin_flush(plugin, timeout, identifier);
  Py_END_ALLOW_THREADS PyMem_Free(plugin);
  PyMem_Free(identifier);
  Py_RETURN_NONE;
}

static PyObject *cpy_register_config(PyObject *self, PyObject *args,
                                     PyObject *kwds) {
  return cpy_register_generic(&cpy_config_callbacks, args, kwds);
}

static PyObject *cpy_register_init(PyObject *self, PyObject *args,
                                   PyObject *kwds) {
  return cpy_register_generic(&cpy_init_callbacks, args, kwds);
}

typedef int reg_function_t(const char *name, void *callback, void *data);

static PyObject *cpy_register_generic_userdata(void *reg, void *handler,
                                               PyObject *args, PyObject *kwds) {
  char buf[512];
  reg_function_t *register_function = (reg_function_t *)reg;
  cpy_callback_t *c = NULL;
  char *name = NULL;
  PyObject *callback = NULL, *data = NULL;
  static char *kwlist[] = {"callback", "data", "name", NULL};

  if (PyArg_ParseTupleAndKeywords(args, kwds, "O|Oet", kwlist, &callback, &data,
                                  NULL, &name) == 0)
    return NULL;
  if (PyCallable_Check(callback) == 0) {
    PyMem_Free(name);
    PyErr_SetString(PyExc_TypeError, "callback needs a be a callable object.");
    return NULL;
  }
  cpy_build_name(buf, sizeof(buf), callback, name);
  PyMem_Free(name);

  Py_INCREF(callback);
  Py_XINCREF(data);

  c = calloc(1, sizeof(*c));
  if (c == NULL)
    return NULL;

  c->name = strdup(buf);
  c->callback = callback;
  c->data = data;
  c->next = NULL;

  user_data_t user_data = {.data = c, .free_func = cpy_destroy_user_data};

  register_function(buf, handler, &user_data);
  ++cpy_num_callbacks;
  return cpy_string_to_unicode_or_bytes(buf);
}

static PyObject *cpy_register_read(PyObject *self, PyObject *args,
                                   PyObject *kwds) {
  char buf[512];
  cpy_callback_t *c = NULL;
  double interval = 0;
  char *name = NULL;
  PyObject *callback = NULL, *data = NULL;
  static char *kwlist[] = {"callback", "interval", "data", "name", NULL};

  if (PyArg_ParseTupleAndKeywords(args, kwds, "O|dOet", kwlist, &callback,
                                  &interval, &data, NULL, &name) == 0)
    return NULL;
  if (PyCallable_Check(callback) == 0) {
    PyMem_Free(name);
    PyErr_SetString(PyExc_TypeError, "callback needs a be a callable object.");
    return NULL;
  }
  cpy_build_name(buf, sizeof(buf), callback, name);
  PyMem_Free(name);

  Py_INCREF(callback);
  Py_XINCREF(data);

  c = calloc(1, sizeof(*c));
  if (c == NULL)
    return NULL;

  c->name = strdup(buf);
  c->callback = callback;
  c->data = data;
  c->next = NULL;

  user_data_t user_data = {.data = c, .free_func = cpy_destroy_user_data};

  plugin_register_complex_read(/* group = */ "python", buf, cpy_read_callback,
                               DOUBLE_TO_CDTIME_T(interval), &user_data);
  ++cpy_num_callbacks;
  return cpy_string_to_unicode_or_bytes(buf);
}

static PyObject *cpy_register_log(PyObject *self, PyObject *args,
                                  PyObject *kwds) {
  return cpy_register_generic_userdata((void *)plugin_register_log,
                                       (void *)cpy_log_callback, args, kwds);
}

static PyObject *cpy_register_write(PyObject *self, PyObject *args,
                                    PyObject *kwds) {
  return cpy_register_generic_userdata((void *)plugin_register_write,
                                       (void *)cpy_write_callback, args, kwds);
}

static PyObject *cpy_register_notification(PyObject *self, PyObject *args,
                                           PyObject *kwds) {
  return cpy_register_generic_userdata((void *)plugin_register_notification,
                                       (void *)cpy_notification_callback, args,
                                       kwds);
}

static PyObject *cpy_register_flush(PyObject *self, PyObject *args,
                                    PyObject *kwds) {
  return cpy_register_generic_userdata((void *)plugin_register_flush,
                                       (void *)cpy_flush_callback, args, kwds);
}

static PyObject *cpy_register_shutdown(PyObject *self, PyObject *args,
                                       PyObject *kwds) {
  return cpy_register_generic(&cpy_shutdown_callbacks, args, kwds);
}

static PyObject *cpy_error(PyObject *self, PyObject *args) {
  char *text;
  if (PyArg_ParseTuple(args, "et", NULL, &text) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS plugin_log(LOG_ERR, "%s", text);
  Py_END_ALLOW_THREADS PyMem_Free(text);
  Py_RETURN_NONE;
}

static PyObject *cpy_warning(PyObject *self, PyObject *args) {
  char *text;
  if (PyArg_ParseTuple(args, "et", NULL, &text) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS plugin_log(LOG_WARNING, "%s", text);
  Py_END_ALLOW_THREADS PyMem_Free(text);
  Py_RETURN_NONE;
}

static PyObject *cpy_notice(PyObject *self, PyObject *args) {
  char *text;
  if (PyArg_ParseTuple(args, "et", NULL, &text) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS plugin_log(LOG_NOTICE, "%s", text);
  Py_END_ALLOW_THREADS PyMem_Free(text);
  Py_RETURN_NONE;
}

static PyObject *cpy_info(PyObject *self, PyObject *args) {
  char *text;
  if (PyArg_ParseTuple(args, "et", NULL, &text) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS plugin_log(LOG_INFO, "%s", text);
  Py_END_ALLOW_THREADS PyMem_Free(text);
  Py_RETURN_NONE;
}

static PyObject *cpy_debug(PyObject *self, PyObject *args) {
#ifdef COLLECT_DEBUG
  char *text;
  if (PyArg_ParseTuple(args, "et", NULL, &text) == 0)
    return NULL;
  Py_BEGIN_ALLOW_THREADS plugin_log(LOG_DEBUG, "%s", text);
  Py_END_ALLOW_THREADS PyMem_Free(text);
#endif
  Py_RETURN_NONE;
}

static PyObject *cpy_unregister_generic(cpy_callback_t **list_head,
                                        PyObject *arg, const char *desc) {
  char buf[512];
  const char *name;
  cpy_callback_t *prev = NULL, *tmp;

  Py_INCREF(arg);
  name = cpy_unicode_or_bytes_to_string(&arg);
  if (name == NULL) {
    PyErr_Clear();
    if (!PyCallable_Check(arg)) {
      PyErr_SetString(PyExc_TypeError, "This function needs a string or a "
                                       "callable object as its only "
                                       "parameter.");
      Py_DECREF(arg);
      return NULL;
    }
    cpy_build_name(buf, sizeof(buf), arg, NULL);
    name = buf;
  }
  for (tmp = *list_head; tmp; prev = tmp, tmp = tmp->next)
    if (strcmp(name, tmp->name) == 0)
      break;

  Py_DECREF(arg);
  if (tmp == NULL) {
    PyErr_Format(PyExc_RuntimeError, "Unable to unregister %s callback '%s'.",
                 desc, name);
    return NULL;
  }
  /* Yes, this is actually safe. To call this function the caller has to
   * hold the GIL. Well, safe as long as there is only one GIL anyway ... */
  if (prev == NULL)
    *list_head = tmp->next;
  else
    prev->next = tmp->next;
  cpy_destroy_user_data(tmp);
  Py_RETURN_NONE;
}

static void cpy_unregister_list(cpy_callback_t **list_head) {
  cpy_callback_t *cur, *next;
  for (cur = *list_head; cur; cur = next) {
    next = cur->next;
    cpy_destroy_user_data(cur);
  }
  *list_head = NULL;
}

typedef int cpy_unregister_function_t(const char *name);

static PyObject *
cpy_unregister_generic_userdata(cpy_unregister_function_t *unreg, PyObject *arg,
                                const char *desc) {
  char buf[512];
  const char *name;

  Py_INCREF(arg);
  name = cpy_unicode_or_bytes_to_string(&arg);
  if (name == NULL) {
    PyErr_Clear();
    if (!PyCallable_Check(arg)) {
      PyErr_SetString(PyExc_TypeError, "This function needs a string or a "
                                       "callable object as its only "
                                       "parameter.");
      Py_DECREF(arg);
      return NULL;
    }
    cpy_build_name(buf, sizeof(buf), arg, NULL);
    name = buf;
  }
  if (unreg(name) == 0) {
    Py_DECREF(arg);
    Py_RETURN_NONE;
  }
  PyErr_Format(PyExc_RuntimeError, "Unable to unregister %s callback '%s'.",
               desc, name);
  Py_DECREF(arg);
  return NULL;
}

static PyObject *cpy_unregister_log(PyObject *self, PyObject *arg) {
  return cpy_unregister_generic_userdata(plugin_unregister_log, arg, "log");
}

static PyObject *cpy_unregister_init(PyObject *self, PyObject *arg) {
  return cpy_unregister_generic(&cpy_init_callbacks, arg, "init");
}

static PyObject *cpy_unregister_config(PyObject *self, PyObject *arg) {
  return cpy_unregister_generic(&cpy_config_callbacks, arg, "config");
}

static PyObject *cpy_unregister_read(PyObject *self, PyObject *arg) {
  return cpy_unregister_generic_userdata(plugin_unregister_read, arg, "read");
}

static PyObject *cpy_unregister_write(PyObject *self, PyObject *arg) {
  return cpy_unregister_generic_userdata(plugin_unregister_write, arg, "write");
}

static PyObject *cpy_unregister_notification(PyObject *self, PyObject *arg) {
  return cpy_unregister_generic_userdata(plugin_unregister_notification, arg,
                                         "notification");
}

static PyObject *cpy_unregister_flush(PyObject *self, PyObject *arg) {
  return cpy_unregister_generic_userdata(plugin_unregister_flush, arg, "flush");
}

static PyObject *cpy_unregister_shutdown(PyObject *self, PyObject *arg) {
  return cpy_unregister_generic(&cpy_shutdown_callbacks, arg, "shutdown");
}

static PyMethodDef cpy_methods[] = {
    {"debug", cpy_debug, METH_VARARGS, log_doc},
    {"info", cpy_info, METH_VARARGS, log_doc},
    {"notice", cpy_notice, METH_VARARGS, log_doc},
    {"warning", cpy_warning, METH_VARARGS, log_doc},
    {"error", cpy_error, METH_VARARGS, log_doc},
    {"get_dataset", (PyCFunction)cpy_get_dataset, METH_VARARGS, get_ds_doc},
    {"flush", (PyCFunction)cpy_flush, METH_VARARGS | METH_KEYWORDS, flush_doc},
    {"register_log", (PyCFunction)cpy_register_log,
     METH_VARARGS | METH_KEYWORDS, reg_log_doc},
    {"register_init", (PyCFunction)cpy_register_init,
     METH_VARARGS | METH_KEYWORDS, reg_init_doc},
    {"register_config", (PyCFunction)cpy_register_config,
     METH_VARARGS | METH_KEYWORDS, reg_config_doc},
    {"register_read", (PyCFunction)cpy_register_read,
     METH_VARARGS | METH_KEYWORDS, reg_read_doc},
    {"register_write", (PyCFunction)cpy_register_write,
     METH_VARARGS | METH_KEYWORDS, reg_write_doc},
    {"register_notification", (PyCFunction)cpy_register_notification,
     METH_VARARGS | METH_KEYWORDS, reg_notification_doc},
    {"register_flush", (PyCFunction)cpy_register_flush,
     METH_VARARGS | METH_KEYWORDS, reg_flush_doc},
    {"register_shutdown", (PyCFunction)cpy_register_shutdown,
     METH_VARARGS | METH_KEYWORDS, reg_shutdown_doc},
    {"unregister_log", cpy_unregister_log, METH_O, unregister_doc},
    {"unregister_init", cpy_unregister_init, METH_O, unregister_doc},
    {"unregister_config", cpy_unregister_config, METH_O, unregister_doc},
    {"unregister_read", cpy_unregister_read, METH_O, unregister_doc},
    {"unregister_write", cpy_unregister_write, METH_O, unregister_doc},
    {"unregister_notification", cpy_unregister_notification, METH_O,
     unregister_doc},
    {"unregister_flush", cpy_unregister_flush, METH_O, unregister_doc},
    {"unregister_shutdown", cpy_unregister_shutdown, METH_O, unregister_doc},
    {0, 0, 0, 0}};

static int cpy_shutdown(void) {
  PyObject *ret;

  if (!state) {
    printf(
        "================================================================\n");
    printf(
        "collectd shutdown while running an interactive session. This will\n");
    printf("probably leave your terminal in a mess.\n");
    printf("Run the command \"reset\" to get it back into a usable state.\n");
    printf("You can press Ctrl+D in the interactive session to\n");
    printf("close collectd and avoid this problem in the future.\n");
    printf(
        "================================================================\n");
  }

  CPY_LOCK_THREADS

  for (cpy_callback_t *c = cpy_shutdown_callbacks; c; c = c->next) {
    ret = PyObject_CallFunctionObjArgs(c->callback, c->data,
                                       (void *)0); /* New reference. */
    if (ret == NULL)
      cpy_log_exception("shutdown callback");
    else
      Py_DECREF(ret);
  }
  PyErr_Print();

  Py_BEGIN_ALLOW_THREADS cpy_unregister_list(&cpy_config_callbacks);
  cpy_unregister_list(&cpy_init_callbacks);
  cpy_unregister_list(&cpy_shutdown_callbacks);
  cpy_shutdown_triggered = 1;
  Py_END_ALLOW_THREADS

      if (!cpy_num_callbacks) {
    Py_Finalize();
    return 0;
  }

  CPY_RELEASE_THREADS
  return 0;
}

static void *cpy_interactive(void *pipefd) {
  PyOS_sighandler_t cur_sig;

  /* Signal handler in a plugin? Bad stuff, but the best way to
   * handle it I guess. In an interactive session people will
   * press Ctrl+C at some time, which will generate a SIGINT.
   * This will cause collectd to shutdown, thus killing the
   * interactive interpreter, and leaving the terminal in a
   * mess. Chances are, this isn't what the user wanted to do.
   *
   * So this is the plan:
   * 1. Restore Python's own signal handler
   * 2. Tell Python we just forked so it will accept this thread
   *    as the main one. No version of Python will ever handle
   *    interrupts anywhere but in the main thread.
   * 3. After the interactive loop is done, restore collectd's
   *    SIGINT handler.
   * 4. Raise SIGINT for a clean shutdown. The signal is sent to
   *    the main thread to ensure it wakes up the main interval
   *    sleep so that collectd shuts down immediately not in 10
   *    seconds.
   *
   * This will make sure that SIGINT won't kill collectd but
   * still interrupt syscalls like sleep and pause. */

  if (PyImport_ImportModule("readline") == NULL) {
    /* This interactive session will suck. */
    cpy_log_exception("interactive session init");
  }
  cur_sig = PyOS_setsig(SIGINT, python_sigint_handler);
  PyOS_AfterFork();
  PyEval_InitThreads();
  close(*(int *)pipefd);
  PyRun_InteractiveLoop(stdin, "<stdin>");
  PyOS_setsig(SIGINT, cur_sig);
  PyErr_Print();
  state = PyEval_SaveThread();
  NOTICE("python: Interactive interpreter exited, stopping collectd ...");
  pthread_kill(main_thread, SIGINT);
  return NULL;
}

static int cpy_init(void) {
  PyObject *ret;
  int pipefd[2];
  char buf;
  static pthread_t thread;

  if (!Py_IsInitialized()) {
    WARNING("python: Plugin loaded but not configured.");
    plugin_unregister_shutdown("python");
    Py_Finalize();
    return 0;
  }
  main_thread = pthread_self();
  if (do_interactive) {
    if (pipe(pipefd)) {
      ERROR("python: Unable to create pipe.");
      return 1;
    }
    if (plugin_thread_create(&thread, NULL, cpy_interactive, pipefd + 1)) {
      ERROR("python: Error creating thread for interactive interpreter.");
    }
    if (read(pipefd[0], &buf, 1))
      ;
    (void)close(pipefd[0]);
  } else {
    PyEval_InitThreads();
    state = PyEval_SaveThread();
  }
  CPY_LOCK_THREADS
  for (cpy_callback_t *c = cpy_init_callbacks; c; c = c->next) {
    ret = PyObject_CallFunctionObjArgs(c->callback, c->data,
                                       (void *)0); /* New reference. */
    if (ret == NULL)
      cpy_log_exception("init callback");
    else
      Py_DECREF(ret);
  }
  CPY_RELEASE_THREADS

  return 0;
}

static PyObject *cpy_oconfig_to_pyconfig(oconfig_item_t *ci, PyObject *parent) {
  PyObject *item, *values, *children, *tmp;

  if (parent == NULL)
    parent = Py_None;

  values = PyTuple_New(ci->values_num); /* New reference. */
  for (int i = 0; i < ci->values_num; ++i) {
    if (ci->values[i].type == OCONFIG_TYPE_STRING) {
      PyTuple_SET_ITEM(values, i, cpy_string_to_unicode_or_bytes(
                                      ci->values[i].value.string));
    } else if (ci->values[i].type == OCONFIG_TYPE_NUMBER) {
      PyTuple_SET_ITEM(values, i,
                       PyFloat_FromDouble(ci->values[i].value.number));
    } else if (ci->values[i].type == OCONFIG_TYPE_BOOLEAN) {
      PyTuple_SET_ITEM(values, i, PyBool_FromLong(ci->values[i].value.boolean));
    }
  }

  tmp = cpy_string_to_unicode_or_bytes(ci->key);
  item = PyObject_CallFunction((void *)&ConfigType, "NONO", tmp, parent, values,
                               Py_None);
  if (item == NULL)
    return NULL;
  children = PyTuple_New(ci->children_num); /* New reference. */
  for (int i = 0; i < ci->children_num; ++i) {
    PyTuple_SET_ITEM(children, i,
                     cpy_oconfig_to_pyconfig(ci->children + i, item));
  }
  tmp = ((Config *)item)->children;
  ((Config *)item)->children = children;
  Py_XDECREF(tmp);
  return item;
}

#ifdef IS_PY3K
static struct PyModuleDef collectdmodule = {
    PyModuleDef_HEAD_INIT, "collectd",  /* name of module */
    "The python interface to collectd", /* module documentation, may be NULL */
    -1, cpy_methods};

PyMODINIT_FUNC PyInit_collectd(void) {
  return PyModule_Create(&collectdmodule);
}
#endif

static int cpy_init_python(void) {
  PyOS_sighandler_t cur_sig;
  PyObject *sys;
  PyObject *module;

#ifdef IS_PY3K
  wchar_t *argv = L"";
  /* Add a builtin module, before Py_Initialize */
  PyImport_AppendInittab("collectd", PyInit_collectd);
#else
  char *argv = "";
#endif

  /* Chances are the current signal handler is already SIG_DFL, but let's make
   * sure. */
  cur_sig = PyOS_setsig(SIGINT, SIG_DFL);
  Py_Initialize();
  python_sigint_handler = PyOS_setsig(SIGINT, cur_sig);

  PyType_Ready(&ConfigType);
  PyType_Ready(&PluginDataType);
  ValuesType.tp_base = &PluginDataType;
  PyType_Ready(&ValuesType);
  NotificationType.tp_base = &PluginDataType;
  PyType_Ready(&NotificationType);
  SignedType.tp_base = &PyLong_Type;
  PyType_Ready(&SignedType);
  UnsignedType.tp_base = &PyLong_Type;
  PyType_Ready(&UnsignedType);
  sys = PyImport_ImportModule("sys"); /* New reference. */
  if (sys == NULL) {
    cpy_log_exception("python initialization");
    return 1;
  }
  sys_path = PyObject_GetAttrString(sys, "path"); /* New reference. */
  Py_DECREF(sys);
  if (sys_path == NULL) {
    cpy_log_exception("python initialization");
    return 1;
  }
  PySys_SetArgv(1, &argv);
  PyList_SetSlice(sys_path, 0, 1, NULL);

#ifdef IS_PY3K
  module = PyImport_ImportModule("collectd");
#else
  module = Py_InitModule("collectd", cpy_methods); /* Borrowed reference. */
#endif
  PyModule_AddObject(module, "Config",
                     (void *)&ConfigType); /* Steals a reference. */
  PyModule_AddObject(module, "Values",
                     (void *)&ValuesType); /* Steals a reference. */
  PyModule_AddObject(module, "Notification",
                     (void *)&NotificationType); /* Steals a reference. */
  PyModule_AddObject(module, "Signed",
                     (void *)&SignedType); /* Steals a reference. */
  PyModule_AddObject(module, "Unsigned",
                     (void *)&UnsignedType); /* Steals a reference. */
  PyModule_AddIntConstant(module, "LOG_DEBUG", LOG_DEBUG);
  PyModule_AddIntConstant(module, "LOG_INFO", LOG_INFO);
  PyModule_AddIntConstant(module, "LOG_NOTICE", LOG_NOTICE);
  PyModule_AddIntConstant(module, "LOG_WARNING", LOG_WARNING);
  PyModule_AddIntConstant(module, "LOG_ERROR", LOG_ERR);
  PyModule_AddIntConstant(module, "NOTIF_FAILURE", NOTIF_FAILURE);
  PyModule_AddIntConstant(module, "NOTIF_WARNING", NOTIF_WARNING);
  PyModule_AddIntConstant(module, "NOTIF_OKAY", NOTIF_OKAY);
  PyModule_AddStringConstant(module, "DS_TYPE_COUNTER",
                             DS_TYPE_TO_STRING(DS_TYPE_COUNTER));
  PyModule_AddStringConstant(module, "DS_TYPE_GAUGE",
                             DS_TYPE_TO_STRING(DS_TYPE_GAUGE));
  PyModule_AddStringConstant(module, "DS_TYPE_DERIVE",
                             DS_TYPE_TO_STRING(DS_TYPE_DERIVE));
  PyModule_AddStringConstant(module, "DS_TYPE_ABSOLUTE",
                             DS_TYPE_TO_STRING(DS_TYPE_ABSOLUTE));
  return 0;
}

static int cpy_config(oconfig_item_t *ci) {
  PyObject *tb;
  int status = 0;

  /* Ok in theory we shouldn't do initialization at this point
   * but we have to. In order to give python scripts a chance
   * to register a config callback we need to be able to execute
   * python code during the config callback so we have to start
   * the interpreter here. */
  /* Do *not* use the python "thread" module at this point! */

  if (!Py_IsInitialized() && cpy_init_python())
    return 1;

  for (int i = 0; i < ci->children_num; ++i) {
    oconfig_item_t *item = ci->children + i;

    if (strcasecmp(item->key, "Interactive") == 0) {
      if (cf_util_get_boolean(item, &do_interactive) != 0) {
        status = 1;
        continue;
      }
    } else if (strcasecmp(item->key, "Encoding") == 0) {
      char *encoding = NULL;
      if (cf_util_get_string(item, &encoding) != 0) {
        status = 1;
        continue;
      }
#ifdef IS_PY3K
      ERROR("python: \"Encoding\" was used in the config file but Python3 was "
            "used, which does not support changing encodings");
      status = 1;
      sfree(encoding);
      continue;
#else
      /* Why is this even necessary? And undocumented? */
      if (PyUnicode_SetDefaultEncoding(encoding)) {
        cpy_log_exception("setting default encoding");
        status = 1;
      }
#endif
      sfree(encoding);
    } else if (strcasecmp(item->key, "LogTraces") == 0) {
      _Bool log_traces;
      if (cf_util_get_boolean(item, &log_traces) != 0) {
        status = 1;
        continue;
      }
      if (!log_traces) {
        Py_XDECREF(cpy_format_exception);
        cpy_format_exception = NULL;
        continue;
      }
      if (cpy_format_exception)
        continue;
      tb = PyImport_ImportModule("traceback"); /* New reference. */
      if (tb == NULL) {
        cpy_log_exception("python initialization");
        status = 1;
        continue;
      }
      cpy_format_exception =
          PyObject_GetAttrString(tb, "format_exception"); /* New reference. */
      Py_DECREF(tb);
      if (cpy_format_exception == NULL) {
        cpy_log_exception("python initialization");
        status = 1;
      }
    } else if (strcasecmp(item->key, "ModulePath") == 0) {
      char *dir = NULL;
      PyObject *dir_object;

      if (cf_util_get_string(item, &dir) != 0) {
        status = 1;
        continue;
      }
      dir_object = cpy_string_to_unicode_or_bytes(dir); /* New reference. */
      if (dir_object == NULL) {
        ERROR("python plugin: Unable to convert \"%s\" to "
              "a python object.",
              dir);
        free(dir);
        cpy_log_exception("python initialization");
        status = 1;
        continue;
      }
      if (PyList_Insert(sys_path, 0, dir_object) != 0) {
        ERROR("python plugin: Unable to prepend \"%s\" to "
              "python module path.",
              dir);
        cpy_log_exception("python initialization");
        status = 1;
      }
      Py_DECREF(dir_object);
      free(dir);
    } else if (strcasecmp(item->key, "Import") == 0) {
      char *module_name = NULL;
      PyObject *module;

      if (cf_util_get_string(item, &module_name) != 0) {
        status = 1;
        continue;
      }
      module = PyImport_ImportModule(module_name); /* New reference. */
      if (module == NULL) {
        ERROR("python plugin: Error importing module \"%s\".", module_name);
        cpy_log_exception("importing module");
        status = 1;
      }
      free(module_name);
      Py_XDECREF(module);
    } else if (strcasecmp(item->key, "Module") == 0) {
      char *name = NULL;
      cpy_callback_t *c;
      PyObject *ret;

      if (cf_util_get_string(item, &name) != 0) {
        status = 1;
        continue;
      }
      for (c = cpy_config_callbacks; c; c = c->next) {
        if (strcasecmp(c->name + 7, name) == 0)
          break;
      }
      if (c == NULL) {
        WARNING("python plugin: Found a configuration for the \"%s\" plugin, "
                "but the plugin isn't loaded or didn't register "
                "a configuration callback.",
                name);
        free(name);
        continue;
      }
      free(name);
      if (c->data == NULL)
        ret = PyObject_CallFunction(
            c->callback, "N",
            cpy_oconfig_to_pyconfig(item, NULL)); /* New reference. */
      else
        ret = PyObject_CallFunction(c->callback, "NO",
                                    cpy_oconfig_to_pyconfig(item, NULL),
                                    c->data); /* New reference. */
      if (ret == NULL) {
        cpy_log_exception("loading module");
        status = 1;
      } else
        Py_DECREF(ret);
    } else {
      ERROR("python plugin: Unknown config key \"%s\".", item->key);
      status = 1;
    }
  }
  return (status);
}

void module_register(void) {
  plugin_register_complex_config("python", cpy_config);
  plugin_register_init("python", cpy_init);
  plugin_register_shutdown("python", cpy_shutdown);
}
