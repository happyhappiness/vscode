void module_register (void)
{
  plugin_register_complex_config ("exec", exec_config);
  plugin_register_init ("exec", exec_init);
  plugin_register_read ("exec", exec_read);
  plugin_register_notification ("exec", exec_notification,
      /* user_data = */ NULL);
  plugin_register_shutdown ("exec", exec_shutdown);
}