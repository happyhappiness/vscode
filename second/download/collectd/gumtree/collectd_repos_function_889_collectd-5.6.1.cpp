void module_register (void)
{
  plugin_register_complex_config ("memcached", memcached_config);
  plugin_register_init ("memcached", memcached_init);
}