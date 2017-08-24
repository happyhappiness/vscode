{
    /* The Ctrl handler is currently working on exiting our process.  Rather
    than return an error code, which could cause incorrect conclusions to be
    reached by the caller, we simply hang.  (For example, a CMake try_run
    configure step might cause the project to configure wrong.)  */
    Sleep(INFINITE);
  }