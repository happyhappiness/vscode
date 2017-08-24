{
    /* Ignore errors. No good way to signal them without leaking memory. */
    FreeLibrary(lib->handle);
    lib->handle = NULL;
  }