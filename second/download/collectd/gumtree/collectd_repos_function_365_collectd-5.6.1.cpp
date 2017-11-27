void module_register (void)
{
    plugin_register_complex_config ("amqp", camqp_config);
    plugin_register_shutdown ("amqp", camqp_shutdown);
}