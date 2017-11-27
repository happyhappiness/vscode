void module_register (void)
{
    plugin_register_complex_config ("mqtt", mqtt_config);
    plugin_register_init ("mqtt", mqtt_init);
}