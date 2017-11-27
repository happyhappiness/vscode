void module_register (void)
{
  plugin_register_config ("exec", exec_config, config_keys, config_keys_num);
  plugin_register_read ("exec", exec_read);
  plugin_register_shutdown ("exec", exec_shutdown);
}