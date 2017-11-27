      PyList_SetItem(list, i,
                     PyLong_FromLongLong(value_list->values[i].derive));
    } else if (ds->ds[i].type == DS_TYPE_ABSOLUTE) {
      PyList_SetItem(
          list, i, PyLong_FromUnsignedLongLong(value_list->values[i].absolute));
    } else {
      Py_BEGIN_ALLOW_THREADS;
      ERROR("cpy_write_callback: Unknown value type %d.", ds->ds[i].type);
      Py_END_ALLOW_THREADS;
      Py_DECREF(list);
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
    char **table = NULL;
    meta_data_t *meta = value_list->meta;

    int num = meta_data_toc(meta, &table);
    for (int i = 0; i < num; ++i) {
      int type;
      char *string;
