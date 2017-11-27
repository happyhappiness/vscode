void module_register (void)
{
    plugin_register_config ("uuid", uuid_config,
            config_keys, STATIC_ARRAY_SIZE (config_keys));
    plugin_register_init ("uuid", uuid_init);
}