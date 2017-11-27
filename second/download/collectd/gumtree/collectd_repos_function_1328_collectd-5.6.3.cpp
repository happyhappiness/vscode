void module_register(void) /* {{{ */
{
  plugin_register_complex_config("pinba", plugin_config);
  plugin_register_init("pinba", plugin_init);
  plugin_register_read("pinba", plugin_read);
  plugin_register_shutdown("pinba", plugin_shutdown);
}