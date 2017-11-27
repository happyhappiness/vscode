static int c_ipmi_init(void) {
  c_ipmi_instance_t *st;
  char callback_name[3 * DATA_MAX_NAME_LEN];

  if (os_handler != NULL) {
    return 0;
  }

  os_handler = ipmi_posix_thread_setup_os_handler(SIGIO);
  if (os_handler == NULL) {
    ERROR("ipmi plugin: ipmi_posix_thread_setup_os_handler failed.");
    return -1;
  }

  os_handler->set_log_handler(os_handler, c_ipmi_log);

  if (ipmi_init(os_handler) != 0) {
    ERROR("ipmi plugin: ipmi_init() failed.");
    os_handler->free_os_handler(os_handler);
    return -1;
  };

  if (instances == NULL) {
    /* No instances were configured, let's start a default instance. */
    st = c_ipmi_init_instance();
    if (st == NULL)
      return ENOMEM;

    c_ipmi_add_instance(st);
  }

  /* Don't send `ADD' notifications during startup (~ 1 minute) */
  int cycles = 1 + (60 / CDTIME_T_TO_TIME_T(plugin_get_interval()));

  st = instances;
  while (NULL != st) {
    /* The `st->name` is used as "domain name" for ipmi_open_domain().
     * That value should be unique, so we do plugin_register_complex_read()
     * at first as it checks the uniqueness. */
    snprintf(callback_name, sizeof(callback_name), "ipmi/%s", st->name);

    user_data_t ud = {
        .data = st,
    };

    int status = plugin_register_complex_read(
        /* group     = */ "ipmi",
        /* name      = */ callback_name,
        /* callback  = */ c_ipmi_read,
        /* interval  = */ 0,
        /* user_data = */ &ud);

    if (status != 0) {
      st = st->next;
      continue;
    }

    st->init_in_progress = cycles;
    st->active = 1;

    status = plugin_thread_create(&st->thread_id, /* attr = */ NULL,
                                  c_ipmi_thread_main,
                                  /* user data = */ (void *)st, "ipmi");

    if (status != 0) {
      st->active = 0;
      st->thread_id = (pthread_t){0};

      plugin_unregister_read(callback_name);

      ERROR("ipmi plugin: pthread_create failed for `%s`.", callback_name);
    }

    st = st->next;
  }

  return 0;
}