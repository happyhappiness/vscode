void module_register (void)
{
  plugin_register_config ("vmem", vmem_config,
      config_keys, config_keys_num);
  plugin_register_read ("vmem", vmem_read);
}