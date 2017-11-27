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