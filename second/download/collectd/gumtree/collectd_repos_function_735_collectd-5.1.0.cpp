void module_register (void)
{
  plugin_register_complex_config ("ethstat", ethstat_config);
  plugin_register_read ("ethstat", ethstat_read);
}