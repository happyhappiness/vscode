static int c_ipmi_read(void) {
  if ((c_ipmi_active == 0) || (thread_id == (pthread_t)0)) {
    INFO("ipmi plugin: c_ipmi_read: I'm not active, returning false.");
    return (-1);
  }

  sensor_list_read_all();

  if (c_ipmi_init_in_progress > 0)
    c_ipmi_init_in_progress--;
  else
    c_ipmi_init_in_progress = 0;

  return (0);
}