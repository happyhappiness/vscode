static void *c_ipmi_thread_main(void *user_data) {
  c_ipmi_instance_t *st = user_data;

  int status = c_ipmi_thread_init(st);
  if (status != 0) {
    ERROR("ipmi plugin: c_ipmi_thread_init failed.");
    st->active = 0;
    return (void *)-1;
  }

  while (st->active != 0) {
    struct timeval tv = {1, 0};
    os_handler->perform_one_op(os_handler, &tv);
  }
  return (void *)0;
}