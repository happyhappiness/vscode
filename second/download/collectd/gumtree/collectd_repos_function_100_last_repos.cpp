static int lv_read(user_data_t *ud) {
  time_t t;
  struct lv_read_instance *inst = NULL;
  struct lv_read_state *state = NULL;

  if (ud->data == NULL) {
    ERROR(PLUGIN_NAME " plugin: NULL userdata");
    return -1;
  }

  inst = ud->data;
  state = &inst->read_state;

  if (inst->id == 0) {
    if (lv_connect() < 0)
      return -1;
  }

  time(&t);

  /* Need to refresh domain or device lists? */
  if ((last_refresh == (time_t)0) ||
      ((interval > 0) && ((last_refresh + interval) <= t))) {
    if (refresh_lists(inst) != 0) {
      if (inst->id == 0)
        lv_disconnect();
      return -1;
    }
    last_refresh = t;
  }

#if 0
    for (int i = 0; i < nr_domains; ++i)
        fprintf (stderr, "domain %s\n", virDomainGetName (state->domains[i].ptr));
    for (int i = 0; i < nr_block_devices; ++i)
        fprintf  (stderr, "block device %d %s:%s\n",
                  i, virDomainGetName (block_devices[i].dom),
                  block_devices[i].path);
    for (int i = 0; i < nr_interface_devices; ++i)
        fprintf (stderr, "interface device %d %s:%s\n",
                 i, virDomainGetName (interface_devices[i].dom),
                 interface_devices[i].path);
#endif

  /* Get domains' metrics */
  for (int i = 0; i < state->nr_domains; ++i) {
    int status = get_domain_metrics(&state->domains[i]);
    if (status != 0)
      ERROR(PLUGIN_NAME " failed to get metrics for domain=%s",
            virDomainGetName(state->domains[i].ptr));
  }

  /* Get block device stats for each domain. */
  for (int i = 0; i < state->nr_block_devices; ++i) {
    int status = get_block_stats(&state->block_devices[i]);
    if (status != 0)
      ERROR(PLUGIN_NAME
            " failed to get stats for block device (%s) in domain %s",
            state->block_devices[i].path,
            virDomainGetName(state->domains[i].ptr));
  }

  /* Get interface stats for each domain. */
  for (int i = 0; i < state->nr_interface_devices; ++i) {
    int status = get_if_dev_stats(&state->interface_devices[i]);
    if (status != 0)
      ERROR(PLUGIN_NAME
            " failed to get interface stats for device (%s) in domain %s",
            state->interface_devices[i].path,
            virDomainGetName(state->interface_devices[i].dom));
  }

  return 0;
}