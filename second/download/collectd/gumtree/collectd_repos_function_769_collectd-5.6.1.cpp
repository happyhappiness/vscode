void module_register (void) /* {{{ */
{
  plugin_register_complex_config ("redis", redis_config);
  plugin_register_init ("redis", redis_init);
  plugin_register_read ("redis", redis_read);
  /* TODO: plugin_register_write: one redis list per value id with
   * X elements */
}