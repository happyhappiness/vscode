void module_register (void)
{
  plugin_register_complex_config ("statsd", statsd_config);
  plugin_register_init ("statsd", statsd_init);
  plugin_register_read ("statsd", statsd_read);
  plugin_register_shutdown ("statsd", statsd_shutdown);
}