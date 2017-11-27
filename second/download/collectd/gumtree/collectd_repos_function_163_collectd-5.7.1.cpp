void module_register(void) /* {{{ */
{
  plugin_register_complex_config("dbi", cdbi_config);
  plugin_register_init("dbi", cdbi_init);
  plugin_register_shutdown("dbi", cdbi_shutdown);
}