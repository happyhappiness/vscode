static meta_data_t *cpy_build_meta(PyObject *meta) {
  int s;
  meta_data_t *m = NULL;
  PyObject *l;

  if ((meta == NULL) || (meta == Py_None))
    return NULL;

  l = PyDict_Items(meta); /* New reference. */
  if (!l) {
    cpy_log_exception("building meta data");
    return NULL;
  }
  s = PyList_Size(l);
  if (s <= 0) {
    Py_XDECREF(l);
    return NULL;
  }

  m = meta_data_create();
  for (int i = 0; i < s; ++i) {
    const char *string, *keystring;
    PyObject *key, *value, *item, *tmp;

    item = PyList_GET_ITEM(l, i);
    key = PyTuple_GET_ITEM(item, 0);
    Py_INCREF(key);
    keystring = cpy_unicode_or_bytes_to_string(&key);
    if (!keystring) {
      PyErr_Clear();
      Py_XDECREF(key);
      continue;
    }
    value = PyTuple_GET_ITEM(item, 1);
    Py_INCREF(value);
    if (value == Py_True) {
      meta_data_add_boolean(m, keystring, 1);
    } else if (value == Py_False) {
      meta_data_add_boolean(m, keystring, 0);
    } else if (PyFloat_Check(value)) {
      meta_data_add_double(m, keystring, PyFloat_AsDouble(value));
    } else if (PyObject_TypeCheck(value, &SignedType)) {
      long long int lli;
      lli = PyLong_AsLongLong(value);
      if (!PyErr_Occurred() && (lli == (int64_t)lli))
        meta_data_add_signed_int(m, keystring, lli);
    } else if (PyObject_TypeCheck(value, &UnsignedType)) {
      long long unsigned llu;
      llu = PyLong_AsUnsignedLongLong(value);
      if (!PyErr_Occurred() && (llu == (uint64_t)llu))
        meta_data_add_unsigned_int(m, keystring, llu);
    } else if (PyNumber_Check(value)) {
      long long int lli;
      long long unsigned llu;
      tmp = PyNumber_Long(value);
      lli = PyLong_AsLongLong(tmp);
      if (!PyErr_Occurred() && (lli == (int64_t)lli)) {
        meta_data_add_signed_int(m, keystring, lli);
      } else {
        PyErr_Clear();
        llu = PyLong_AsUnsignedLongLong(tmp);
        if (!PyErr_Occurred() && (llu == (uint64_t)llu))
          meta_data_add_unsigned_int(m, keystring, llu);
      }
      Py_XDECREF(tmp);
    } else {
      string = cpy_unicode_or_bytes_to_string(&value);
      if (string) {
        meta_data_add_string(m, keystring, string);
      } else {
        PyErr_Clear();
        tmp = PyObject_Str(value);
        string = cpy_unicode_or_bytes_to_string(&tmp);
        if (string)
          meta_data_add_string(m, keystring, string);
        Py_XDECREF(tmp);
      }
    }
    if (PyErr_Occurred())
      cpy_log_exception("building meta data");
    Py_XDECREF(value);
    Py_DECREF(key);
  }
  Py_XDECREF(l);
  return m;
}