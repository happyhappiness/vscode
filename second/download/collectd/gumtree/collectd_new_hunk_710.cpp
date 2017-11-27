                                    const char *name, void *callback,
                                    user_data_t const *ud) {
  callback_func_t *cf;

  cf = calloc(1, sizeof(*cf));
  if (cf == NULL) {
    free_userdata(ud);
    ERROR("plugin: create_register_callback: calloc failed.");
    return -1;
  }

  cf->cf_callback = callback;
  if (ud == NULL) {
    cf->cf_udata.data = NULL;
    cf->cf_udata.free_func = NULL;
  } else {
    cf->cf_udata = *ud;
  }

  cf->cf_ctx = plugin_get_ctx();

  return register_callback(list, name, cf);
} /* }}} int create_register_callback */

static int plugin_unregister(llist_t *list, const char *name) /* {{{ */
{
  llentry_t *e;

  if (list == NULL)
    return -1;

  e = llist_search(list, name);
  if (e == NULL)
    return -1;

  llist_remove(list, e);

  sfree(e->key);
  destroy_callback(e->value);

  llentry_destroy(e);

  return 0;
} /* }}} int plugin_unregister */

/*
 * (Try to) load the shared object `file'. Won't complain if it isn't a shared
 * object, but it will bitch about a shared object not having a
 * ``module_register'' symbol..
 */
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

static void *plugin_read_thread(void __attribute__((unused)) * args) {
  while (read_loop != 0) {
    read_func_t *rf;
    plugin_ctx_t old_ctx;
