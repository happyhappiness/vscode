void module_register (void)
{
  plugin_register_complex_config ("curl", cc_config);
  plugin_register_init ("curl", cc_init);
  plugin_register_read ("curl", cc_read);
  plugin_register_shutdown ("curl", cc_shutdown);
}