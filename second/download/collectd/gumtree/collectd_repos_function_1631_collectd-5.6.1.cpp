void module_register (void)
{
  plugin_register_complex_config ("curl_xml", cx_config);
  plugin_register_init ("curl_xml", cx_init);
}