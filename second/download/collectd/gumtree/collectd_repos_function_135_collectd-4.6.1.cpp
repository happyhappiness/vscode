void module_register (void)
{
  plugin_register_config ("rrdcached", rc_config,
      config_keys, config_keys_num);
  plugin_register_init ("rrdcached", rc_init);
  plugin_register_write ("rrdcached", rc_write);
  plugin_register_shutdown ("rrdcached", rc_shutdown);
}