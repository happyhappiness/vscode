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