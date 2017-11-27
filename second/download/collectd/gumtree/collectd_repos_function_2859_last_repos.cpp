static int plugin_load_file(const char *file, _Bool global) {
  void (*reg_handle)(void);

  int flags = RTLD_NOW;
  if (global)
    flags |= RTLD_GLOBAL;

  void *dlh = dlopen(file, flags);

  if (dlh == NULL) {
    char errbuf[1024] = "";

    snprintf(errbuf, sizeof(errbuf),
             "dlopen (\"%s\") failed: %s. "
             "The most common cause for this problem is "
             "missing dependencies. Use ldd(1) to check "
             "the dependencies of the plugin "
             "/ shared object.",
             file, dlerror());

    ERROR("%s", errbuf);
    /* Make sure this is printed to STDERR in any case, but also
     * make sure it's printed only once. */
    if (list_log != NULL)
      fprintf(stderr, "ERROR: %s\n", errbuf);

    return 1;
  }

  reg_handle = (void (*)(void))dlsym(dlh, "module_register");
  if (reg_handle == NULL) {
    WARNING("Couldn't find symbol \"module_register\" in \"%s\": %s\n", file,
            dlerror());
    dlclose(dlh);
    return -1;
  }

  (*reg_handle)();

  return 0;
}