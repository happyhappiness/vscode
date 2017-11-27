      Py_XDECREF(key);
      continue;
    }
    value = PyTuple_GET_ITEM(item, 1);
    Py_INCREF(value);
    if (value == Py_True) {
      meta_func->add_boolean(m, keystring, 1);
    } else if (value == Py_False) {
      meta_func->add_boolean(m, keystring, 0);
    } else if (PyFloat_Check(value)) {
      meta_func->add_double(m, keystring, PyFloat_AsDouble(value));
    } else if (PyObject_TypeCheck(value, &SignedType)) {
      long long int lli;
      lli = PyLong_AsLongLong(value);
      if (!PyErr_Occurred() && (lli == (int64_t)lli))
        meta_func->add_signed_int(m, keystring, lli);
    } else if (PyObject_TypeCheck(value, &UnsignedType)) {
      long long unsigned llu;
      llu = PyLong_AsUnsignedLongLong(value);
      if (!PyErr_Occurred() && (llu == (uint64_t)llu))
        meta_func->add_unsigned_int(m, keystring, llu);
    } else if (PyNumber_Check(value)) {
      long long int lli;
      long long unsigned llu;
      tmp = PyNumber_Long(value);
      lli = PyLong_AsLongLong(tmp);
      if (!PyErr_Occurred() && (lli == (int64_t)lli)) {
        meta_func->add_signed_int(m, keystring, lli);
      } else {
        PyErr_Clear();
        llu = PyLong_AsUnsignedLongLong(tmp);
        if (!PyErr_Occurred() && (llu == (uint64_t)llu))
          meta_func->add_unsigned_int(m, keystring, llu);
      }
      Py_XDECREF(tmp);
    } else {
      string = cpy_unicode_or_bytes_to_string(&value);
      if (string) {
        meta_func->add_string(m, keystring, string);
      } else {
        PyErr_Clear();
        tmp = PyObject_Str(value);
        string = cpy_unicode_or_bytes_to_string(&tmp);
        if (string)
          meta_func->add_string(m, keystring, string);
        Py_XDECREF(tmp);
      }
    }
    if (PyErr_Occurred())
      cpy_log_exception("building meta data");
    Py_XDECREF(value);
    Py_DECREF(key);
  }
  Py_XDECREF(l);
  return 0;
}

#define CPY_BUILD_META_FUNC(meta_type, func, val_type)                         \
  static int cpy_##func(void *meta, const char *key, val_type val) {           \
    return func((meta_type *)meta, key, val);                                  \
  }

#define CPY_BUILD_META_HANDLER(func_prefix, meta_type)                         \
  CPY_BUILD_META_FUNC(meta_type, func_prefix##_add_string, const char *)       \
  CPY_BUILD_META_FUNC(meta_type, func_prefix##_add_signed_int, int64_t)        \
  CPY_BUILD_META_FUNC(meta_type, func_prefix##_add_unsigned_int, uint64_t)     \
  CPY_BUILD_META_FUNC(meta_type, func_prefix##_add_double, double)             \
  CPY_BUILD_META_FUNC(meta_type, func_prefix##_add_boolean, _Bool)             \
                                                                               \
  static cpy_build_meta_handler_t cpy_##func_prefix = {                        \
      .add_string = cpy_##func_prefix##_add_string,                            \
      .add_signed_int = cpy_##func_prefix##_add_signed_int,                    \
      .add_unsigned_int = cpy_##func_prefix##_add_unsigned_int,                \
      .add_double = cpy_##func_prefix##_add_double,                            \
      .add_boolean = cpy_##func_prefix##_add_boolean}

CPY_BUILD_META_HANDLER(meta_data, meta_data_t);
CPY_BUILD_META_HANDLER(plugin_notification_meta, notification_t);

static meta_data_t *cpy_build_meta(PyObject *meta) {
  meta_data_t *m = meta_data_create();
  if (cpy_build_meta_generic(meta, &cpy_meta_data, (void *)m) < 0) {
    meta_data_destroy(m);
    return NULL;
  }
  return m;
}

static void cpy_build_notification_meta(notification_t *n, PyObject *meta) {
  cpy_build_meta_generic(meta, &cpy_plugin_notification_meta, (void *)n);
}

static PyObject *Values_dispatch(Values *self, PyObject *args, PyObject *kwds) {
  int ret;
  const data_set_t *ds;
  size_t size;
  value_t *value;
  value_list_t value_list = VALUE_LIST_INIT;
