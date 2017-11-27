void module_register (void)
{
    plugin_register_write ("write_log", wl_write, NULL);
}