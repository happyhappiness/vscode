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
    if (plugin_thread_create(&thread, NULL, cpy_interactive, pipefd + 1,
                             "python interpreter")) {
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