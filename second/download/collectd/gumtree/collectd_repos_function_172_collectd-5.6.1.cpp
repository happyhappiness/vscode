static int rc_init (void)
{
  if (config_collect_stats)
    plugin_register_read ("rrdcached", rc_read);

  return (0);
}