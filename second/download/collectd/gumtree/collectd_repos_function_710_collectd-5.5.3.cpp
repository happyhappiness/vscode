void module_register (void)
{
  plugin_register_init ("onewire", cow_init);
  plugin_register_config ("onewire", cow_load_config,
                          config_keys, config_keys_num);
}