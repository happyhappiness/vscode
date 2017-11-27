static int cow_init (void)
{
  int status;
  struct timespec cb_interval;

  if (device_g == NULL)
  {
    ERROR ("onewire plugin: cow_init: No device configured.");
    return (-1);
  }

  status = (int) OW_init (device_g);
  if (status != 0)
  {
    ERROR ("onewire plugin: OW_init(%s) failed: %i.", device_g, status);
    return (1);
  }

  memset (&cb_interval, 0, sizeof (cb_interval));
  if (ow_interval > 0)
    cb_interval.tv_sec = (time_t) ow_interval;

  plugin_register_complex_read (/* group = */ NULL, "onewire", cow_read,
      &cb_interval, /* user data = */ NULL);
  plugin_register_shutdown ("onewire", cow_shutdown);

  return (0);
}