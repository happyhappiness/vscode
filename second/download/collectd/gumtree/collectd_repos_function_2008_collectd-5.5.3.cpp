void module_register (void)
{
  plugin_register_complex_config ("curl_json", cj_config);
  plugin_register_init ("curl_json", cj_init);
}