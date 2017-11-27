void module_register (void)
{
  plugin_register_config ("netlink", ir_config, config_keys, config_keys_num);
  plugin_register_init ("netlink", ir_init);
  plugin_register_read ("netlink", ir_read);
  plugin_register_shutdown ("netlink", ir_shutdown);
}