void module_register (void)
{
    plugin_register_init ("xencpu", xencpu_init);
    plugin_register_read ("xencpu", xencpu_read);
    plugin_register_shutdown ("xencpu", xencpu_shutdown);
}