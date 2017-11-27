void module_register (void)
{
    plugin_register_config ("ted", ted_config,
            config_keys, config_keys_num);
    plugin_register_read ("ted", ted_read);
    plugin_register_shutdown ("ted", ted_shutdown);
}