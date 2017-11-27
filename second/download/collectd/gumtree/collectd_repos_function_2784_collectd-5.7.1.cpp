static int my_read(void) {
  /* do the magic to read the data */
  gauge_t value = random();

  if (my_submit(value) != 0)
    WARNING("myplugin plugin: Dispatching a random value failed.");

  /* A return value != 0 indicates an error and the plugin will be skipped
   * for an increasing amount of time. */
  return 0;
}