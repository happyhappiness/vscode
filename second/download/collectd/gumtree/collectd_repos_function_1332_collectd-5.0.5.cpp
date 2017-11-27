void module_register (void)
{
  plugin_register_complex_config ("threshold", ut_config);
  plugin_register_missing ("threshold", ut_missing,
      /* user data = */ NULL);
  plugin_register_write ("threshold", ut_check_threshold,
      /* user data = */ NULL);
}