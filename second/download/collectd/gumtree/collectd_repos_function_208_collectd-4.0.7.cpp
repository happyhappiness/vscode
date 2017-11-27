void module_register (void)
{
#if NUT_HAVE_READ
  plugin_register_config ("nut", nut_config, config_keys, config_keys_num);
  plugin_register_read ("nut", nut_read);
  plugin_register_shutdown ("nut", nut_shutdown);
#endif
}