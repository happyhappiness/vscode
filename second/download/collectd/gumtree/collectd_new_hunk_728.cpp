      cpy_log_exception("shutdown callback");
    else
      Py_DECREF(ret);
  }
  PyErr_Print();

  Py_BEGIN_ALLOW_THREADS;
  cpy_unregister_list(&cpy_config_callbacks);
  cpy_unregister_list(&cpy_init_callbacks);
  cpy_unregister_list(&cpy_shutdown_callbacks);
  cpy_shutdown_triggered = 1;
  Py_END_ALLOW_THREADS;

  if (!cpy_num_callbacks) {
    Py_Finalize();
    return 0;
  }

  CPY_RELEASE_THREADS
  return 0;
