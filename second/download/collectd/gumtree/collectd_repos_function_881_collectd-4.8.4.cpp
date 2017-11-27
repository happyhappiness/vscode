void module_register (void)
{
  plugin_register_complex_config ("gmond", gmond_config);
  plugin_register_init ("gmond", gmond_init);
  plugin_register_shutdown ("gmond", gmond_shutdown);
}