static int c_ipmi_shutdown(void) {
  c_ipmi_instance_t *st = instances;
  instances = NULL;

  while (st != NULL) {
    c_ipmi_instance_t *next = st->next;

    st->next = NULL;
    st->active = 0;

    if (!pthread_equal(st->thread_id, (pthread_t){0})) {
      pthread_join(st->thread_id, NULL);
      st->thread_id = (pthread_t){0};
    }