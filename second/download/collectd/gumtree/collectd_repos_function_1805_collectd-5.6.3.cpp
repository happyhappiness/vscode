void module_register(void) /* {{{ */
{
  plugin_register_complex_config("oracle", o_config);
  plugin_register_init("oracle", o_init);
  plugin_register_read("oracle", o_read);
  plugin_register_shutdown("oracle", o_shutdown);
}