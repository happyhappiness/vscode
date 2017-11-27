void module_register (void)
{
  plugin_register_init ("numa", numa_init);
  plugin_register_read ("numa", numa_read);
}