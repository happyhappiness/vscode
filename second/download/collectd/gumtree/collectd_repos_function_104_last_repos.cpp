static int lv_init(void) {
  if (virInitialize() != 0)
    return -1;

  if (lv_connect() != 0)
    return -1;

  DEBUG(PLUGIN_NAME " plugin: starting %i instances", nr_instances);

  for (int i = 0; i < nr_instances; ++i)
    lv_init_instance(i, lv_read);

  return 0;
}