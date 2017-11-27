void module_register (void)
{
  plugin_register_config ("nginx", config, config_keys, config_keys_num);
  plugin_register_init ("nginx", init);
  plugin_register_read ("nginx", nginx_read);
}