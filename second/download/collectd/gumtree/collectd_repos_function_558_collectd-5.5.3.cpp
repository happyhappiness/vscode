void module_register (void)
{
    plugin_register_config ("barometer",
                            collectd_barometer_config,
                            config_keys,
                            config_keys_num);
    plugin_register_init ("barometer", collectd_barometer_init);
    plugin_register_shutdown ("barometer", collectd_barometer_shutdown);
}