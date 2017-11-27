void module_register (void)
{
  cgps_config_data.host = sstrdup (CGPS_DEFAULT_HOST);
  cgps_config_data.port = sstrdup (CGPS_DEFAULT_PORT);
  cgps_config_data.timeout = CGPS_DEFAULT_TIMEOUT;
  cgps_config_data.pause_connect = CGPS_DEFAULT_PAUSE_CONNECT;

  plugin_register_complex_config ("gps", cgps_config);
  plugin_register_init ("gps", cgps_init);
  plugin_register_read ("gps", cgps_read);
  plugin_register_shutdown ("gps", cgps_shutdown);
}