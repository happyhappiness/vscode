{
    /* Ignore errors. No good way to signal them without leaking memory. */
    dlclose(lib->handle);
    lib->handle = NULL;
  }