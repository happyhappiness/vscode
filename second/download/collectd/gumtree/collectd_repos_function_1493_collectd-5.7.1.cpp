static int c_ipmi_init(void) {
  int status;

  /* Don't send `ADD' notifications during startup (~ 1 minute) */
  time_t iv = CDTIME_T_TO_TIME_T(plugin_get_interval());
  c_ipmi_init_in_progress = 1 + (60 / iv);

  c_ipmi_active = 1;

  status = plugin_thread_create(&thread_id, /* attr = */ NULL, thread_main,
                                /* user data = */ NULL, "ipmi");
  if (status != 0) {
    c_ipmi_active = 0;
    thread_id = (pthread_t)0;
    ERROR("ipmi plugin: pthread_create failed.");
    return (-1);
  }

  return (0);
}