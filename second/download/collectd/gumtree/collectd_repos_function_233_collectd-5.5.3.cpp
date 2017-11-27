void
module_register (void)
{
    plugin_register_config (PLUGIN_NAME,
    lv_config,
    config_keys, NR_CONFIG_KEYS);
    plugin_register_init (PLUGIN_NAME, lv_init);
    plugin_register_read (PLUGIN_NAME, lv_read);
    plugin_register_shutdown (PLUGIN_NAME, lv_shutdown);
}