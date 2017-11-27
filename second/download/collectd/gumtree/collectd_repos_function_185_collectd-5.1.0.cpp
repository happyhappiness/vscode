void module_register (void)
{
  plugin_register_complex_config ("rrdcached", rc_config);
  plugin_register_init ("rrdcached", rc_init);
  plugin_register_shutdown ("rrdcached", rc_shutdown);
}