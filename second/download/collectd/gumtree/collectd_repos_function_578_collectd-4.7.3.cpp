void module_register (void)
{
  plugin_register_complex_config ("bind", bind_config);
  plugin_register_init ("bind", bind_init);
  plugin_register_read ("bind", bind_read);
  plugin_register_shutdown ("bind", bind_shutdown);
}