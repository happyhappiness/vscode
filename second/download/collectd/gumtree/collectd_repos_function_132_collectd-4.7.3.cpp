static int rc_init (void)
{
  if (config_collect_stats != 0)
    plugin_register_read ("rrdcached", rc_read);

  return (0);
}