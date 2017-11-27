void module_register (void) /* {{{ */
{
        plugin_register_complex_config ("write_http", wh_config);
        plugin_register_init ("write_http", wh_init);
}