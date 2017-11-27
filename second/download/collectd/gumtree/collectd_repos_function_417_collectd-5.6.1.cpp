void module_register (void)
{
  plugin_register_config ("disk", disk_config,
      config_keys, config_keys_num);
  plugin_register_init ("disk", disk_init);
  plugin_register_shutdown ("disk", disk_shutdown);
  plugin_register_read ("disk", disk_read);
}